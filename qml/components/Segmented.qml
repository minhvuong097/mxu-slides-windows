import QtQuick
import "qrc:/qml/theme"

// Segmented control used for the Edit / Present / Stage switch and library
// tabs. Active segment: #1b1b1d with an inset #3a3a3d border (mockup default).
Rectangle {
    id: control
    property var model: []
    property int currentIndex: 0
    property bool compact: false
    property bool outlined: false
    property color trackColor: outlined ? "#252528" : Theme.segmentedBg
    signal activated(int index)

    color: trackColor
    radius: compact ? 11 : 10
    border.color: outlined ? "#38383b" : "transparent"
    border.width: outlined ? 1 : 0

    width: row.implicitWidth + 4
    height: row.implicitHeight + 4

    Row {
        id: row
        anchors.centerIn: parent
        Repeater {
            model: control.model
            delegate: Rectangle {
                width: label.implicitWidth + (control.compact ? 16 : 28)
                height: Math.max(24, label.implicitHeight + 10)
                radius: control.compact ? 9 : 8
                color: control.currentIndex === index ? "#1b1b1d" : "transparent"
                border.width: control.currentIndex === index ? 1 : 0
                border.color: "#343437"

                Text {
                    id: label
                    anchors.centerIn: parent
                    text: typeof modelData === "string" ? modelData : (modelData.name || modelData.title || "")
                    color: control.currentIndex === index ? Theme.text : Theme.textDim
                    font.pixelSize: 11
                    font.weight: control.currentIndex === index ? Font.DemiBold : Font.Normal
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        control.currentIndex = index
                        control.activated(index)
                    }
                }
            }
        }
    }
}
