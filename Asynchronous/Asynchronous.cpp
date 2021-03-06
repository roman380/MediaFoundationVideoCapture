#include <winsdkver.h>
#include <sdkddkver.h>

#include <unknwn.h>
#include <winrt\base.h>

#include <iostream>
#include <functional>

#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>

#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mf.lib")
#pragma comment(lib, "mfreadwrite.lib")

static UINT32 g_Index = 0;

class Callback : public winrt::implements<Callback, IMFSourceReaderCallback>
{
public:
	using ReadSample = std::function<void()>;

	Callback(ReadSample ReadSample) : 
		m_ReadSample(ReadSample)
	{
		WINRT_ASSERT(m_ReadSample);
	}

// IMFSourceReaderCallback
	IFACEMETHOD(OnReadSample)(HRESULT Status, DWORD StreamIndex, DWORD StreamFlags, LONGLONG Time, IMFSample* Sample) override
	{
		WINRT_ASSERT(SUCCEEDED(Status));
		Time -= m_BaseTime;
		std::wcout << 
			L"StreamIndex " << StreamIndex << L", " <<
			L"StreamFlags 0x" << std::hex << StreamFlags << L", " <<
			L"Time " << std::fixed << Time / 1E7 <<
			std::endl;
		if(StreamIndex == 0 && (StreamFlags & MF_SOURCE_READERF_STREAMTICK))
		{
			WINRT_ASSERT(!Sample);
			m_BaseTime = Time;
		}
		m_ReadSample();
		return S_OK;
	}
	IFACEMETHOD(OnFlush)(DWORD StreamIndex) override
	{
		return S_OK;
	}
	IFACEMETHOD(OnEvent)(DWORD StreamIndex, IMFMediaEvent* MediaEvent) override
	{
		return S_OK;
	}

private:
	ReadSample m_ReadSample;
	LONGLONG m_BaseTime = 0;
};

int main()
{
	std::wcout.precision(3);
	winrt::init_apartment();
	winrt::check_hresult(MFStartup(MF_VERSION));
	{
		winrt::com_ptr<IMFMediaSource> MediaSource;
		{
			winrt::com_ptr<IMFActivate> Activate;
			{
				winrt::com_ptr<IMFAttributes> Attributes;
				winrt::check_hresult(MFCreateAttributes(Attributes.put(), 1));
				winrt::check_hresult(Attributes->SetGUID(MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE, MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID));
				IMFActivate** Activates = nullptr;
				UINT32 ActivateCount = 0;
				winrt::check_hresult(MFEnumDeviceSources(Attributes.get(), &Activates, &ActivateCount));
				WINRT_ASSERT(g_Index < ActivateCount);
				Activate.copy_from(Activates[g_Index]);
				for(UINT32 Index = 0; Index < ActivateCount; Index++)
					Activates[Index]->Release();
				CoTaskMemFree(Activates);
			}
			winrt::check_hresult(Activate->ActivateObject(IID_PPV_ARGS(MediaSource.put())));
			wchar_t FriendlyName[256];
			UINT32 FriendlyNameLength;
			winrt::check_hresult(Activate->GetString(MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME, FriendlyName, static_cast<UINT32>(std::size(FriendlyName)), &FriendlyNameLength));
			std::wcout << L"Friendly Name: " << FriendlyName << std::endl;
		}
		winrt::com_ptr<IMFSourceReader> SourceReader;
		auto const ReadSample = [&]
		{
			winrt::check_hresult(SourceReader->ReadSample(MF_SOURCE_READER_ANY_STREAM, 0, nullptr, nullptr, nullptr, nullptr));
		};
		auto const SourceReaderCallback = winrt::make_self<Callback>(ReadSample);
		winrt::com_ptr<IMFAttributes> Attributes;
		winrt::check_hresult(MFCreateAttributes(Attributes.put(), 1));
		winrt::check_hresult(Attributes->SetUnknown(MF_SOURCE_READER_ASYNC_CALLBACK, SourceReaderCallback.get()));
		winrt::check_hresult(MFCreateSourceReaderFromMediaSource(MediaSource.get(), Attributes.get(), SourceReader.put()));
		ReadSample();
		for(; ; )
			SwitchToThread();
	}
	winrt::check_hresult(MFShutdown());
    return 0;
}
