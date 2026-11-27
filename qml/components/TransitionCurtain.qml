import QtQuick

// Transition curtain drawn with plain Qt Quick items.
//
// The previous version used a ShaderEffect with inline GLSL source, which Qt 6
// rejects (shaders must be precompiled .qsb files), so the curtain never drew.
// For "burn" a coarse dissolve grid is used instead of a noise shader.
Item {
    id: curtain
    property color curtainColor: "black"
    property real strength: 0
    property bool burn: false

    readonly property real effective: Math.max(0, Math.min(1, strength))

    // Smooth wash
    Rectangle {
        anchors.fill: parent
        visible: !curtain.burn
        color: curtain.curtainColor
        opacity: curtain.curtainColor.a * curtain.effective
    }

    // Burn: blocky dissolve whose cells appear in a pseudo-random order
    Grid {
        id: grid
        anchors.fill: parent
        visible: curtain.burn
        readonly property int cols: 32
        readonly property int rows: 18
        columns: cols
        Repeater {
            model: grid.cols * grid.rows
            delegate: Rectangle {
                required property int index
                width: grid.width / grid.cols
                height: grid.height / grid.rows
                color: curtain.curtainColor
                // deterministic per-cell threshold in [0, 1)
                readonly property real threshold: ((index * 2654435761) % 4294967296) / 4294967296
                // 0 at strength 0, fully covered at strength 1, smoothstep in between
                readonly property real t: Math.max(0, Math.min(1, (curtain.effective - threshold * 0.6) / 0.4))
                opacity: curtain.curtainColor.a * t * t * (3 - 2 * t)
            }
        }
    }
}
