import QtQuick
import QtQuick.Layouts
import "qrc:/qml/theme"
import "qrc:/qml/components"

Rectangle {
    id: row
    property string label: ""
    property bool toggle: false
    property bool checked: false
    property string value: ""
    property real fieldWidth: 210
    signal toggled(bool value)
    signal clicked()

    height: 42
    color: "transparent"
    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 1
        color: "#333"
    }

    RowLayout {
        anchors.fill: parent
        spacing: 10
        Text {
            Layout.fillWidth: true
            text: row.label
            color: Theme.text
            font.pixelSize: 12
            elide: Text.ElideRight
        }
        ToggleSwitch {
            visible: row.toggle
            Layout.alignment: Qt.AlignVCenter
            checked: row.checked
            onToggled: row.toggled(value)
        }
        Rectangle {
            visible: !row.toggle
            Layout.preferredWidth: row.fieldWidth
            Layout.preferredHeight: 28
            radius: 8
            color: "#2b2b2e"
            border.color: "#3a3a3d"
            border.width: 1
            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                Text {
                    Layout.fillWidth: true
                    text: row.value
                    color: Theme.text
                    font.pixelSize: 12
                    elide: Text.ElideRight
                }
                AppIcon { name: "sort"; size: 11; color: Theme.textDim }
            }
            MouseArea { anchors.fill: parent; onClicked: row.clicked() }
        }
    }
}
