import QtQuick
import "qrc:/qml/theme"
import "qrc:/qml/components"

Rectangle {
    id: button
    property string icon: ""
    property color iconColor: Theme.textDim
    property real iconSize: 16
    property bool highlighted: false
    signal clicked()

    width: 28; height: 24
    radius: 7
    color: area.containsMouse ? "#3a3a3e" : (highlighted ? Qt.rgba(10/255, 132/255, 1, 0.16) : "transparent")
    border.color: highlighted ? Qt.rgba(10/255, 132/255, 1, 0.4) : "transparent"
    border.width: highlighted ? 1 : 0

    AppIcon {
        anchors.centerIn: parent
        name: button.icon
        size: button.iconSize
        color: button.highlighted ? Theme.accent : button.iconColor
    }

    MouseArea {
        id: area
        anchors.fill: parent
        hoverEnabled: true
        onClicked: button.clicked()
    }
}
