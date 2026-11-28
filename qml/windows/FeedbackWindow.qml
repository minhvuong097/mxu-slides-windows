import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Window
import "qrc:/qml/theme"

// Feedback + diagnostics bundle (Mac FeedbackView / DiagnosticsStore parity).
Window {
    id: feedback
    width: 520
    height: 420
    minimumWidth: 420
    minimumHeight: 340
    title: "Feedback — MxU Slides"
    color: Theme.bg
    flags: Qt.Window
    visible: false

    function open() { visible = true }

    Column {
        anchors.fill: parent
        anchors.margins: 14
        spacing: 10

        Text { text: "Send feedback"; color: Theme.text; font.pixelSize: 16; font.weight: Font.DemiBold }

        ComboBox {
            id: categoryBox
            width: parent.width
            model: ["Bug", "Idea", "Performance", "Other"]
            background: Rectangle { radius: 7; color: Theme.inset }
            contentItem: Text { text: categoryBox.currentText; color: Theme.text; font.pixelSize: 11; verticalAlignment: Text.AlignVCenter }
        }

        TextArea {
            id: messageField
            width: parent.width
            height: 170
            placeholderText: "What happened? What did you expect?"
            color: Theme.text
            font.pixelSize: 12
            background: Rectangle { radius: 8; color: Theme.inset }
        }

        Rectangle {
            width: parent.width
            height: 66
            radius: 8
            color: Theme.card
            Column {
                anchors.fill: parent
                anchors.margins: 8
                spacing: 2
                Text { text: "DIAGNOSTICS"; color: Theme.textDim; font.pixelSize: 9; font.weight: Font.Bold }
                Text {
                    text: "Uptime " + Mxu.diagnostics.uptime + " · FPS " + Mxu.diagnostics.fps.toFixed(1)
                          + " · hitches " + Mxu.diagnostics.hitchCount + " · errors " + Mxu.diagnostics.errorCount
                    color: Theme.text; font.pixelSize: 10; elide: Text.ElideRight
                }
                Text { text: "Events " + Mxu.diagnostics.events.length + " · ticks " + Mxu.diagnostics.tickCount; color: Theme.textDim; font.pixelSize: 10 }
            }
        }

        Row {
            width: parent.width; spacing: 8
            Rectangle {
                width: 120; height: 30; radius: 7; color: Theme.surface
                Text { anchors.centerIn: parent; text: "Export bundle"; color: Theme.text; font.pixelSize: 10 }
                MouseArea { anchors.fill: parent; onClicked: bundleDialog.open() }
            }
            Rectangle {
                width: 140; height: 30; radius: 7; color: Theme.accent
                Text { anchors.centerIn: parent; text: "Send feedback"; color: "white"; font.pixelSize: 10; font.weight: Font.Bold }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (Mxu.submitFeedback(categoryBox.currentText, messageField.text)) {
                            messageField.text = ""
                            feedback.visible = false
                        }
                    }
                }
            }
        }
    }

    FileDialog {
        id: bundleDialog
        title: "Save diagnostics bundle"
        fileMode: FileDialog.SaveFile
        defaultSuffix: "json"
        nameFilters: ["JSON files (*.json)"]
        onAccepted: Mxu.exportDiagnostics(selectedFile.toString())
    }
}
