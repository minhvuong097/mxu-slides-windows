# ProSlides for Windows

Bản port Windows của **MxU Slides** (macOS), tên sản phẩm **ProSlides**, viết bằng **C++20 / Qt 6**, với
giao diện 5 màn hình theo thiết kế **Service Flow** ("macOS-style", 1280×840).

Repo này là một codebase mới, xây dựng từ các khái niệm và cấu trúc dữ liệu của
`mxu-slides-main` (Swift) — không kế thừa codebase FreeShow cũ.

## Yêu cầu

- Windows 10/11, Visual Studio 2022 (MSVC, C++20)
- CMake ≥ 3.25
- Qt 6.12, kit `msvc2022_64` (tối thiểu 6.5): Core, Gui, Qml, Quick, QuickControls2, Network,
  WebSockets, Svg

## Build

```powershell
$env:CMAKE_PREFIX_PATH = "C:\Qt\6.12.0\msvc2022_64"
python3 scripts/generate_models.py   # chỉ cần khi đổi schema/documents.json
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DMXU_BUILD_TESTS=ON
cmake --build build --config Release
.\build\Release\MxuSlides.exe
```

### Tùy chọn phần cứng/SDK

`-DMXU_ENABLE_DECKLINK=ON -DDECKLINK_SDK_INCLUDE_DIR=<DeckLink SDK Windows>/Win/include`
bật output DeckLink. Thư mục `vendor/decklink` là SDK **macOS** (CoreFoundation)
nên không dùng được trên Windows; mặc định DeckLink là stub.

## Kiến trúc

```
src/core/generated/Models.*   103 record + 62 enum sinh từ schema/documents.json
scripts/generate_models.py    Bộ sinh model C++20 (chạy lại khi schema đổi)
src/core/Document.*           Service/cue/media + JSON (.mxuslides, schemaVersion 161)
src/core/ShowDocument.*       SlideObject CRUD + undo/redo snapshot
src/app/Models.{h,cpp}        ServiceModel, CueModel, LibraryModel cho QML
src/app/AppController.*       Điều hướng 5 màn hình, timer, settings, stage
src/api/LocalApiServer.*      REST + WebSocket, token scopes (port 6980/6981)
qml/theme/                    Theme + Icons (QtQuick.Shapes)
qml/components/               Card, Segmented, CueCard, Checkerboard, ...
qml/screens/                  Present, Edit, Stage, Library, Settings
qml/windows/                   Output windows: Presentation/Stage/Confidence + operator
                               windows Notes/Timeline/QuickSearch (Mac parity)
```

## Local API

| Route | Method | Scope | Mô tả |
|---|---|---|---|
| `/v1/ping` | GET | — | Health check |
| `/v1/status` | GET | status | Slide đang chiếu, cue, timer |
| `/v1/slides` | GET | status | Danh sách slide |
| `/v1/advance` | POST | control | Sang slide tiếp |
| `/v1/clear` | POST | control | Clear/restore output |
| `/openapi.json` | GET | — | API description |
| ws://127.0.0.1:6981 | WS | — | Event `hello` / `state` |

Token mặc định được tạo lần đầu chạy và lưu trong `QSettings` (`mxu/api/tokens`).

## Phím tắt

`Space` / `→` slide tiếp · `←` slide trước · `Ctrl+S` lưu · `Ctrl+1…5` chuyển màn hình.


## Trạng thái port

Các module macOS đã có mặt tương ứng: schema codegen, service/cue/slide/media,
scene + transition, media import + audio mixer, output manager, automation,
notes, FTS5 search, sync ledger, diagnostics và Local API. Xem
[docs/PORT-ROADMAP.md](docs/PORT-ROADMAP.md) và [docs/REMAINING.md](docs/REMAINING.md).

CI: `.github/workflows/build-windows.yml` build & test với Qt 6.12 trên Windows Server 2022.

## Ghi chú bản quyền

Mã nguồn macOS MxU Slides dùng PolyForm Shield License 1.0.0. Hãy xác nhận
bạn có quyền chuyển đổi nền tảng trước khi phân phối bản port này.


## UI check

Run `MxuSlides.exe --screenshots out` to render the five screens, then compare with `docs/ui-reference/` (see `docs/UI-PARITY.md`).
