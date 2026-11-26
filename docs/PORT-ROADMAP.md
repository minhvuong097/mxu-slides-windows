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
| LocalAPI (tối giản) | ✅ REST + WS + scoped token |
| Document schema | ⚠️ JSON projection (`schemaVersion 161`), chưa có codegen |
| PresenterCore (Automerge, SQLite/FTS5) | ❌ |
| RenderEngine (Metal) | ❌ |
| SlideScene / SlideEditorModel | ❌ |
| MediaEngine / AudioEngine | ❌ |
| OutputEngine / NDI / DeckLink / Syphon | ❌ |
| StreamEngine / MIDI / Scheduler / Notes | ❌ |
| ProImport / PPTXImport | ❌ |
| Diagnostics / perf | ❌ |

## Phase 1 — Nền tảng dữ liệu và editor (P0)

Mục tiêu: sửa được slide thật, lưu được show thật.

- Đổi `packages/schema/documents.json` → codegen C++20 structs + JSON codec
  (hiện đang viết tay trong `src/core/Document.*`).
- `SlideObject` (text/media/shape/liveInput): geometry, styleRuns, chords,
  animationSteps, visibility → `core::SlideObject`.
- `ShowState` (liveSlide, lastSlide, overlays, clear scope) → `app::ShowState`.
- `SlideEditorModel`: selection, drag/resize, commit/undo queue.
- QML `SceneCanvas` + inspector bind thật vào object model.

## Phase 2 — Output renderer (P0)

- Scene model (`RenderScene`, `RenderLayer`, `RenderItem`, `LayerKind`).
- Qt Quick/RHI scene graph thay cho `Text` thuần: layer ordering, opacity,
  blend, mask, scale mode.
- `SceneTransitionEngine`: cut/dissolve/fadeBlack/fadeWhite/blurDissolve.
- Confidence layout builder + stage layout variants.

## Phase 3 — Media & Audio (P1)

- FFmpeg decode (D3D11VA/DXVA2) → `QVideoSink`/RHI texture; thumbnailer.
- Media library import, file hash, in/out points, playRate.
- WASAPI audio engine: 2 decks, crossfade, playlist queue, mixer.
- Multitrack stems (từ `MultitrackEngine`) — có thể làm sau.

## Phase 4 — Outputs & APIs (P1)

- `OutputManager`: screen map, placeholder screens, per-screen preset.
- NDI sender (SDK) + DeckLink SDK (đã có header vendor trong repo Mac).
- Recorder (Media Foundation hoặc FFmpeg muxer).
- LocalAPI đầy đủ: ~40 routes, Bonjour/mDNS, follow pairing, scope tokens,
  Keychain → DPAPI/Credential Manager.

## Phase 5 — Tự động hoá & nội dung (P2)

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
