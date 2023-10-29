# Synchronous

See [SharpDX camera streaming not respecting MediaType set](https://stackoverflow.com/a/77383293/868014) for the original Q.

## Sample Output

Media type changes triggers video frame buffer size change.

```
Friendly Name: BRIO 4K Stream Edition
SetCurrentMediaType: 1280 x 720
StreamIndex 0, StreamFlags 0x100, Time 48727.428745
StreamIndex 0, StreamFlags 0x0, Time 0.116069, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.132025, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.148124, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.164089, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.180003, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.196032, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.212031, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.228095, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.244027, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.259990, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.276009, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.292087, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.308082, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.340064, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.355993, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.372090, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.388026, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.404012, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.420082, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.436012, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.452071, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.468075, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.484074, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.500020, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.516078, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.532006, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.548098, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.564077, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.580086, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.596070, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.612075, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.628073, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.644082, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.660065, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.676082, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.692075, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.708082, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.740065, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.756076, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.772079, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.788072, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.804061, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.820017, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.836071, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.852061, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.868069, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.884072, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.900028, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.916036, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.932011, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.948117, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.964040, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.980070, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 0.996061, Size 1382400
StreamIndex 0, StreamFlags 0x0, Time 1.012077, Size 1382400
SetCurrentMediaType: 1920 x 1080
StreamIndex 0, StreamFlags 0x0, Time 2.384053, Size 3110400
StreamIndex 0, StreamFlags 0x0, Time 2.416234, Size 3110400
StreamIndex 0, StreamFlags 0x0, Time 2.448192, Size 3110400
StreamIndex 0, StreamFlags 0x0, Time 2.480115, Size 3110400
StreamIndex 0, StreamFlags 0x0, Time 2.512117, Size 3110400
StreamIndex 0, StreamFlags 0x0, Time 2.544112, Size 3110400
StreamIndex 0, StreamFlags 0x0, Time 2.576114, Size 3110400
StreamIndex 0, StreamFlags 0x0, Time 2.608131, Size 3110400
StreamIndex 0, StreamFlags 0x0, Time 2.640069, Size 3110400
StreamIndex 0, StreamFlags 0x0, Time 2.688092, Size 3110400
StreamIndex 0, StreamFlags 0x0, Time 2.720084, Size 3110400
StreamIndex 0, StreamFlags 0x0, Time 2.752092, Size 3110400
StreamIndex 0, StreamFlags 0x0, Time 2.784088, Size 3110400
StreamIndex 0, StreamFlags 0x0, Time 2.816047, Size 3110400
StreamIndex 0, StreamFlags 0x0, Time 2.848168, Size 3110400
StreamIndex 0, StreamFlags 0x0, Time 2.880129, Size 3110400
StreamIndex 0, StreamFlags 0x0, Time 2.912136, Size 3110400
StreamIndex 0, StreamFlags 0x0, Time 2.944122, Size 3110400
StreamIndex 0, StreamFlags 0x0, Time 2.976131, Size 3110400
StreamIndex 0, StreamFlags 0x0, Time 3.008132, Size 3110400
```