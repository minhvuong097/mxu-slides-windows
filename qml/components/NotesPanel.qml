import QtQuick
import QtQuick.Controls
import QtQuick.Window
import "qrc:/qml/theme"

// Sermon notes window bound to NotesService (NoteDocument schema). Ported from
// the Mac NoteWindow as a real OS window instead of an in-shell panel.
Window {
    id: panel
    width: 420
    height: 460
    visible: false
    flags: Qt.Window | Qt.FramelessWindowHint
            | (Mxu.outputs.alwaysOnTop ? Qt.WindowStaysOnTopHint : 0)

    signal closeRequested()

    Rectangle {
        anchors.fill: parent
        radius: 12
        color: Theme.card
        border.color: "#3a3a3e"
        border.width: 1

        Column {
            anchors.fill: parent
            anchors.margins: 14
            spacing: 8

            Row {
                width: parent.width
                Text { anchors.verticalCenter: parent.verticalCenter; text: "Sermon Notes"; color: Theme.text; font.pixelSize: 13; font.weight: Font.DemiBold }
                Item { width: parent.width - 200; height: 1 }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "×"; color: Theme.textDim; font.pixelSize: 16
                    MouseArea { anchors.fill: parent; onClicked: panel.closeRequested() }
                }
            }

            Rectangle { width: parent.width; height: 1; color: "#333" }

            ListView {
                width: parent.width
                height: 300
                clip: true
                model: Mxu.notes.blocks
                delegate: Rectangle {
                    width: ListView.view.width
                    height: 40
                    color: "transparent"
                    Text {
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width - 40
                        text: modelData.text
                        color: Theme.text
                        font.pixelSize: 11
                        elide: Text.ElideRight
                    }
                    Text {
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        text: "×"; color: Theme.textDim; font.pixelSize: 14
                        MouseArea { anchors.fill: parent; onClicked: Mxu.notes.removeBlock(modelData.id) }
                    }
                }
            }

            TextField {
                id: noteInput
                width: parent.width
                placeholderText: "Add a note…"
                placeholderTextColor: Theme.textDim
                color: Theme.text
                font.pixelSize: 11
                background: Rectangle { radius: 7; color: Theme.inset }
            }

            Rectangle {
                width: 90; height: 28; radius: 9; color: Theme.accent
                Text { anchors.centerIn: parent; text: "Add"; color: "white"; font.pixelSize: 11; font.weight: Font.DemiBold }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        Mxu.notes.addBlock(noteInput.text)
                        noteInput.text = ""
                    }
                }
            }
        }
    }

    function open() { visible = true; noteInput.forceActiveFocus() }
    function hide() { visible = false }
}
