import QtQuick
import QtQuick.Window
import "qrc:/qml/theme"
import "qrc:/qml/components"

// Musician stage display with clock, section timer, current/next slide and message.
Window {
    id: stage
    flags: Qt.Window | Qt.FramelessWindowHint
            | (Mxu.outputs.alwaysOnTop ? Qt.WindowStaysOnTopHint : 0)
    screen: Qt.application.screens.length > Mxu.outputs.screenIndexFor("stage")
            ? Qt.application.screens[Mxu.outputs.screenIndexFor("stage")]
            : Qt.application.screens[0]
    visibility: Mxu.stageOutputVisible ? Window.FullScreen : Window.Hidden
    color: "black"
    title: "ProSlides — Stage"

    onClosing: Mxu.setStageOutputVisible(false)

    Rectangle {
        anchors.fill: parent
        color: "black"

        Column {
            anchors.fill: parent
            anchors.margins: 36
            spacing: 22

            property bool lyricsLayout: Mxu.stageLayout === "Lyrics + Next" || Mxu.stageLayout === "Chords"
            property bool timerLayout: Mxu.stageLayout === "Timer only"
            property bool messageLayout: Mxu.stageLayout === "Message wall"

            Row {
                width: parent.width
                visible: parent.lyricsLayout || parent.timerLayout
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
                visible: parent.lyricsLayout
                width: parent.width
                height: (parent.height - 200) * 0.55
                radius: 12
                border.color: "white"
                border.width: 3
                color: "transparent"
                SceneView {
                    anchors.fill: parent
                    anchors.margins: 12
                    cleared: false
                }
                Text {
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.margins: 18
                    visible: Mxu.chordsVisible
                    text: Mxu.currentChord
                    color: Theme.yellow
                    font.pixelSize: Mxu.stageLayout === "Chords" ? 56 : 28
                    font.weight: Font.Bold
                }
            }

            Rectangle {
                visible: parent.lyricsLayout && Mxu.stageLayout === "Lyrics + Next"
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
                visible: parent.timerLayout
                width: parent.width
                height: parent.height - 160
                radius: 16
                color: "transparent"
                Column {
                    anchors.centerIn: parent
                    spacing: 20
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: Mxu.serviceTimerText
                        color: Theme.green
                        font.pixelSize: 160
                        font.weight: Font.Bold
                    }
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: Mxu.serviceClock
                        color: Theme.text
                        font.pixelSize: 48
                    }
                }
            }

            Rectangle {
                visible: parent.messageLayout && Mxu.stageMessage.length > 0
                width: parent.width
                height: parent.height - 160
                radius: 16
                color: Mxu.accent
                Text {
                    anchors.centerIn: parent
                    width: parent.width - 60
                    text: Mxu.stageMessage
                    color: "white"
                    font.pixelSize: 72
                    font.weight: Font.Bold
                    wrapMode: Text.WordWrap
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            Rectangle {
                width: parent.width
                height: 56
                radius: 12
                color: Theme.accent
                visible: Mxu.stageMessage.length > 0 && !parent.messageLayout
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
