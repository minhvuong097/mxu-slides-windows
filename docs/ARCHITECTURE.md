# MxU Slides macOS → Windows mapping

| macOS (Swift) | Windows (C++20 / Qt 6) |
|---|---|
| `packages/schema/documents.json` (schemaVersion 161) | `src/core/Document.*` — JSON projection, cùng schemaVersion |
| `PresenterCore`: Service, ServiceItem, Presentation, Slide, MediaItem | `core::ServiceItem`, `core::Cue`, `core::Slide`, `core::MediaItem` |
| `AppModel`, `AppShell`, `RunOrderList` | `app::ServiceModel` + `PresentScreen` |
| `ServiceControls`, `ShowState` | `app::AppController::next/previous/toggleClear` |
| `SlideSceneBuilder`, `RenderEngine` (Metal) | QML `Checkerboard`/`GradientThumb`, `StageScreen` (Qt Quick RHI/D3D) |
| `LocalAPIServer` (6980) | `api::LocalApiServer` (REST 6980 + WS 6981) |
| `APITokenStore` / `APIScope` | `QSettings` token store, scopes status/control/admin |
| `AppSettingsView` / `@AppStorage` | `QSettings` key `mxu/*`, `Core.Document.settings` |
| `ServiceTimingController`, `TimersModule` | `AppController` timer rows + 1s `QTimer` |
| `OutputEngine` / `NSScreen` | `QGuiApplication::screens()` + `identifyDisplays()` |
| XPC helpers, IOSurface, CoreAudio, AVFoundation | Không dùng; kiến trúc in-process, Qt Multimedia/WASAPI khi mở rộng |

## UI tokens

- Window `#1c1c1e`, card `#232326`, border `#3a3a3e`, radius 12
- Text `#f5f5f7`, secondary `#a1a1a6`, accent `#0a84ff`
- Sections: yellow `#ffd60a`, green `#30d158`, purple `#bf5af2`, pink `#ff375f`
- Font: Segoe UI (Windows counterpart of Inter / Segoe UI Variable)
- Sidebar 270px, right rail 290px, gap 10px, padding 10px
