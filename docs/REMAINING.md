# Còn thiếu so với macOS MxU Slides (252k dòng)

Bản Windows đã覆盖 phần lõi của 6 phase. Những hạng mục dưới đây cần SDK,
phần cứng hoặc thời gian triển khai riêng:

| Hạng mục macOS | Lý do chưa làm | Cách nối tiếp |
|---|---|---|
| Automerge CRDT wire format | Cần automerge-cpp + xcframework parity | `core::SyncLedger` + `/v1/sync` là lớp thay thế; map thao tác sang Automerge op |
| NDI sender thật | Cần NDI SDK for Windows | `MXU_ENABLE_NDI` → thay body `api::NdiSender::start` bằng `NDIlib_send_create` |
| DeckLink output/keying | Cần Blackmagic SDK | `MXU_ENABLE_DECKLINK` → `IDeckLinkOutput` |
| Encoder RTMP/HLS/SRT + recorder | Cần FFmpeg/Media Foundation/MF transforms | `MXU_ENABLE_FFMPEG` → `api::StreamingService` |
| MTC/LTC timecode decode | WinMM MIDI input đã có; timecode vẫn dùng system clock | mở rộng `AutomationService` |
| Keystone/tilt + mask | `SceneView` đã render shape/path/blend (PNG export) | viết ShaderEffect/HLSL cho mask/keystone |
| ProPresenter protobuf | Cần generated protobuf types | mở rộng `AppController::importProPresenter`; PPTX text import đã có `PptxImporter` |
| Audio 2-deck crossfade, multitrack stems | Cần DSP ring buffer/WASAPI low-latency | mở rộng `AudioService` |
| Bonjour/mDNS full + follow pairing | Đã có ~30 routes, `DiscoveryService` UDP heartbeat và DPAPI vault | mở rộng `api::LocalApiServer`/`DiscoveryService` |
| Hitch report export | `DiagnosticsService` đã có fps/hitches/maxFrameMs | thêm file report/CLI |

Nguyên tắc khi port tiếp: giữ schema `schemaVersion 161` làm nguồn chân lý, mọi
field mới optional; giữ contract LocalAPI/OpenAPI để remote app dùng lại.
