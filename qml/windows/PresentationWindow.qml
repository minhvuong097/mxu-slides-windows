import QtQuick
import QtQuick.Window
import Mxu.Scene 1.0
import "qrc:/qml/theme"
import "qrc:/qml/components"

// Audience output. Opens fullscreen on the second display when available and
// renders the C++ scene through SceneView (layers, opacity, chords, transitions).
Window {
    id: output
    flags: Qt.Window | Qt.FramelessWindowHint
            | (Mxu.outputs.alwaysOnTop ? Qt.WindowStaysOnTopHint : 0)
    screen: Qt.application.screens.length > Mxu.outputs.screenIndexFor("main")
            ? Qt.application.screens[Mxu.outputs.screenIndexFor("main")]
            : Qt.application.screens[0]
    visibility: Mxu.presenting ? Window.FullScreen : Window.Hidden
    color: "black"
    title: "ProSlides — Output"

    onClosing: Mxu.setPresenting(false)

    Rectangle {
        anchors.fill: parent
        color: "black"

        Image {
            anchors.fill: parent
            source: Mxu.mediaService.backgroundUrl
            fillMode: Image.PreserveAspectCrop
            opacity: 0.35
            asynchronous: true
        }

        SceneSurface {
            anchors.fill: parent
            layers: Mxu.renderLayers
            previousLayers: Mxu.previousRenderLayers
            transitionProgress: Mxu.transition.progress
            transitionKind: Mxu.transition.kind
            background: "black"
        }

        TransitionCurtain {
            anchors.fill: parent
            curtainColor: Mxu.transition.curtainColor
            strength: Mxu.transition.curtainOpacity
            burn: Mxu.transition.kind === "filmBurn" || Mxu.transition.kind === "blurDissolve"
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 40
            visible: Mxu.chordsVisible && !Mxu.outputCleared
            text: Mxu.currentChord
            color: Theme.yellow
            font.pixelSize: 32
            font.weight: Font.Bold
        }

        Text {
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 32
            visible: !Mxu.outputCleared
            text: Mxu.currentSlideName
            color: Theme.textFaint
            font.pixelSize: 18
        }

        Text {
            anchors.centerIn: parent
            visible: Mxu.outputCleared
            text: "OUTPUT CLEARED"
            color: Theme.textFaint
            font.pixelSize: 28
            font.weight: Font.DemiBold
            font.letterSpacing: 4
        }

        Rectangle {
            visible: Mxu.alerts.visible &&
                     (Mxu.alerts.active.target === "both" || Mxu.alerts.active.target === "audience")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 40
            width: parent.width * 0.8
            height: 64
            radius: 10
            color: Theme.pink
            Text {
                anchors.centerIn: parent
                width: parent.width - 24
                text: Mxu.alerts.active.text || ""
                color: "white"
                font.pixelSize: 22
                font.weight: Font.Bold
                elide: Text.ElideRight
            }
            MouseArea { anchors.fill: parent; onClicked: Mxu.alerts.dismiss() }
        }
    }
}
