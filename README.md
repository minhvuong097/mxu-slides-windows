# MxU Slides for Windows

Bản port Windows của **MxU Slides** (macOS), viết bằng **C++20 / Qt 6**, với
giao diện 5 màn hình theo thiết kế "macOS-style" do Claude thiết kế.

Repo này là một codebase mới, xây dựng từ các khái niệm và cấu trúc dữ liệu của
`mxu-slides-main` (Swift) — không kế thừa codebase FreeShow/ProSlides.

## Yêu cầu

- Windows 10/11, Visual Studio 2022 (MSVC, C++20)
- CMake ≥ 3.25
- Qt 6.12 (tối thiểu 6.5): Core, Gui, Qml, Quick, QuickControls2, Network,
  WebSockets, Svg

## Build

```powershell
$env:CMAKE_PREFIX_PATH = "C:\Qt\6.12.0\msvc2019_64"
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DMXU_BUILD_TESTS=ON
cmake --build build --config Release
.\build\Release\MxuSlides.exe
```

## Kiến trúc

```
src/core/Document.{h,cpp}     Mô hình service/cue/slide/media + JSON (.mxuslides, schemaVersion 161)
src/app/Models.{h,cpp}        ServiceModel, CueModel, LibraryModel cho QML
src/app/AppController.*       Điều hướng 5 màn hình, timer, settings, stage
src/api/LocalApiServer.*      REST + WebSocket, token scopes (port 6980/6981)
qml/theme/                    Theme + Icons (QtQuick.Shapes)
qml/components/               Card, Segmented, CueCard, Checkerboard, ...
qml/screens/                  Present, Edit, Stage, Library, Settings
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

## Ghi chú bản quyền

Mã nguồn macOS MxU Slides dùng PolyForm Shield License 1.0.0. Hãy xác nhận
bạn có quyền chuyển đổi nền tảng trước khi phân phối bản port này.
