#include <winsdkver.h>
#include <sdkddkver.h>

#include <unknwn.h>
#include <winrt\base.h>

#include <iostream>
#include <sstream>

#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <mferror.h>

#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mf.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")

static UINT32 g_Index = 0;

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
		winrt::check_hresult(MFCreateSourceReaderFromMediaSource(MediaSource.get(), nullptr, SourceReader.put()));

		for(DWORD StreamIndex = 0; ; StreamIndex++)
		{
			//std::wcout << L"Stream " << StreamIndex << L":" << std::endl;
			HRESULT Result;
			for(DWORD MediaTypeIndex = 0; ; MediaTypeIndex++)
			{
				winrt::com_ptr<IMFMediaType> MediaType;
				Result = SourceReader->GetNativeMediaType(StreamIndex, MediaTypeIndex, MediaType.put());
				if(Result == MF_E_INVALIDSTREAMNUMBER || Result == MF_E_NO_MORE_TYPES)
					break;
				winrt::check_hresult(Result);
				{
					GUID Subtype;
					winrt::check_hresult(MediaType->GetGUID(MF_MT_SUBTYPE, &Subtype));
					wchar_t SubtypeText[64];
					WINRT_VERIFY(StringFromGUID2(Subtype, SubtypeText, static_cast<int>(std::size(SubtypeText))));
					std::pair<UINT32, UINT32> FrameSize;
					winrt::check_hresult(MFGetAttributeSize(MediaType.get(), MF_MT_FRAME_SIZE, &FrameSize.first, &FrameSize.second));
					//std::wcout << L"Media Type " << MediaTypeIndex << ": " << FrameSize.first << " x " << FrameSize.second << ", " << SubtypeText << std::endl;
				}
				//winrt::check_hresult(SourceReader->SetCurrentMediaType(StreamIndex, nullptr, MediaType.get()));
			}
			if(Result == MF_E_INVALIDSTREAMNUMBER)
				break;
		}

		{
			winrt::com_ptr<IMFMediaType> MediaType;
			winrt::check_hresult(SourceReader->GetNativeMediaType(0u, 323u, MediaType.put()));
			std::pair<UINT32, UINT32> FrameSize;
			winrt::check_hresult(MFGetAttributeSize(MediaType.get(), MF_MT_FRAME_SIZE, &FrameSize.first, &FrameSize.second));
			WINRT_ASSERT(FrameSize.first == 1280u && FrameSize.second == 720u);
			std::wcout << L"SetCurrentMediaType: " << FrameSize.first << L" x " << FrameSize.second << std::endl;
			winrt::check_hresult(SourceReader->SetCurrentMediaType(0u, nullptr, MediaType.get()));
		}

		LONGLONG BaseTime = 0;
		bool MediaTypeChanged = false;
		for(; ; )
		{
			DWORD StreamIndex;
			DWORD StreamFlags;
			LONGLONG Time;
			winrt::com_ptr<IMFSample> Sample;
			winrt::check_hresult(SourceReader->ReadSample(MF_SOURCE_READER_ANY_STREAM, 0, &StreamIndex, &StreamFlags, &Time, Sample.put()));
			Time -= BaseTime;

			std::wostringstream Stream;
			Stream <<
				L"StreamIndex " << StreamIndex << L", " <<
				L"StreamFlags 0x" << std::hex << StreamFlags << std::dec << L", " <<
				L"Time " << std::fixed << Time / 1E7;
			if(Sample)
			{
				winrt::com_ptr<IMFMediaBuffer> MediaBuffer;
				winrt::check_hresult(Sample->ConvertToContiguousBuffer(MediaBuffer.put()));
				DWORD Size = 0;
				winrt::check_hresult(MediaBuffer->GetCurrentLength(&Size));
				Stream << L", Size " << Size;
			}
			std::wcout << Stream.str() << std::endl;

			if(StreamIndex == 0 && (StreamFlags & MF_SOURCE_READERF_STREAMTICK))
			{
				WINRT_ASSERT(!Sample);
				BaseTime = Time;
				continue;
			}
			if(!MediaTypeChanged && Time >= 1'000'0000ll)
			{
				MediaTypeChanged = true;
				winrt::com_ptr<IMFMediaType> MediaType;
				winrt::check_hresult(SourceReader->GetNativeMediaType(0u, 355u, MediaType.put()));
				std::pair<UINT32, UINT32> FrameSize;
				winrt::check_hresult(MFGetAttributeSize(MediaType.get(), MF_MT_FRAME_SIZE, &FrameSize.first, &FrameSize.second));
				WINRT_ASSERT(FrameSize.first == 1920u && FrameSize.second == 1080u);
				std::wcout << L"SetCurrentMediaType: " << FrameSize.first << L" x " << FrameSize.second << std::endl;
				winrt::check_hresult(SourceReader->SetCurrentMediaType(0u, nullptr, MediaType.get()));
			}
			#if !defined(NDEBUG)
				else if(Time >= 3'000'0000ll)
					std::this_thread::yield();
			#endif
			// TODO: Get one's hands down to Sample contents
		}
	}
	winrt::check_hresult(MFShutdown());
	return 0;
}
