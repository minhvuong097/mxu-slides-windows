import QtQuick
import QtQuick.Controls
import QtQuick.Window
import "qrc:/qml/theme"

// Presentation timeline (Mac PresentationTimelineView / TimelineControls):
// timed cue lanes with waveform blocks, trim handles, timecode scrubbing and
// per-clip editing. Persisted in TimelineService.
Window {
    id: panel
    width: 1020
    height: 420
    minimumWidth: 820
    minimumHeight: 340
    visible: false
    flags: Qt.Window | Qt.FramelessWindowHint
            | (Mxu.outputs.alwaysOnTop ? Qt.WindowStaysOnTopHint : 0)

    signal closeRequested()

    property real pixelsPerSecond: 8
    property string selectedCueId: ""
    readonly property var selectedCue: {
        const found = Mxu.timeline.cues.find(function (cue) { return cue.id === panel.selectedCueId })
        return found || {}
    }

    function open() { visible = true }
    function hide() { visible = false }

    function setProp(key, value) {
        if (panel.selectedCueId)
            Mxu.timeline.setCueProp(panel.selectedCueId, key, value)
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

            // Transport + timecode.
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
                TextField {
                    id: timecodeField
                    width: 96; height: 24
                    text: Mxu.timeline.timecodeAt(Mxu.timeline.playhead)
                    color: Theme.text; font.pixelSize: 10
                    background: Rectangle { radius: 7; color: Theme.inset }
                    onEditingFinished: Mxu.timeline.seekTimecode(text)
                }
                Text { anchors.verticalCenter: parent.verticalCenter; text: "/" + Mxu.timeline.timecodeAt(Mxu.timeline.duration); color: Theme.textDim; font.pixelSize: 10 }
                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    width: 24; height: 24; radius: 7; color: Theme.surface
                    Text { anchors.centerIn: parent; text: "−"; color: Theme.text; font.pixelSize: 12 }
                    MouseArea { anchors.fill: parent; onClicked: panel.pixelsPerSecond = Math.max(3, panel.pixelsPerSecond - 2) }
                }
                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    width: 24; height: 24; radius: 7; color: Theme.surface
                    Text { anchors.centerIn: parent; text: "+"; color: Theme.text; font.pixelSize: 12 }
                    MouseArea { anchors.fill: parent; onClicked: panel.pixelsPerSecond = Math.min(40, panel.pixelsPerSecond + 2) }
                }
                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    width: 36; height: 24; radius: 7; color: Theme.surface
                    Text { anchors.centerIn: parent; text: "JSON"; color: Theme.text; font.pixelSize: 9 }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            const json = Mxu.timeline.exportJson()
                            Mxu.diagnostics.log("timeline.export " + json.length + " chars")
                        }
                    }
                }
                Item { width: parent.width - 500; height: 1 }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "×"; color: Theme.textDim; font.pixelSize: 16
                    MouseArea { anchors.fill: parent; onClicked: panel.closeRequested() }
                }
            }

            // Add clip + selected clip editor.
            Row {
                width: parent.width
                height: 40
                spacing: 6
                TextField {
                    id: draftName
                    width: 160; height: 26
                    placeholderText: "New cue"
                    color: Theme.text; font.pixelSize: 10
                    background: Rectangle { radius: 6; color: Theme.inset }
                }
                ComboBox {
                    id: draftLane
                    width: 90; height: 26
                    model: ["slides", "audio", "media"]
                    background: Rectangle { radius: 6; color: Theme.inset }
                    contentItem: Text { text: draftLane.currentText; color: Theme.text; font.pixelSize: 10; verticalAlignment: Text.AlignVCenter }
                }
                TextField {
                    id: draftAt
                    width: 52; height: 26
                    text: (Mxu.timeline.playhead / 1000).toFixed(1)
                    color: Theme.text; font.pixelSize: 10
                    background: Rectangle { radius: 6; color: Theme.inset }
                }
                TextField {
                    id: draftDuration
                    width: 52; height: 26
                    text: "10"
                    color: Theme.text; font.pixelSize: 10
                    background: Rectangle { radius: 6; color: Theme.inset }
                }
                Rectangle {
                    width: 56; height: 26; radius: 6; color: Theme.accent
                    Text { anchors.centerIn: parent; text: "+ Add"; color: "white"; font.pixelSize: 9; font.weight: Font.Bold }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            const id = Mxu.timeline.addCue(draftName.text || "Cue", draftLane.currentText,
                                                            parseFloat(draftAt.text) * 1000, parseFloat(draftDuration.text) * 1000)
                            panel.selectedCueId = id
                            draftName.text = ""
                        }
                    }
                }

                Rectangle { width: 1; height: 26; color: Theme.borderMid }

                TextField {
                    id: clipName
                    width: 150; height: 26
                    text: panel.selectedCue.name || ""
                    placeholderText: "Selected clip"
                    color: Theme.text; font.pixelSize: 10
                    background: Rectangle { radius: 6; color: Theme.inset }
                    onEditingFinished: panel.setProp("name", text)
                }
                TextField {
                    id: clipSource
                    width: 130; height: 26
                    text: panel.selectedCue.source || ""
                    placeholderText: "Source"
                    color: Theme.text; font.pixelSize: 10
                    background: Rectangle { radius: 6; color: Theme.inset }
                    onEditingFinished: panel.setProp("source", text)
                }
                Rectangle {
                    width: 26; height: 26; radius: 6
                    color: panel.selectedCue.locked ? Theme.pink : Theme.surface
                    Text { anchors.centerIn: parent; text: panel.selectedCue.locked ? "🔒" : "🔓"; font.pixelSize: 10 }
                    MouseArea { anchors.fill: parent; onClicked: Mxu.timeline.toggleLock(panel.selectedCueId) }
                }
                Rectangle {
                    width: 56; height: 26; radius: 6; color: Theme.surface
                    Text { anchors.centerIn: parent; text: "Dup"; color: Theme.text; font.pixelSize: 9 }
                    MouseArea { anchors.fill: parent; onClicked: Mxu.timeline.duplicateCue(panel.selectedCueId) }
                }
                Rectangle {
                    width: 56; height: 26; radius: 6; color: Theme.surface
                    Text { anchors.centerIn: parent; text: "✕ Del"; color: Theme.text; font.pixelSize: 9 }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: { Mxu.timeline.removeCue(panel.selectedCueId); panel.selectedCueId = "" }
                    }
                }
            }

            Rectangle { width: parent.width; height: 1; color: "#333" }

            Item {
                width: parent.width
                height: parent.height - 110

                // Ruler: click to scrub.
                Item {
                    id: ruler
                    width: parent.width
                    height: 20
                    Repeater {
                        model: Math.ceil(Mxu.timeline.duration / 1000 / 5) + 1
                        delegate: Item {
                            x: 60 + index * 5 * panel.pixelsPerSecond
                            Rectangle { width: 1; height: 8; color: Theme.borderMid }
                            Text { y: 8; text: (index * 5) + "s"; color: Theme.textFaint; font.pixelSize: 9 }
                        }
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: Mxu.timeline.seek((mouse.x - 60) / panel.pixelsPerSecond * 1000)
                    }
                }

                Flickable {
                    anchors.top: ruler.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    contentWidth: 60 + (Mxu.timeline.duration / 1000 + 5) * panel.pixelsPerSecond
                    contentHeight: laneColumn.implicitHeight
                    clip: true

                    Column {
                        id: laneColumn
                        spacing: 4

                        Repeater {
                            model: Mxu.timeline.lanes
                            delegate: Item {
                                property string laneId: modelData.id
                                width: 60 + (Mxu.timeline.duration / 1000 + 5) * panel.pixelsPerSecond
                                height: 62
                                Rectangle { anchors.fill: parent; color: "transparent"; border.color: "#2e2e31"; border.width: 1 }
                                Text { anchors.left: parent.left; anchors.top: parent.top; anchors.margins: 4; text: modelData.name; color: Theme.textDim; font.pixelSize: 10 }

                                Repeater {
                                    model: Mxu.timeline.cues
                                    delegate: Rectangle {
                                        id: clip
                                        property real editX: -1
                                        property real editWidth: -1
                                        visible: modelData.lane === laneId
                                        x: editX >= 0 ? editX : 60 + modelData.at / 1000 * panel.pixelsPerSecond
                                        y: 20
                                        width: editWidth >= 0 ? editWidth : Math.max(24, modelData.duration / 1000 * panel.pixelsPerSecond)
                                        height: 38
                                        radius: 6
                                        color: modelData.color || "#1f8f3f"
                                        border.color: panel.selectedCueId === modelData.id ? Theme.yellow : "transparent"
                                        border.width: 2
                                        opacity: modelData.locked ? 0.6 : 1

                                        // Waveform bars for audio/media clips.
                                        Row {
                                            anchors.left: parent.left
                                            anchors.right: parent.right
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.margins: 2
                                            clip: true
                                            visible: modelData.lane !== "slides"
                                            Repeater {
                                                model: modelData.waveform || []
                                                delegate: Rectangle {
                                                    width: 2
                                                    height: Math.max(2, (modelData || 0.2) * 30)
                                                    anchors.verticalCenter: parent.verticalCenter
                                                    color: "#ffffff"
                                                    opacity: 0.5
                                                }
                                            }
                                        }

                                        Text {
                                            anchors.centerIn: parent
                                            width: parent.width - 8
                                            text: modelData.name
                                            color: "white"
                                            font.pixelSize: 9
                                            elide: Text.ElideRight
                                        }

                                        MouseArea {
                                            id: moveArea
                                            anchors.fill: parent
                                            anchors.rightMargin: 8
                                            property real startX: 0
                                            property real startPos: 0
                                            onPressed: { panel.selectedCueId = modelData.id; startX = mouseX; startPos = clip.x }
                                            onPositionChanged: {
                                                if (pressed && !modelData.locked)
                                                    clip.editX = Math.max(60, startPos + mouseX - startX)
                                            }
                                            onReleased: {
                                                if (clip.editX >= 0)
                                                    Mxu.timeline.moveCue(modelData.id, (clip.editX - 60) / panel.pixelsPerSecond * 1000)
                                                clip.editX = -1
                                            }
                                        }
                                        Rectangle {
                                            anchors.right: parent.right
                                            anchors.top: parent.top
                                            anchors.bottom: parent.bottom
                                            width: 8
                                            color: "white"
                                            opacity: 0.35
                                            MouseArea {
                                                anchors.fill: parent
                                                property real startX: 0
                                                property real startWidth: 0
                                                onPressed: { startX = mouseX; startWidth = clip.width }
                                                onPositionChanged: {
                                                    if (pressed && !modelData.locked)
                                                        clip.editWidth = Math.max(24, startWidth + mouseX - startX)
                                                }
                                                onReleased: {
                                                    if (clip.editWidth >= 0)
                                                        Mxu.timeline.resizeCue(modelData.id, clip.editWidth / panel.pixelsPerSecond * 1000)
                                                    clip.editWidth = -1
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    Rectangle {
                        x: 60 + Mxu.timeline.playhead / 1000 * panel.pixelsPerSecond
                        y: 0
                        width: 2
                        height: parent.height
                        color: Theme.yellow
                    }
                }
            }
        }
    }
}
