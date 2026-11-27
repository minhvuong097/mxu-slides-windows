import QtQuick
import QtQuick.Controls
import QtQuick.Window
import "qrc:/qml/theme"

// Operator service controls window (Mac ServiceControlsWindow): module rail
// over the selected module surface. Kickoff hosts the Timers module surface.
Window {
    id: serviceControls
    width: 420
    height: 520
    visible: false
    flags: Qt.Window | Qt.FramelessWindowHint
            | (Mxu.outputs.alwaysOnTop ? Qt.WindowStaysOnTopHint : 0)

    property string module: "timers"

    function modeLabel(mode) {
        if (mode === "countUp")
            return "Count-up"
        if (mode === "countdownToTime")
            return "Countdown to time"
        return "Countdown"
    }

    Rectangle {
        anchors.fill: parent
        color: Theme.card

        Column {
            anchors.fill: parent
            anchors.margins: 16
            spacing: 12

            Text {
                id: header
                text: "Service Controls"
                color: Theme.text
                font.pixelSize: 18
                font.weight: Font.DemiBold
            }

            Row {
                id: rail
                width: parent.width
                height: 40
                spacing: 8

                Repeater {
                    model: [
                        "timers",
                        "alerts",
                        "combos",
                        "confidence",
                        "outputs",
                        "timecode"
                    ]
                    delegate: Rectangle {
                        id: railItem
                        width: 64
                        height: 40
                        radius: 10
                        color: serviceControls.module === modelData ? Theme.accent : Theme.surface
                        Text {
                            anchors.centerIn: parent
                            text: modelData
                            color: serviceControls.module === modelData ? "white" : Theme.text
                            font.pixelSize: 11
                            font.weight: Font.Bold
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: serviceControls.module = modelData
                        }
                    }
                }
            }

            Loader {
                id: moduleLoader
                anchors.top: header.bottom
                anchors.bottom: parent.bottom
                width: parent.width
                sourceComponent: module === "timers" ? timersModule : null
            }
        }
    }

    Component {
        id: timersModule
        Rectangle {
            width: moduleLoader.width
            height: moduleLoader.height
            color: "transparent"

            Column {
                anchors.fill: parent
                anchors.margins: 0
                spacing: 8

                Repeater {
                    model: Mxu.timerBoard.timers
                    delegate: Rectangle {
                        id: row
                        width: parent.width
                        height: 56
                        radius: 10
                        color: "#2c2c30"

                        Row {
                            anchors.fill: parent
                            anchors.leftMargin: 12
                            anchors.rightMargin: 12
                            spacing: 8

                            Column {
                                width: parent.width - 132
                                Text {
                                    text: modelData.name
                                    color: Theme.text
                                    font.pixelSize: 13
                                    font.weight: Font.Bold
                                    elide: Text.ElideRight
                                }
                                Text {
                                    text: modeLabel(modelData.mode) + " · " + (modelData.remaining / 60).toFixed(0) + " min"
                                    color: Theme.textDim
                                    font.pixelSize: 11
                                }
                            }

                            Rectangle {
                                width: 40
                                height: 28
                                radius: 8
                                color: Theme.accent
                                Text { anchors.centerIn: parent; text: modelData.running ? "Pause" : "Start"; color: "white"; font.pixelSize: 11; font.weight: Font.Bold }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: modelData.running ? Mxu.timerBoard.pause(modelData.id) : Mxu.timerBoard.start(modelData.id)
                                }
                            }
                            Rectangle {
                                width: 40
                                height: 28
                                radius: 8
                                color: Theme.surface
                                Text { anchors.centerIn: parent; text: "Reset"; color: Theme.text; font.pixelSize: 11; font.weight: Font.Bold }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: Mxu.timerBoard.reset(modelData.id)
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
