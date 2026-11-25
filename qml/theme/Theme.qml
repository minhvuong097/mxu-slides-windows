pragma Singleton
import QtQuick

// Design tokens from the Claude "Service Flow (Windows, macOS-style)" mockup.
// The legacy aliases at the bottom keep the original views working while the
// MxU shell uses the new palette.
QtObject {
    // Surfaces
    readonly property color bg:             "#1c1c1e"
    readonly property color card:           "#232326"
    readonly property color inset:          "#1c1c1e"
    readonly property color hover:          "#3a3a3e"
    readonly property color surface:        "#38383c"
    readonly property color surfaceAlt:     "#2a2a2d"
    readonly property color surfaceSoft:    "#2b2b2e"
    readonly property color segmentedBg:    "#2d2d30"
    readonly property color segmentActive:  "#1b1b1d"
    readonly property color searchField:    "#2c2c30"
    readonly property color iconButton:     "#2e2e31"
    readonly property color startButton:    "#303033"
    readonly property color scrollTrack:    "#262629"
    readonly property color statusStrip:    "#26262a"
    readonly property color border:         "#3a3a3e"
    readonly property color borderSoft:     "#333333"
    readonly property color borderMid:      "#4a4a4d"

    // Text
    readonly property color text:           "#f5f5f7"
    readonly property color textDim:        "#a1a1a6"
    readonly property color textFaint:      "#8e8e93"
    readonly property color textMid:        "#b8b8bc"
    readonly property color textBright:     "#d1d1d6"
    readonly property color textIcon:       "#bdbdc2"

    // Accents
    readonly property color accent:         "#0a84ff"
    readonly property color green:          "#30d158"
    readonly property color yellow:         "#ffd60a"
    readonly property color gold:           "#ffb000"
    readonly property color goldBorder:     "#e8a300"
    readonly property color orange:         "#ff9f0a"
    readonly property color pink:           "#ff375f"
    readonly property color purple:         "#bf5af2"
    readonly property color cyan:           "#5ac8fa"
    readonly property color redClose:       "#c42b1c"
    readonly property color trafficRed:     "#ff5f57"
    readonly property color trafficYellow:  "#febc2e"
    readonly property color trafficGreen:   "#28c840"

    // Media
    readonly property color black:          "#000000"
    readonly property color checkerBase:    "#0b0b0c"
    readonly property color checkerA:       "#171719"
    readonly property color checkerB:       "#0e0e10"
    readonly property color stageTop:       "#2c2c3e"

    // Metrics
    readonly property int radius:           10
    readonly property int radiusSmall:      7
    readonly property int radiusTiny:       5
    readonly property int spacing:          10
    readonly property int sidebarWidth:     270
    readonly property int inspectorWidth:   290

    // Typography — Segoe UI is the native Windows counterpart of the
    // mockup's Inter / Segoe UI Variable stack.
    readonly property string fontFamily:    "Segoe UI"
    readonly property font bodyFont:        Qt.font({ family: fontFamily, pixelSize: 11 })
    readonly property font smallFont:       Qt.font({ family: fontFamily, pixelSize: 11 })
    readonly property font titleFont:       Qt.font({ family: fontFamily, pixelSize: 16, weight: Font.DemiBold })
    readonly property font slideFont:       Qt.font({ family: fontFamily, pixelSize: 18, weight: Font.DemiBold })

    // Legacy aliases (original ProSlides views)
    readonly property color panel:          card
    readonly property color panelAlt:       surfaceAlt
    readonly property color surfaceHover:   hover
    readonly property color blue:           accent
    readonly property color red:            pink
    readonly property color accentDim:      "#0a64c8"
}
