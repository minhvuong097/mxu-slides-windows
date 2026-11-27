import QtQuick
import QtQuick.Window
import Mxu.Scene 1.0
import "qrc:/qml/theme"
import "qrc:/qml/components"

// Preview window (Mac PreviewWindow) — renders the current scene for a target
// layout before it goes live on the audience output.
Window {
    id: preview
    width: 640
    height: 380
    visible: false
    flags: Qt.Window | Qt.FramelessWindowHint
            | (Mxu.outputs.alwaysOnTop ? Qt.WindowStaysOnTopHint : 0)

    Rectangle {
        anchors.fill: parent
        color: "black"

        SceneSurface {
            anchors.fill: parent
            layers: Mxu.renderLayers
            previousLayers: Mxu.previousRenderLayers
            transitionProgress: Mxu.transition.progress
            transitionKind: Mxu.transition.kind
            background: "black"
        }

        Text {
            anchors.top: parent.top
            anchors.topMargin: 16
            anchors.right: parent.right
            anchors.rightMargin: 16
            text: Mxu.currentSlideName
            color: Theme.textDim
            font.pixelSize: 16
            font.weight: Font.DemiBold
            elide: Text.ElideRight
            horizontalAlignment: Text.AlignRight
        }
    }
}
