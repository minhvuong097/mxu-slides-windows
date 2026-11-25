import QtQuick
import "qrc:/qml/theme"
import "qrc:/qml/components"

Rectangle {
    id: tool
    property string text: ""
    property string icon: ""
    property real iconSize: 16
    signal clicked()

    width: 34; height: 34
    radius: 8
    color: area.containsMouse ? "#48484c" : Theme.surface

    Text {
        anchors.centerIn: parent
        visible: tool.text !== ""
        text: tool.text
        color: "white"
        font.pixelSize: 15
        font.weight: Font.Bold
    }
    AppIcon {
        anchors.centerIn: parent
        visible: tool.icon !== ""
        name: tool.icon
        size: tool.iconSize
        color: "white"
    }

    MouseArea {
        id: area
        anchors.fill: parent
        hoverEnabled: true
        onClicked: tool.clicked()
    }
}
