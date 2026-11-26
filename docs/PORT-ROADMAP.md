# Lộ trình port MxU Slides macOS → Windows

Số liệu đo từ `mxu-slides-main`: **251.796 dòng code**, **1.048 file Swift**
(`apps/mac/Sources`: 93.058 dòng/198 file; `apps/mac/Packages`: 145.912 dòng/843 file,
gồm cả tests; helpers: 637 dòng). Một bản port
"ngang chức năng" không thể làm trong một bước; tài liệu này chia công việc
theo package và xác định cái nào đã có, cái nào cần làm tiếp.

## Trạng thái hiện tại

| Package macOS | Trạng thái Windows |
|---|---|
| UI shell / AppShell / ModeSwitcher | ✅ `qml/main.qml` + 5 screens |
| Service outline + cue cards | ✅ demo data, `ServiceModel` / `CueModel` |
| LocalAPI | ✅ 12 routes + WS + scoped tokens; Bonjour/follow chưa có |
| Document schema | ✅ `scripts/generate_models.py` → 103 record / 62 enum từ `schema/documents.json` |
| PresenterCore (Automerge, SQLite/FTS5) | ❌ |
| RenderEngine (Metal) | ⚠️ Scene model + transitions; RHI blend/mask chưa có |
| SlideScene / SlideEditorModel | ⚠️ `core::ShowDocument` + SlideObject/undo/redo; renderer đơn giản |
| MediaEngine / AudioEngine | ⚠️ Media import/thumbnails + Qt Multimedia mixer; video frame grab & multitrack chưa có |
| OutputEngine / NDI / DeckLink / Syphon | ⚠️ OutputManager + SDK stubs; recorder/Syphon chưa có |
| StreamEngine / MIDI / Scheduler / Notes | ⚠️ Automation + notes + lyric import; MIDI hardware & streaming chưa có |
| ProImport / PPTXImport | ❌ |
| Diagnostics / perf | ❌ |

## Phase 1 — Nền tảng dữ liệu và editor (P0) — ĐÃ LÀM

- ✅ Codegen C++20 từ `schema/documents.json` (103 record, 62 enum, ~7.200 dòng).
- ✅ `SlideObject` với geometry, textStyle, chords, animationSteps, visibility.
- ✅ `ShowDocument`: thêm/xoá/sửa/duplicate/move slide & object, undo/redo snapshot JSON.
- ✅ Edit screen binds `Mxu.slides`, `Mxu.slideObjects`, `Mxu.selectedObject`; kéo object, sửa X/Y/W/H, text, font, màu, animation.
- ✅ Save/load `.mxuslides` chứa slides + objects.

Còn lại của Phase 1: transition/layer rendering và scene rules đầy đủ (đẩy sang Phase 2).

- Đổi `packages/schema/documents.json` → codegen C++20 structs + JSON codec
  (hiện đang viết tay trong `src/core/Document.*`).
- `SlideObject` (text/media/shape/liveInput): geometry, styleRuns, chords,
  animationSteps, visibility → `core::SlideObject`.
- `ShowState` (liveSlide, lastSlide, overlays, clear scope) → `app::ShowState`.
- `SlideEditorModel`: selection, drag/resize, commit/undo queue.
- QML `SceneCanvas` + inspector bind thật vào object model.

## Phase 2 — Output renderer (P0) — ĐÃ LÀM (phần lõi)

- ✅ `core::SceneModel`: RenderScene/RenderLayer/RenderItem, layer kinds, ShowState.
- ✅ `SceneTransitionEngine`: cut/dissolve/fadeBlack/White/Color/blurDissolve/filmBurn + curtain.
- ✅ `SceneView.qml`: render layers, opacity, chord, clear; dùng trong PresentationWindow & StageOutputWindow.
- ⚠️ Chưa có: blend mode shader, mask, per-screen output preset (Phase 4).

Kiến trúc gốc của phase này:

- Scene model (`RenderScene`, `RenderLayer`, `RenderItem`, `LayerKind`).
- Qt Quick/RHI scene graph thay cho `Text` thuần: layer ordering, opacity,
  blend, mask, scale mode.
- `SceneTransitionEngine`: cut/dissolve/fadeBlack/fadeWhite/blurDissolve.
- Confidence layout builder + stage layout variants.

## Phase 3 — Media & Audio (P1) — ĐÃ LÀM (phần lõi)

- ✅ `MediaService`: import file/folder, QImage thumbnails, file size/type, service flow add, background.
- ✅ Library screen dùng thumbnail thật + `FileDialog` Import.
- ✅ `AudioService`: QMediaPlayer/QAudioOutput mixer, mute/solo/volume, play/stop; Settings › Audio pane.
- ⚠️ Chưa có: FFmpeg video decode & frame grab, 2-deck crossfade, playlist, multitrack stems, camera/live input.

Kiến trúc gốc của phase này:

- FFmpeg decode (D3D11VA/DXVA2) → `QVideoSink`/RHI texture; thumbnailer.
- Media library import, file hash, in/out points, playRate.
- WASAPI audio engine: 2 decks, crossfade, playlist queue, mixer.
- Multitrack stems (từ `MultitrackEngine`) — có thể làm sau.

## Phase 4 — Outputs & APIs (P1) — ĐÃ LÀM (phần lõi)

- ✅ `OutputManager`: QScreen topology, per-role assignment, identify, persistence.
- ✅ Settings Outputs dùng màn hình thật & gán role.
- ✅ NDI/DeckLink backend stubs với build options (`MXU_ENABLE_NDI`, `MXU_ENABLE_DECKLINK`).
- ✅ LocalAPI 12 routes: ping/status/slides/advance/clear/goToSlide/timers/present/stop/clearLayer/tokens/openapi + WS.
- ⚠️ Chưa có: Bonjour/mDNS, follow pairing, recorder, SDK implementation thật.

Kiến trúc gốc của phase này:

- `OutputManager`: screen map, placeholder screens, per-screen preset.
- NDI sender (SDK) + DeckLink SDK (đã có header vendor trong repo Mac).
- Recorder (Media Foundation hoặc FFmpeg muxer).
- LocalAPI đầy đủ: ~40 routes, Bonjour/mDNS, follow pairing, scope tokens,
  Keychain → DPAPI/Credential Manager.

## Phase 5 — Tự động hoá & nội dung (P2) — ĐÃ LÀM (phần lõi)

- ✅ `AutomationService`: triggers (key/MIDI mapping), scheduler, timecode display.
- ✅ `NotesService`: NoteBlock JSON in document, add/update/link slide.
- ✅ Lyric import (stanza → slides); ProPresenter/PPTX stubs rõ ràng.
- ⚠️ Chưa có: MIDI hardware in/out, MTC/LTC decode, full note rich text, ProPresenter protobuf, PPTX parser.

Kiến trúc gốc của phase này:

- MIDI in/out, MTC/LTC timecode, keyboard shortcut map.
- Scheduler, combos/control boards, action combos.
- Notes engine (`NoteDocument`, `NoteBlock`, live slide update detection).
- Song map, presentation timeline, arrangements.
- ProPresenter/PPTX import, "Make Slides" lyric generator.

## Phase 6 — Chất lượng (P2)

- SQLite FTS5 search, CRDT sync ledger.
- Diagnostics, `MainPassMeter`, hitch report, perf scripts.

## Nguyên tắc port

1. **Schema làm nguồn chân lý**: mọi field mới phải optional để document cũ decode được.
2. **Giữ contract LocalAPI/OpenAPI** giống Mac để remote app dùng lại.
3. **Thay thế nền tảng, giữ logic**: DSP, transition timing, scene rules,
   visibility rules là code thuần, port được gần 1-1; chỉ thay Metal/AVFoundation/
   CoreAudio/AppKit bằng RHI/FFmpeg/WASAPI/QML.
4. **Test đối chiếu**: dùng `Tests/` của Swift package làm behavioural spec.
