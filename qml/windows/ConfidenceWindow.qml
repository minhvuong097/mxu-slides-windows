import QtQuick
import QtQuick.Window
import "qrc:/qml/theme"
import "qrc:/qml/components"

// Confidence monitor for the operator — mirrors the macOS ConfidenceModule.
Window {
    id: monitor
    flags: Qt.Window | Qt.FramelessWindowHint
    screen: Qt.application.screens.length > Mxu.outputs.screenIndexFor("confidence")
            ? Qt.application.screens[Mxu.outputs.screenIndexFor("confidence")]
            : Qt.application.screens[0]
    visibility: Mxu.confidenceVisible ? Window.FullScreen : Window.Hidden
    color: "black"
    title: "MxU Slides — Confidence"

    onClosing: Mxu.setConfidenceVisible(false)

    Rectangle {
        anchors.fill: parent
        color: "black"

        Column {
            anchors.fill: parent
            anchors.margins: 32
            spacing: 14

            Row {
                width: parent.width
                Text { text: Mxu.serviceClock; color: Theme.textMid; font.pixelSize: 26; font.weight: Font.Bold }
                Item { width: parent.width - 260; height: 1 }
                Text { text: Mxu.serviceTimerText; color: Theme.green; font.pixelSize: 26; font.weight: Font.Bold }
            }

            Rectangle {
                width: parent.width
                height: (parent.height - 190) * 0.5
                radius: 10
                border.color: "white"
                border.width: 2
                color: "transparent"
                Text {
                    anchors.centerIn: parent
                    width: parent.width - 30
                    text: Mxu.currentSlideText
                    color: Theme.text
                    font.pixelSize: 34
                    font.weight: Font.Bold
                    wrapMode: Text.WordWrap
                    horizontalAlignment: Text.AlignHCenter
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: -12
                    color: Theme.textDim
                    font.pixelSize: 11
                    font.weight: Font.DemiBold
                    text: "CURRENT SLIDE"
                }
            }

            Rectangle {
                width: parent.width
                height: (parent.height - 190) * 0.35
                radius: 10
                border.color: Theme.yellow
                border.width: 2
                color: "transparent"
                Text {
                    anchors.centerIn: parent
                    width: parent.width - 30
                    text: Mxu.nextSlideText
                    color: Theme.text
                    font.pixelSize: 26
                    wrapMode: Text.WordWrap
                    horizontalAlignment: Text.AlignHCenter
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: -12
                    color: Theme.yellow
                    font.pixelSize: 11
                    font.weight: Font.DemiBold
                    text: "NEXT SLIDE"
                }
            }

            Rectangle {
                width: parent.width
                height: 44
                radius: 10
                color: Mxu.accent
                visible: Mxu.stageMessage.length > 0
                Text {
                    anchors.centerIn: parent
                    width: parent.width - 20
                    text: Mxu.stageMessage
                    color: "white"
                    font.pixelSize: 18
                    font.weight: Font.DemiBold
                    elide: Text.ElideRight
                }
            }
        }

        Rectangle {
            visible: Mxu.alerts.visible &&
                     (Mxu.alerts.active.target === "both" || Mxu.alerts.active.target === "confidence")
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
