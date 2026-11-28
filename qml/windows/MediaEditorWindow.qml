import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Window
import "qrc:/qml/theme"
import "qrc:/qml/components"

// Windows counterpart of the Mac MediaEditorView: classification, trim points,
// playback rate, looping, notes and missing-file relocation.
Window {
    id: editor
    width: 900
    height: 560
    minimumWidth: 760
    minimumHeight: 440
    title: "Media Editor — MxU Slides"
    color: Theme.bg
    flags: Qt.Window
    visible: false

    function open(index) {
        if (index >= 0)
            Mxu.mediaService.selectedIndex = index
        visible = true
    }

    readonly property var media: {
        const items = Mxu.mediaService.items
        const index = Mxu.mediaService.selectedIndex
        return index >= 0 && index < items.length ? items[index] : {}
    }

    function patch(key, value) {
        const payload = {}
        payload[key] = value
        Mxu.mediaService.updateMedia(Mxu.mediaService.selectedIndex, payload)
    }

    Row {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 12

        // Media picker + thumbnail.
        Rectangle {
            width: 240
            height: parent.height
            radius: 10
            color: Theme.card
            Column {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 8

                Text { text: "MEDIA"; color: Theme.textDim; font.pixelSize: 10; font.weight: Font.Bold }
                ComboBox {
                    id: mediaPicker
                    width: parent.width
                    model: Mxu.mediaService.items
                    currentIndex: Mxu.mediaService.selectedIndex
                    textRole: "name"
                    onActivated: Mxu.mediaService.selectedIndex = currentIndex
                    background: Rectangle { radius: 7; color: Theme.inset }
                    contentItem: Text { text: mediaPicker.currentText; color: Theme.text; font.pixelSize: 11; elide: Text.ElideRight; verticalAlignment: Text.AlignVCenter }
                }
                Rectangle {
                    width: parent.width
                    height: width * 9 / 16
                    radius: 8
                    color: "#1b1b20"
                    border.color: "#3a3a3e"
                    border.width: 1
                    clip: true
                    Image {
                        anchors.fill: parent
                        source: editor.media.thumbnail || ""
                        fillMode: Image.PreserveAspectCrop
                    }
                    Text {
                        anchors.centerIn: parent
                        visible: !editor.media.thumbnail
                        text: "No thumbnail"
                        color: Theme.textFaint
                        font.pixelSize: 11
                    }
                }
                Text {
                    width: parent.width
                    text: editor.media.name || "No media"
                    color: Theme.text
                    font.pixelSize: 13
                    font.weight: Font.Bold
                    elide: Text.ElideRight
                }
                Text { text: editor.media.type + " · " + editor.media.size; color: Theme.textDim; font.pixelSize: 10 }
                Text {
                    width: parent.width
                    text: editor.media.missing ? "⚠ File missing — locate it" : "● File ready"
                    color: editor.media.missing ? Theme.pink : Theme.green
                    font.pixelSize: 10
                    wrapMode: Text.WordWrap
                }
                Rectangle {
                    width: parent.width; height: 28; radius: 7
                    color: editor.media.favorite ? Theme.yellow : Theme.surface
                    Text {
                        anchors.centerIn: parent
                        text: editor.media.favorite ? "★ Favorite" : "☆ Favorite"
                        color: editor.media.favorite ? "#1c1c1e" : Theme.text
                        font.pixelSize: 10
                    }
                    MouseArea { anchors.fill: parent; onClicked: Mxu.mediaService.toggleFavorite(Mxu.mediaService.selectedIndex) }
                }
                Rectangle {
                    width: parent.width; height: 28; radius: 7; color: Theme.accent
                    Text { anchors.centerIn: parent; text: "Add to Service Flow"; color: "white"; font.pixelSize: 10; font.weight: Font.Bold }
                    MouseArea { anchors.fill: parent; onClicked: Mxu.mediaService.addToServiceFlow(editor.media.name) }
                }
                Rectangle {
                    width: parent.width; height: 28; radius: 7; color: Theme.surface
                    Text { anchors.centerIn: parent; text: "Set as background"; color: Theme.text; font.pixelSize: 10 }
                    MouseArea { anchors.fill: parent; onClicked: Mxu.mediaService.setBackground(editor.media.name) }
                }
            }
        }

        // Deep editor fields.
        Flickable {
            width: parent.width - 252
            height: parent.height
            contentWidth: width
            contentHeight: fields.implicitHeight
            clip: true
            Column {
                id: fields
                width: parent.width
                spacing: 8

                Text { text: "METADATA"; color: Theme.textDim; font.pixelSize: 10; font.weight: Font.Bold }
                TextField {
                    width: parent.width; placeholderText: "Name"
                    text: editor.media.name || ""
                    color: Theme.text; font.pixelSize: 11
                    background: Rectangle { radius: 7; color: Theme.inset }
                    onEditingFinished: editor.patch("name", text)
                }
                ComboBox {
                    id: classificationBox
                    width: parent.width
                    model: ["media", "background", "overlay", "audio", "uncategorized"]
                    currentIndex: Math.max(0, model.indexOf(editor.media.classification || "media"))
                    onActivated: editor.patch("classification", classificationBox.currentText)
                    background: Rectangle { radius: 7; color: Theme.inset }
                    contentItem: Text { text: classificationBox.currentText; color: Theme.text; font.pixelSize: 11; verticalAlignment: Text.AlignVCenter }
                }
                TextField {
                    width: parent.width; placeholderText: "Folder / collection"
                    text: editor.media.folder || ""
                    color: Theme.text; font.pixelSize: 11
                    background: Rectangle { radius: 7; color: Theme.inset }
                    onEditingFinished: editor.patch("folder", text)
                }
                TextField {
                    width: parent.width; placeholderText: "Note"
                    text: editor.media.note || ""
                    color: Theme.text; font.pixelSize: 11
                    background: Rectangle { radius: 7; color: Theme.inset }
                    onEditingFinished: editor.patch("note", text)
                }

                Text { text: "PLAYBACK & TRIM"; color: Theme.textDim; font.pixelSize: 10; font.weight: Font.Bold }
                Row {
                    width: parent.width; spacing: 6
                    NumberField { width: 110; label: "In"; value: editor.media.inPoint || 0; onCommitted: editor.patch("inPoint", value) }
                    NumberField { width: 110; label: "Out"; value: editor.media.outPoint || 0; onCommitted: editor.patch("outPoint", value) }
                    NumberField { width: 110; label: "Rate"; value: editor.media.playRate || 1; onCommitted: editor.patch("playRate", value) }
                }
                Text { text: "Duration " + (editor.media.durationSeconds || 0).toFixed(1) + "s"; color: Theme.textDim; font.pixelSize: 10 }
                Rectangle {
                    width: 120; height: 28; radius: 7
                    color: editor.media.loops ? Theme.green : Theme.surface
                    Text {
                        anchors.centerIn: parent
                        text: editor.media.loops ? "Loops: On" : "Loops: Off"
                        color: editor.media.loops ? "white" : Theme.text
                        font.pixelSize: 10
                    }
                    MouseArea { anchors.fill: parent; onClicked: editor.patch("loops", !editor.media.loops) }
                }

                Text { text: "SOURCE"; color: Theme.textDim; font.pixelSize: 10; font.weight: Font.Bold }
                Text {
                    width: parent.width
                    text: editor.media.sourcePath || "No file path recorded"
                    color: Theme.textDim
                    font.pixelSize: 10
                    wrapMode: Text.WordWrap
                }
                Rectangle {
                    width: 130; height: 28; radius: 7; color: Theme.accent
                    Text { anchors.centerIn: parent; text: "Locate file…"; color: "white"; font.pixelSize: 10; font.weight: Font.Bold }
                    MouseArea { anchors.fill: parent; onClicked: locateDialog.open() }
                }
                FileDialog {
                    id: locateDialog
                    title: "Locate media file"
                    onAccepted: {
                        Mxu.mediaService.locateMedia(Mxu.mediaService.selectedIndex, selectedFile.toString())
                        Mxu.waveform.decode(selectedFile.toString())
                    }
                }
                Row {
                    width: parent.width; spacing: 2; height: 30
                    clip: true
                    Repeater {
                        model: Mxu.waveform.peaks
                        delegate: Rectangle {
                            width: 3; height: Math.max(2, modelData * 28)
                            anchors.verticalCenter: parent.verticalCenter
                            color: Theme.accent
                        }
                    }
                }
                Text { text: Mxu.waveform.status; color: Theme.textDim; font.pixelSize: 9 }

                Rectangle {
                    width: 120; height: 28; radius: 7; color: "#3a2326"
                    Text { anchors.centerIn: parent; text: "Remove media"; color: Theme.pink; font.pixelSize: 10 }
                    MouseArea { anchors.fill: parent; onClicked: Mxu.mediaService.removeMedia(Mxu.mediaService.selectedIndex) }
                }
            }
        }
    }
}
