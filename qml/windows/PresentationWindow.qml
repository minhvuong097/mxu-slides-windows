import QtQuick
import QtQuick.Window
import "qrc:/qml/theme"

// Audience output. Opens fullscreen on the second display when available.
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

        Image {
            anchors.fill: parent
            source: Mxu.libraryModel.selectedItem.from ? "" : ""
            visible: false
        }

        Column {
            anchors.centerIn: parent
            width: parent.width * 0.86
            spacing: 36

            Text {
                id: chord
                anchors.horizontalCenter: parent.horizontalCenter
                visible: Mxu.chordsVisible && !Mxu.outputCleared
                text: Mxu.currentChord
                color: Theme.yellow
                font.pixelSize: 34
                font.weight: Font.Bold
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width
                visible: !Mxu.outputCleared
                text: Mxu.currentSlideText
                color: Theme.text
                font.pixelSize: 64
                font.weight: Font.Bold
                lineHeight: 1.35
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
            }
        }

        Text {
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 32
            visible: !Mxu.outputCleared
            text: Mxu.cueModel.currentCue.title || ""
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
