import QtQuick
import "qrc:/qml/theme"

Rectangle {
    id: thumb
    property string from: "#6a2cf0"
    property string to: "#0a0a2a"
    property string label: ""
    property real labelSize: 18

    radius: 8
    gradient: Gradient {
        orientation: Gradient.Horizontal
        GradientStop { position: 0; color: thumb.from }
        GradientStop { position: 1; color: thumb.to }
    }

    Text {
        anchors.centerIn: parent
        width: parent.width - 12
        text: thumb.label
        color: "white"
        font.pixelSize: thumb.labelSize
        font.weight: Font.ExtraBold
        font.italic: true
        font.strikeout: false
        lineHeight: 1.05
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WordWrap
    }
}
