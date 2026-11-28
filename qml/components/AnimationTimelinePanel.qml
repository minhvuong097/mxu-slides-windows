import QtQuick
import QtQuick.Window
import "qrc:/qml/theme"

// Multi-lane animation timeline (Mac AnimationTimelinePanel). Each slide object
// owns a lane; blocks are its animation steps and can be dragged in time.
Window {
    id: panel
    width: 980
    height: 360
    visible: false
    flags: Qt.Window | Qt.FramelessWindowHint
            | (Mxu.outputs.alwaysOnTop ? Qt.WindowStaysOnTopHint : 0)

    signal closeRequested()

    function open() { visible = true }

    property real pixelsPerSecond: (width - 200) / 30
    property real playhead: 0
    property bool playing: false
    property real totalSeconds: 10

    function stepsFor(objectId) {
        const object = Mxu.slideObjects.find(function (o) { return o.id === objectId })
        const steps = object && object.animationSteps ? object.animationSteps : []
        return steps.map(function (step) { return Object.assign({}, step) })
    }

    function patchSteps(objectId, steps) {
        Mxu.selectObject(objectId)
        Mxu.updateObject({ "animationSteps": steps })
    }

    function shiftStep(objectId, stepId, delay) {
        const steps = stepsFor(objectId)
        for (const step of steps) {
            if (step.id === stepId)
                step.delaySeconds = Math.max(0, delay)
        }
        patchSteps(objectId, steps)
    }

    function addStep() {
        if (!Mxu.selectedObject.id)
            return
        const steps = stepsFor(Mxu.selectedObject.id)
        steps.push({ "kind": "In", "animation": "Fade", "trigger": "OnClick",
                     "durationSeconds": 0.4, "delaySeconds": playhead })
        patchSteps(Mxu.selectedObject.id, steps)
    }

    function kindColor(kind) {
        if (kind === "In") return Theme.green
        if (kind === "Out") return Theme.pink
        if (kind === "Emphasis") return Theme.yellow
        return Theme.accent
    }

    onVisibleChanged: {
        if (!visible)
            playing = false
        playhead = 0
    }

    Rectangle {
        anchors.fill: parent
        radius: 12
        color: Theme.card
        border.color: "#3a3a3e"
        border.width: 1

        Column {
            anchors.fill: parent
            anchors.margins: 12
            spacing: 8

            Row {
                width: parent.width
                height: 28
                spacing: 6
                Text { anchors.verticalCenter: parent.verticalCenter; text: "Animation Timeline"; color: Theme.text; font.pixelSize: 13; font.weight: Font.DemiBold }
                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    width: 28; height: 24; radius: 7; color: Theme.surface
                    Text { anchors.centerIn: parent; text: panel.playing ? "II" : ">"; color: Theme.text; font.pixelSize: 11; font.weight: Font.Bold }
                    MouseArea { anchors.fill: parent; onClicked: panel.playing = !panel.playing }
                }
                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    width: 34; height: 24; radius: 7; color: Theme.surface
                    Text { anchors.centerIn: parent; text: "Stop"; color: Theme.text; font.pixelSize: 10 }
                    MouseArea { anchors.fill: parent; onClicked: { panel.playing = false; panel.playhead = 0 } }
                }
                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    width: 88; height: 24; radius: 7; color: Theme.accent
                    Text { anchors.centerIn: parent; text: "+ Animation"; color: "white"; font.pixelSize: 10; font.weight: Font.Bold }
                    MouseArea { anchors.fill: parent; onClicked: panel.addStep() }
                }
                Text { anchors.verticalCenter: parent.verticalCenter; text: panel.playhead.toFixed(1) + "s / " + panel.totalSeconds.toFixed(1) + "s"; color: Theme.textDim; font.pixelSize: 10 }
                Item { width: parent.width - 330; height: 1 }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "×"; color: Theme.textDim; font.pixelSize: 16
                    MouseArea { anchors.fill: parent; onClicked: panel.closeRequested() }
                }
            }

            Rectangle { width: parent.width; height: 1; color: "#333" }

            Item {
                width: parent.width
                height: parent.height - 70

                // Time ruler.
                Item {
                    id: ruler
                    anchors.left: parent.left
                    anchors.leftMargin: 140
                    anchors.right: parent.right
                    height: 22
                    Repeater {
                        model: 16
                        delegate: Item {
                            x: index * 2 * panel.pixelsPerSecond
                            Rectangle { width: 1; height: 8; color: Theme.borderMid }
                            Text { y: 8; text: (index * 2) + "s"; color: Theme.textFaint; font.pixelSize: 9 }
                        }
                    }
                }

                Flickable {
                    anchors.top: ruler.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    contentWidth: 140 + Math.max(30, panel.totalSeconds + 2) * panel.pixelsPerSecond
                    contentHeight: lanes.implicitHeight
                    clip: true

                    Column {
                        id: lanes
                        width: parent.width
                        spacing: 4

                        Repeater {
                            model: Mxu.slideObjects
                            delegate: Rectangle {
                                property string objectId: modelData.id
                                width: Math.max(140 + 32 * panel.pixelsPerSecond, parent.width)
                                height: 40
                                radius: 6
                                color: modelData.selected ? "#303034" : "#2a2a2e"

                                Rectangle {
                                    x: 4; y: 4; width: 132; height: 32; radius: 5; color: "transparent"
                                    Text {
                                        anchors.fill: parent
                                        text: modelData.name || modelData.text || "Object"
                                        color: modelData.selected ? Theme.accent : Theme.text
                                        font.pixelSize: 10
                                        elide: Text.ElideRight
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                    MouseArea { anchors.fill: parent; onClicked: Mxu.selectObject(objectId) }
                                }

                                Repeater {
                                    model: modelData.animationSteps || []
                                    delegate: Rectangle {
                                        id: block
                                        x: 140 + (modelData.delaySeconds || 0) * panel.pixelsPerSecond
                                        y: 8
                                        width: Math.max(28, (modelData.durationSeconds || 0.4) * panel.pixelsPerSecond)
                                        height: 24
                                        radius: 5
                                        color: panel.kindColor(modelData.kind)
                                        opacity: 0.85
                                        Text {
                                            anchors.centerIn: parent
                                            text: modelData.animation
                                            color: "white"
                                            font.pixelSize: 9
                                            elide: Text.ElideRight
                                        }
                                        MouseArea {
                                            anchors.fill: parent
                                            drag.target: block
                                            drag.axis: Drag.XAxis
                                            drag.minimumX: 140
                                            drag.maximumX: 140 + 30 * panel.pixelsPerSecond - block.width
                                            onClicked: Mxu.selectObject(objectId)
                                            onReleased: panel.shiftStep(objectId, modelData.id, (block.x - 140) / panel.pixelsPerSecond)
                                        }
                                    }
                                }
                            }
                        }
                    }

                    // Playhead overlay.
                    Rectangle {
                        x: 140 + panel.playhead * panel.pixelsPerSecond
                        y: 0; width: 2; height: parent.height
                        color: Theme.accent
                        visible: panel.playhead > 0
                    }
                }
            }
        }
    }

    Timer {
        interval: 100
        repeat: true
        running: panel.playing && panel.visible
        onTriggered: {
            let end = 0
            for (const object of Mxu.slideObjects) {
                for (const step of (object.animationSteps || []))
                    end = Math.max(end, (step.delaySeconds || 0) + (step.durationSeconds || 0))
            }
            panel.totalSeconds = Math.max(10, end + 1)
            panel.playhead = panel.playhead >= panel.totalSeconds ? 0 : panel.playhead + 0.1
        }
    }
}
