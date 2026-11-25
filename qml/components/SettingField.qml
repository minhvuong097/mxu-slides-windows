import QtQuick
import QtQuick.Layouts
import "qrc:/qml/theme"
import "qrc:/qml/components"

Rectangle {
    id: row
    property string label: ""
    property string value: ""
    property color valueColor: Theme.text
    property string icon: ""
    signal clicked()

    implicitHeight: 28
    radius: 7
    color: Theme.inset

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        spacing: 6
        AppIcon {
            visible: row.icon !== ""
            name: row.icon
            size: 12
            color: Theme.textDim
        }
        Text {
            Layout.fillWidth: true
            text: row.label
            color: Theme.text
            font.pixelSize: 11
            elide: Text.ElideRight
        }
        Text {
            text: row.value
            color: row.valueColor
            font.pixelSize: 11
        }
        AppIcon { name: "chevronDown"; size: 11; color: Theme.textDim }
    }

    MouseArea { anchors.fill: parent; onClicked: row.clicked() }
}
