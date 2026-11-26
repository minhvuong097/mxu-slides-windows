import QtQuick
import QtQuick.Controls
import "qrc:/qml/theme"

Rectangle {
    id: popup
    width: 340
    height: 190
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
        Text { text: "Click a row to change the display"; color: Theme.textDim; font.pixelSize: 10 }
    }

    function open() { visible = true }
    function hide() { visible = false }
}
