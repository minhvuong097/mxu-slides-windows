import QtQuick
import QtQuick.Controls
import "qrc:/qml/theme"

// Compact cue timeline with lanes, draggable blocks and a playhead.
Rectangle {
    id: panel
    width: 900
    height: 300
    radius: 12
    color: Theme.card
    border.color: "#3a3a3e"
    border.width: 1
    visible: false
    z: 15

    signal closeRequested()

    property real pixelsPerSecond: (width - 120) / 90

    Column {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 8

        Row {
            width: parent.width
            height: 28
            spacing: 6
            Text { anchors.verticalCenter: parent.verticalCenter; text: "Timeline"; color: Theme.text; font.pixelSize: 13; font.weight: Font.DemiBold }
            Rectangle {
                anchors.verticalCenter: parent.verticalCenter
                width: 28; height: 24; radius: 7; color: Theme.surface
                Text { anchors.centerIn: parent; text: Mxu.timeline.playing ? "II" : ">"; color: Theme.text; font.pixelSize: 11; font.weight: Font.Bold }
                MouseArea { anchors.fill: parent; onClicked: Mxu.timeline.playing ? Mxu.timeline.pause() : Mxu.timeline.play() }
            }
            Rectangle {
                anchors.verticalCenter: parent.verticalCenter
                width: 44; height: 24; radius: 7; color: Theme.surface
                Text { anchors.centerIn: parent; text: "Stop"; color: Theme.text; font.pixelSize: 10 }
                MouseArea { anchors.fill: parent; onClicked: Mxu.timeline.stop() }
            }
            Text { anchors.verticalCenter: parent.verticalCenter; text: (Mxu.timeline.playhead / 1000).toFixed(1) + "s"; color: Theme.textDim; font.pixelSize: 11 }
            Item { width: parent.width - 320; height: 1 }
            Text { anchors.verticalCenter: parent.verticalCenter; text: "×"; color: Theme.textDim; font.pixelSize: 14
                MouseArea { anchors.fill: parent; onClicked: panel.closeRequested() } }
        }

        Rectangle { width: parent.width; height: 1; color: "#333" }

        Repeater {
            model: Mxu.timeline.lanes
            delegate: Item {
                id: laneRow
                property string laneId: modelData.id
                width: panel.width - 24
                height: 68
                Rectangle {
                    anchors.fill: parent
                    color: "transparent"
                    border.color: "#2e2e31"
                    border.width: 1
                }
                Text { anchors.left: parent.left; anchors.top: parent.top; anchors.margins: 4; text: modelData.name; color: Theme.textDim; font.pixelSize: 10 }
                Repeater {
                    model: Mxu.timeline.cues
                    delegate: Rectangle {
                        visible: modelData.lane === laneRow.laneId
                        x: 60 + modelData.at / 1000 * panel.pixelsPerSecond
                        y: 24
                        width: Math.max(24, modelData.duration / 1000 * panel.pixelsPerSecond)
                        height: 34
                        radius: 6
                        color: modelData.lane === "audio" ? "#0a64c8" : (modelData.lane === "media" ? "#8a3fc8" : "#1f8f3f")
                        Text {
                            anchors.centerIn: parent
                            width: parent.width - 4
                            text: modelData.name
                            color: "white"
                            font.pixelSize: 9
                            elide: Text.ElideRight
                        }
                        MouseArea {
                            anchors.fill: parent
                            drag.target: parent
                            drag.axis: Drag.XAxis
                            onReleased: Mxu.timeline.moveCue(modelData.id, (parent.x - 60) / panel.pixelsPerSecond * 1000)
                        }
                    }
                }
            }
        }

        Rectangle {
            x: 60 + Mxu.timeline.playhead / 1000 * panel.pixelsPerSecond
            y: 0
            width: 2
            height: 3 * 68
            color: Theme.yellow
        }
    }

    function open() { visible = true }
    function hide() { visible = false }
}
