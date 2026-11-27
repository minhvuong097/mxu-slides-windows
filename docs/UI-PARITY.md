# UI parity: Claude mockup vs. QML

`docs/ui-reference/*.png` are the five screens of the Claude "Service Flow
(Windows, macOS-style)" mockup (1280x840 / 1280x800).

## How to get the QML renders to compare

```
MxuSlides.exe --screenshots out        # writes 01-present.png ... 05-library.png
```

CI does the same (step "Render the five screens") and uploads the artifact
`ProSlides-UI-screenshots`. Compare each `out/NN-*.png` with
`docs/ui-reference/NN-*.png`.

## Screen map

| # | Mockup | QML screen | Notes |
|---|--------|------------|-------|
| 1 | Present (Service Flow) | `qml/screens/PresentScreen.qml` | 3 columns 270 / flex / 290; top row has traffic lights, sidebar, bell, sync |
| 2 | Edit | `qml/screens/EditScreen.qml` | Toolbar T/shape/image/play, canvas, Inspector |
| 3 | Stage | `qml/screens/StageScreen.qml` | Extra "Open/Close Stage" pill is functional (not in the mockup) |
| 4 | Settings | `qml/screens/SettingsScreen.qml` | Outputs pane; colored nav icons |
| 5 | Library | `qml/screens/LibraryScreen.qml` | Early mockup layout (sidebar list + Details) |

## Tokens
`qml/theme/Theme.qml` holds the mockup palette; panels use `Theme.card`
(#232326), radius 10, base text 11-12 px. Panel headers are 12 px DemiBold.
