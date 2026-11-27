import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "qrc:/qml/theme"

Rectangle {
    id: field
    property string label: ""
    property real value: 0
    signal committed(real value)

    implicitHeight: 28
    radius: 7
    color: Theme.inset

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 8
        anchors.rightMargin: 8
        Text { text: field.label; color: Theme.textDim; font.pixelSize: 11 }
        Item { Layout.fillWidth: true; Layout.preferredHeight: 1 }
        TextField {
            id: input
            Layout.preferredWidth: 54
            text: Number(field.value).toFixed(field.value % 1 === 0 ? 0 : 2)
            color: Theme.text
            font.pixelSize: 11
            horizontalAlignment: Text.AlignRight
            padding: 0
            background: Rectangle { color: "transparent" }
            onEditingFinished: field.committed(Number(text))
            onAccepted: field.committed(Number(text))
        }
    }
}
