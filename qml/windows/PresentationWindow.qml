import QtQuick
import QtQuick.Window
import "qrc:/qml/theme"
import "qrc:/qml/components"

// Audience output. Opens fullscreen on the second display when available and
// renders the C++ scene through SceneView (layers, opacity, chords, transitions).
Window {
    id: output
    flags: Qt.Window | Qt.FramelessWindowHint
    screen: Qt.application.screens.length > 1
            ? Qt.application.screens[1] : Qt.application.screens[0]
    visibility: Mxu.presenting ? Window.FullScreen : Window.Hidden
    color: "black"
    title: "MxU Slides — Output"

    onClosing: Mxu.setPresenting(false)

    Rectangle {
        anchors.fill: parent
        color: "black"

        SceneView {
            anchors.fill: parent
            cleared: Mxu.showState.isCleared("slide")
        }

        Rectangle {
            anchors.fill: parent
            color: Mxu.transition.curtainColor
            opacity: Mxu.transition.curtainOpacity
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
    }
}
