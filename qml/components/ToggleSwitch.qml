import QtQuick
import "qrc:/qml/theme"

Rectangle {
    id: toggle
    property bool checked: false
    signal toggled(bool value)

    width: 34; height: 20
    radius: 99
    color: checked ? Theme.green : "#48484c"

    Rectangle {
        width: 16; height: 16
        radius: 8
        color: "white"
        x: toggle.checked ? 16 : 2
        y: 2
        Behavior on x { NumberAnimation { duration: 120 } }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            toggle.checked = !toggle.checked
            toggle.toggled(toggle.checked)
        }
    }
}
