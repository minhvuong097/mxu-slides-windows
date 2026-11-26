# Cách bật NDI / DeckLink / FFmpeg trên Windows

Các backend này đã có code sẵn trong repo; chỉ cần SDK + cờ build.

## 1. FFmpeg (encoder RTMP/HLS/file)

```powershell
git clone https://github.com/microsoft/vcpkg C:\vcpkg
C:\vcpkg\bootstrap-vcpkg.bat
C:\vcpkg\vcpkg install ffmpeg:x64-windows

cmake -S . -B build -G "Visual Studio 17 2022" -A x64 `
  -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake `
  -DMXU_ENABLE_FFMPEG=ON -DMXU_BUILD_TESTS=ON
cmake --build build --config Release
```

`cmake/FindFFmpeg.cmake` tìm `avcodec/avformat/avutil/swscale`. Khi tìm thấy,
macro `MXU_HAS_FFMPEG` được định nghĩa và `src/api/FfmpegEncoder.cpp` biên dịch
đường dẫn thật: `avcodec_find_encoder(H264)` → `sws_scale` (BGRA→YUV420P) →
`av_interleaved_write_frame` tới URL (file/RTMP/HLS). Không tìm thấy → class vẫn
có nhưng `available() == false`.

## 2. NDI

Không cần SDK lúc build: `NdiDynamicSender` nạp DLL lúc chạy qua `QLibrary`.

1. Cài NDI Runtime cho Windows (`Processing.NDI.Lib.x64.dll`).
2. Đặt DLL cạnh `MxuSlides.exe` hoặc trong `C:\Program Files\NDI\NDI 5 SDK\Lib\x64`.
3. `Mxu.ndiDynamic.available` sẽ thành `true`; gọi `start("MxU Slides")`, `sendFrame(QImage)`.

Nếu muốn dùng NDI SDK API thật thay vì dynamic loader, thay phần resolve trong
`src/api/NdiDynamicSender.cpp` bằng include SDK và link `Processing.NDI.Lib.x64.lib`.

## 3. DeckLink

1. Cài Blackmagic Desktop Video SDK/Driver.
2. Header COM đã có sẵn trong `vendor/decklink/` (copy từ repo Mac), CMake tự thêm
   `vendor/decklink` vào include path khi `WIN32`.
3. Build:

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 `
  -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake `
  -DMXU_ENABLE_DECKLINK=ON
```

`src/api/DeckLinkWindows.cpp` dùng `CLSID_DeckLinkIterator`, `IDeckLinkOutput`,
`EnableVideoOutput(bmdModeHD1080p2997)`, `CreateVideoFrame(bmdFormat8BitBGRA)`,
`ScheduleVideoFrame`. Link `ole32`/`uuid`. Trên Linux file này chỉ biên dịch stub.

## 4. Kiểm tra sau build

- Settings › Stream and NDI: NDI/DeckLink/Streaming hiện trạng thái `Ready`/`Unavailable`.
- Local API: `GET /v1/presets`, `POST /v1/stream`, `POST /v1/record`.
- `QtMultimedia` + WASAPI: `Mxu.wasapi.available == true`, callback chạy ở thread render.
- Automerge: `Mxu.automerge.exportChanges()` / `importChanges()` (wire format `mxu-lww-v1`).

## Lưu ý

Tôi không thể biên dịch các cờ này trên máy Linux hiện tại (không có SDK Windows),
nên đường dẫn SDK chỉ được đảm bảo bởi cấu trúc code và cờ CMake; cần chạy build
trên Windows với SDK để xác nhận link.
