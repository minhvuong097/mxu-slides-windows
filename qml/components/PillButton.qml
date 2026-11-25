import QtQuick
import "qrc:/qml/theme"
import "qrc:/qml/components"

Rectangle {
    id: pill
    property string text: ""
    property string icon: ""
    property real iconSize: 15
    property bool success: false
    property bool active: false
    property color pillColor: success ? Qt.rgba(48/255, 209/255, 88/255, 0.16)
                                      : (active ? "#0a84ff" : Theme.surfaceSoft)
    property color pillBorder: success ? Qt.rgba(48/255, 209/255, 88/255, 0.32)
                                       : (active ? Theme.accent : "#3c3c40")
    property color pillText: success || active ? Theme.green : Theme.textDim
    signal clicked()

    implicitWidth: content.implicitWidth + 18
    implicitHeight: 24
    radius: 99
    color: area.containsMouse ? (success ? Qt.rgba(48/255, 209/255, 88/255, 0.24) : "#38383c") : pillColor
    border.color: pillBorder
    border.width: 1

    Row {
        id: content
        anchors.centerIn: parent
        spacing: 5
        AppIcon {
            visible: pill.icon !== ""
            name: pill.icon
            size: pill.iconSize
            color: pill.pillText
        }
        Text {
            visible: pill.text !== ""
            text: pill.text
            color: pill.pillText
            font.pixelSize: 11
            font.weight: Font.DemiBold
        }
    }

    MouseArea {
        id: area
        anchors.fill: parent
        hoverEnabled: true
        onClicked: pill.clicked()
    }
}
