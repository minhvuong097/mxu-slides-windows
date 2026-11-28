import QtQuick
import QtQuick.Window
import "qrc:/qml/theme"
import "qrc:/qml/components"

// Screen Configuration window (Mac "Screen Configuration" / outputs window):
// operator surface for the display topology — screens, role assignments and
// output presets.

Window {
    id: screenConfiguration
    width: 1080
    height: 680
    visible: false
    flags: Qt.Window | Qt.FramelessWindowHint
            | (Mxu.outputs.alwaysOnTop ? Qt.WindowStaysOnTopHint : 0)

    function open() { visible = true }
    function hide() { visible = false }

    Rectangle {
        anchors.fill: parent
        color: Theme.card
        Column {
            anchors.fill: parent
            anchors.margins: 16
            spacing: 8

            Text {
                text: "Screen Configuration"
                color: Theme.text
                font.pixelSize: 18
                font.weight: Font.DemiBold
            }

            Text { text: "SCREENS"; width: parent.width; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold }
            Repeater {
                model: Mxu.outputs.screens
                delegate: Rectangle {
                    id: row
                    width: parent.width
                    height: 48
                    radius: 10
                    color: "#2c2c30"
                    Row {
                        anchors.fill: parent
                        anchors.leftMargin: 12
                        anchors.rightMargin: 12
                        spacing: 8
                        Column {
                            width: parent.width - 100
                            Text { text: modelData.name; color: Theme.text; font.pixelSize: 13; font.weight: Font.Bold; elide: Text.ElideRight }
                            Text { text: modelData.geometry; color: Theme.textDim; font.pixelSize: 11; elide: Text.ElideRight }
                        }
                        Rectangle {
                            width: 90
                            height: 26
                            radius: 8
                            color: Theme.accent
                            Text { anchors.centerIn: parent; text: "Stage"; color: "white"; font.pixelSize: 11; font.weight: Font.Bold }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.outputs.assign("stage", modelData.index) }
                        }
                    }
                }
            }
            Rectangle { width: parent.width; height: 1; color: "#333" }

            Text { text: "PRESETS"; width: parent.width; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold }
            Repeater {
                model: Mxu.outputPresets.presets
                delegate: Rectangle {
                    width: parent.width
                    height: 48
                    radius: 10
                    color: "#2c2c30"
                    Row {
                        anchors.centerIn: parent
                        spacing: 8
                        Column {
                            width: parent.width - 110
                            Text { text: modelData.name; color: Theme.text; font.pixelSize: 13; font.weight: Font.Bold; elide: Text.ElideRight }
                            Text { text: modelData.value; color: Theme.textDim; font.pixelSize: 11; elide: Text.ElideRight }
                        }
                        Rectangle {
                            width: 90
                            height: 26
                            radius: 8
                            color: Theme.accent
                            Text { anchors.centerIn: parent; text: "Apply"; color: "white"; font.pixelSize: 11; font.weight: Font.Bold }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.outputPresets.apply(modelData.id) }
                        }
                    }
                }
            }
        }
    }
}
