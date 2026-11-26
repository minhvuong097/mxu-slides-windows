import QtQuick
import QtQuick.Controls
import "qrc:/qml/theme"

Rectangle {
    id: popup
    width: 340
    height: 260
    radius: 12
    color: Theme.card
    border.color: "#3a3a3e"
    border.width: 1
    visible: false
    z: 19
    signal closeRequested()

    Column {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 6
        Text { text: "Output profile — Default · All"; color: Theme.text; font.pixelSize: 12; font.weight: Font.DemiBold }
        SettingField {
            width: parent.width; label: "Main output"; value: Mxu.outputs.assignment("main")
            onClicked: Mxu.outputs.cycleScreen("main")
        }
        SettingField {
            width: parent.width; label: "Stage display"; value: Mxu.outputs.assignment("stage")
            onClicked: Mxu.outputs.cycleScreen("stage")
        }
        SettingField {
            width: parent.width; label: "Confidence"; value: Mxu.confidenceVisible ? "On" : "Off"
            onClicked: Mxu.toggleConfidence()
        }
        Rectangle { width: parent.width; height: 1; color: "#333" }
        Text { text: "PRESETS"; color: Theme.textDim; font.pixelSize: 9; font.weight: Font.Bold; font.letterSpacing: 0.72 }
        Repeater {
            model: Mxu.outputPresets.presets
            delegate: Rectangle {
                width: parent.width
                height: 26
                radius: 6
                color: "transparent"
                Text {
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    text: modelData.name
                    color: Theme.text
                    font.pixelSize: 11
                }
                MouseArea { anchors.fill: parent; onClicked: Mxu.outputPresets.apply(modelData.id) }
            }
        }
        Rectangle {
            width: parent.width; height: 26; radius: 7; color: Theme.accent
            Text { anchors.centerIn: parent; text: "Save current as preset"; color: "white"; font.pixelSize: 11; font.weight: Font.DemiBold }
            MouseArea { anchors.fill: parent; onClicked: Mxu.outputPresets.save("Preset " + (Mxu.outputPresets.presets.length + 1), true, true) }
        }
    }

    function open() { visible = true }
    function hide() { visible = false }
}
