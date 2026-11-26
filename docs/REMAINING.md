# Còn thiếu so với macOS MxU Slides (252k dòng)

Bản Windows đã覆盖 phần lõi của 6 phase. Những hạng mục dưới đây cần SDK,
phần cứng hoặc thời gian triển khai riêng:

| Hạng mục macOS | Lý do chưa làm | Cách nối tiếp |
|---|---|---|
| Automerge CRDT wire format | Cần automerge-cpp + xcframework parity | `core::SyncLedger` là lớp thay thế; map操作 sang Automerge op |
| NDI sender thật | Cần NDI SDK for Windows | `MXU_ENABLE_NDI` → thay body `api::NdiSender::start` bằng `NDIlib_send_create` |
| DeckLink output/keying | Cần Blackmagic SDK | `MXU_ENABLE_DECKLINK` → `IDeckLinkOutput` |
| Encoder RTMP/HLS/SRT + recorder | Cần FFmpeg/Media Foundation/MF transforms | `MXU_ENABLE_FFMPEG` → `api::StreamingService` |
| MIDI hardware in/out, MTC/LTC | Cần WinRT MIDI / midiIn*; `midiAvailable()` hiện false | mở rộng `AutomationService` |
| Metal RHI blend/mask/keystone | Qt Quick/RHI chưa có shader tương đương | viết ShaderEffect/HLSL cho `SceneView` |
| ProPresenter protobuf, PPTX parser | Cần generated protobuf + OOXML | stub đã có trong `AppController` |
| Audio 2-deck crossfade, multitrack stems | Cần DSP ring buffer/WASAPI low-latency | mở rộng `AudioService` |
| 40+ LocalAPI routes, Bonjour, follow pairing | Đã có 18 routes; mDNS/DPAPI chưa | mở rộng `api::LocalApiServer` |
| Perf meter/hitch report | Cần instrumentation main thread | mở rộng `DiagnosticsService` |

Nguyên tắc khi port tiếp: giữ schema `schemaVersion 161` làm nguồn chân lý, mọi
field mới optional; giữ contract LocalAPI/OpenAPI để remote app dùng lại.
