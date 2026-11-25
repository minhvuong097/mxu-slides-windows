import QtQuick
import QtQuick.Window
import "qrc:/qml/theme"

// Musician stage display with clock, section timer, current/next slide and message.
Window {
    id: stage
    flags: Qt.Window | Qt.FramelessWindowHint
    screen: Qt.application.screens.length > 2
            ? Qt.application.screens[2] : Qt.application.screens[0]
    visibility: Mxu.stageOutputVisible ? Window.FullScreen : Window.Hidden
    color: "black"
    title: "MxU Slides — Stage"

    onClosing: Mxu.setStageOutputVisible(false)

    Rectangle {
        anchors.fill: parent
        color: "black"

        Column {
            anchors.fill: parent
            anchors.margins: 36
            spacing: 22

            Row {
                width: parent.width
                Text {
                    visible: Mxu.clockVisible
                    text: Mxu.serviceClock
                    color: Theme.text
                    font.pixelSize: 44
                    font.weight: Font.Bold
                }
                Item { width: parent.width - 360; height: 1 }
                Text {
                    visible: Mxu.sectionTimerVisible
                    text: Mxu.serviceTimerText
                    color: Theme.green
                    font.pixelSize: 44
                    font.weight: Font.Bold
                }
            }

            Rectangle {
                width: parent.width
                height: (parent.height - 200) * 0.55
                radius: 12
                border.color: "white"
                border.width: 3
                color: "transparent"
                Text {
                    anchors.centerIn: parent
                    width: parent.width - 40
                    text: Mxu.currentSlideText
                    color: Theme.text
                    font.pixelSize: Mxu.lyricsFontSize * 1.4
                    font.weight: Font.Bold
                    lineHeight: 1.4
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WordWrap
                }
                Text {
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.margins: 18
                    visible: Mxu.chordsVisible
                    text: Mxu.currentChord
                    color: Theme.yellow
                    font.pixelSize: 28
                    font.weight: Font.Bold
                }
            }

            Rectangle {
                width: parent.width
                height: 110
                radius: 12
                border.color: Theme.yellow
                border.width: 3
                color: "transparent"
                Text {
                    anchors.centerIn: parent
                    width: parent.width - 32
                    text: Mxu.nextSlideText
                    color: Theme.text
                    font.pixelSize: 28
                    font.weight: Font.DemiBold
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            Rectangle {
                width: parent.width
                height: 56
                radius: 12
                color: Theme.accent
                visible: Mxu.stageMessage.length > 0
                Text {
                    anchors.centerIn: parent
                    width: parent.width - 28
                    text: "Message: " + Mxu.stageMessage
                    color: "white"
                    font.pixelSize: 22
                    font.weight: Font.DemiBold
                    elide: Text.ElideRight
                }
            }
        }
    }
}
