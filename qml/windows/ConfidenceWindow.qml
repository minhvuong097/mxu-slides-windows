import QtQuick
import QtQuick.Window
import "qrc:/qml/theme"
import "qrc:/qml/components"

// Confidence monitor for the operator — mirrors the macOS ConfidenceModule.
Window {
    id: monitor
    flags: Qt.Window | Qt.FramelessWindowHint
            | (Mxu.outputs.alwaysOnTop ? Qt.WindowStaysOnTopHint : 0)
    screen: Qt.application.screens.length > Mxu.outputs.screenIndexFor("confidence")
            ? Qt.application.screens[Mxu.outputs.screenIndexFor("confidence")]
            : Qt.application.screens[0]
    visibility: Mxu.confidenceVisible ? Window.FullScreen : Window.Hidden
    color: "black"
    title: "ProSlides — Confidence"

    onClosing: Mxu.setConfidenceVisible(false)

    Rectangle {
        anchors.fill: parent
        color: "black"

        Column {
            anchors.fill: parent
            anchors.margins: 32
            spacing: 14

            Repeater {
                model: Mxu.confidenceLayout.nodes
                delegate: Rectangle {
                    width: parent.width
                    height: modelData.source === "currentSlide" || modelData.source === "nextSlide"
                            ? (parent.height - 120) / 2 : 70
                    radius: 12
                    border.color: modelData.source === "nextSlide" ? Theme.yellow : "#ffffff"
                    border.width: 2
                    color: "transparent"
                    Text {
                        anchors.centerIn: parent
                        width: parent.width - 32
                        text: {
                            if (modelData.source === "clock") return Mxu.serviceClock
                            if (modelData.source === "timer") return Mxu.serviceTimerText
                            if (modelData.source === "stageMessage") return Mxu.stageMessage
                            if (modelData.source === "currentSlide") return Mxu.currentSlideText
                            if (modelData.source === "nextSlide") return Mxu.nextSlideText
                            return Mxu.currentSlideName
                        }
                        color: modelData.source === "clock" || modelData.source === "timer" ? Theme.green : Theme.text
                        font.pixelSize: modelData.source === "currentSlide" ? 32
                                        : (modelData.source === "nextSlide" ? 24 : 26)
                        font.weight: Font.Bold
                        wrapMode: Text.WordWrap
                        horizontalAlignment: Text.AlignHCenter
                    }
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top
                        anchors.topMargin: -12
                        text: modelData.title
                        color: Theme.textDim
                        font.pixelSize: 11
                        font.weight: Font.DemiBold
                    }
                }
            }
        }
    }
}
