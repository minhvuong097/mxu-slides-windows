import QtQuick
import "qrc:/qml/theme"
import "qrc:/qml/components"

Rectangle {
    id: field
    property string text: ""
    property string icon: ""
    property color fieldColor: Theme.inset
    property bool showChevron: false
    property color textColor: Theme.textDim
    property real textSize: 11
    signal clicked()

    implicitHeight: 26
    radius: 7
    color: fieldColor

    Row {
        anchors.fill: parent
        anchors.leftMargin: 8
        anchors.rightMargin: 8
        spacing: 6

        AppIcon {
            visible: field.icon !== ""
            anchors.verticalCenter: parent.verticalCenter
            name: field.icon
            size: 12
            color: field.textColor
        }
        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: field.text
            color: field.textColor
            font.pixelSize: field.textSize
            elide: Text.ElideRight
            maximumLineCount: 1
        }
        Item { width: 2; height: 1 }
        AppIcon {
            visible: field.showChevron
            anchors.verticalCenter: parent.verticalCenter
            name: "chevronDown"
            size: 11
            color: field.textColor
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: field.clicked()
    }
}
