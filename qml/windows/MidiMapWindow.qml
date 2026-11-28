import QtQuick
import QtQuick.Controls
import QtQuick.Window
import "qrc:/qml/theme"

// Windows counterpart of the Mac MIDI map editor: device connection, channel
// filtering, note-name display, learn mode and velocity-as-index options.
Window {
    id: map
    width: 760
    height: 460
    minimumWidth: 640
    minimumHeight: 360
    title: "MIDI Map — MxU Slides"
    color: Theme.bg
    flags: Qt.Window
    visible: false

    readonly property var actions: ["next", "previous", "clear", "present", "stop", "stage"]
    property bool learning: false
    property int manualNote: 60

    function open() { visible = true }

    Connections {
        target: Mxu.automation.midiInput
        function onNoteReceived(note, on) {
            if (on && map.learning) {
                Mxu.automation.addMidiTrigger(actionBox.currentText, note)
                map.learning = false
            }
        }
    }

    Row {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 12

        Rectangle {
            width: 260
            height: parent.height
            radius: 10
            color: Theme.card
            Column {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 8

                Text { text: "DEVICES"; color: Theme.textDim; font.pixelSize: 10; font.weight: Font.Bold }
                Repeater {
                    model: Mxu.automation.midiInput.devices
                    delegate: Rectangle {
                        width: parent.width; height: 34; radius: 7; color: "#2c2c30"
                        Row {
                            anchors.fill: parent; anchors.leftMargin: 8; anchors.rightMargin: 8; spacing: 8
                            Text {
                                width: parent.width - 90
                                anchors.verticalCenter: parent.verticalCenter
                                text: modelData.name || ("Device " + modelData.index)
                                color: Theme.text; font.pixelSize: 11; elide: Text.ElideRight
                            }
                            Rectangle {
                                width: 66; height: 22; radius: 6
                                color: Mxu.automation.midiInput.connected ? Theme.green : Theme.surface
                                Text {
                                    anchors.centerIn: parent
                                    text: Mxu.automation.midiInput.connected ? "Stop" : "Connect"
                                    color: "white"; font.pixelSize: 9
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: Mxu.automation.midiInput.connected
                                               ? Mxu.automation.midiInput.disconnectDevice()
                                               : Mxu.automation.midiInput.connectDevice(modelData.index)
                                }
                            }
                        }
                    }
                }
                Rectangle {
                    width: 100; height: 26; radius: 7; color: Theme.surface
                    Text { anchors.centerIn: parent; text: "Refresh"; color: Theme.text; font.pixelSize: 10 }
                    MouseArea { anchors.fill: parent; onClicked: Mxu.automation.midiInput.refresh() }
                }
                Text { text: "Last note: " + Mxu.automation.midiNoteName(Mxu.automation.midiInput.lastNote); color: Theme.textDim; font.pixelSize: 10 }

                Text { text: "CHANNEL FILTER"; color: Theme.textDim; font.pixelSize: 10; font.weight: Font.Bold }
                ComboBox {
                    id: channelBox
                    width: parent.width
                    model: ["All channels", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
                    currentIndex: Mxu.automation.midiChannel < 0 ? 0 : Mxu.automation.midiChannel
                    onActivated: Mxu.automation.midiChannel = currentIndex === 0 ? -1 : currentIndex
                    background: Rectangle { radius: 7; color: Theme.inset }
                    contentItem: Text { text: channelBox.currentText; color: Theme.text; font.pixelSize: 11; verticalAlignment: Text.AlignVCenter }
                }

                Text { text: "LEARN"; color: Theme.textDim; font.pixelSize: 10; font.weight: Font.Bold }
                ComboBox {
                    id: actionBox
                    width: parent.width
                    model: map.actions
                    background: Rectangle { radius: 7; color: Theme.inset }
                    contentItem: Text { text: actionBox.currentText; color: Theme.text; font.pixelSize: 11; verticalAlignment: Text.AlignVCenter }
                }
                Rectangle {
                    width: parent.width; height: 28; radius: 7
                    color: map.learning ? Theme.pink : Theme.accent
                    Text {
                        anchors.centerIn: parent
                        text: map.learning ? "Waiting for note…" : "Learn note"
                        color: "white"; font.pixelSize: 10; font.weight: Font.Bold
                    }
                    MouseArea { anchors.fill: parent; onClicked: map.learning = !map.learning }
                }
                Row {
                    width: parent.width; spacing: 6
                    NumberField { id: manualNoteField; width: 90; label: "Note"; value: map.manualNote; onCommitted: map.manualNote = value }
                    Rectangle {
                        width: 90; height: 26; radius: 7; color: Theme.surface
                        Text { anchors.centerIn: parent; text: "+ Manual"; color: Theme.text; font.pixelSize: 10 }
                        MouseArea { anchors.fill: parent; onClicked: Mxu.automation.addMidiTrigger(actionBox.currentText, map.manualNote) }
                    }
                }
            }
        }

        Rectangle {
            width: parent.width - 272
            height: parent.height
            radius: 10
            color: Theme.card
            Column {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 8
                Text { text: "COMMAND MAP"; color: Theme.textDim; font.pixelSize: 10; font.weight: Font.Bold }
                Flickable {
                    width: parent.width
                    height: parent.height - 20
                    contentHeight: triggerList.implicitHeight
                    clip: true
                    Column {
                        id: triggerList
                        width: parent.width
                        spacing: 4
                        Repeater {
                            model: Mxu.automation.triggers
                            delegate: Rectangle {
                                width: parent.width
                                height: 44
                                radius: 7
                                color: modelData.kind === "midi" ? "#2c2c30" : "#252528"
                                Row {
                                    anchors.fill: parent; anchors.leftMargin: 8; anchors.rightMargin: 8; spacing: 6
                                    Column {
                                        width: 130; anchors.verticalCenter: parent.verticalCenter
                                        Text { text: modelData.action; color: Theme.text; font.pixelSize: 11; font.weight: Font.Bold }
                                        Text { text: modelData.kind; color: Theme.textDim; font.pixelSize: 9 }
                                    }
                                    Text {
                                        width: 56; anchors.verticalCenter: parent.verticalCenter
                                        text: modelData.kind === "midi"
                                              ? (modelData.noteName || Mxu.automation.midiNoteName(modelData.value))
                                              : modelData.value
                                        color: Theme.accent; font.pixelSize: 11; font.weight: Font.Bold
                                    }
                                    ComboBox {
                                        visible: modelData.kind === "midi"
                                        width: 46; height: 24
                                        model: ["All", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
                                        currentIndex: modelData.channel && modelData.channel > 0 ? modelData.channel : 0
                                        onActivated: Mxu.automation.configureMidiTrigger(modelData.id, currentIndex === 0 ? -1 : currentIndex, modelData.velocityAsIndex || false)
                                        background: Rectangle { radius: 6; color: Theme.surface }
                                        contentItem: Text { text: currentText; color: Theme.text; font.pixelSize: 9; verticalAlignment: Text.AlignVCenter }
                                    }
                                    Rectangle {
                                        visible: modelData.kind === "midi"
                                        width: 88; height: 24; radius: 6
                                        color: modelData.velocityAsIndex ? Theme.yellow : Theme.surface
                                        Text {
                                            anchors.centerIn: parent
                                            text: modelData.velocityAsIndex ? "Velocity idx" : "Note only"
                                            color: modelData.velocityAsIndex ? "#1c1c1e" : Theme.text
                                            font.pixelSize: 9
                                        }
                                        MouseArea {
                                            anchors.fill: parent
                                            onClicked: Mxu.automation.configureMidiTrigger(modelData.id, modelData.channel || -1, !modelData.velocityAsIndex)
                                        }
                                    }
                                    Rectangle {
                                        width: 28; height: 24; radius: 6; color: Theme.surface
                                        Text { anchors.centerIn: parent; text: "✕"; color: Theme.textDim; font.pixelSize: 10 }
                                        MouseArea { anchors.fill: parent; onClicked: Mxu.automation.removeTrigger(modelData.id) }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
