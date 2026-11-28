import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Window
import "qrc:/qml/theme"

// Import activity (Mac ImportActivity / ReplaceMediaFileFlow): persisted ledger
// with status filters, hash verification, retry and batch import.
Window {
    id: activity
    width: 880
    height: 500
    minimumWidth: 700
    minimumHeight: 380
    title: "Import Activity — MxU Slides"
    color: Theme.bg
    flags: Qt.Window
    visible: false

    readonly property var filters: ["all", "ready", "pending", "failed", "missing", "changed"]
    readonly property var counts: Mxu.importLedger.counts

    function open() { visible = true }

    function statusColor(status) {
        if (status === "ready") return Theme.green
        if (status === "pending") return Theme.yellow
        if (status === "failed" || status === "missing") return Theme.pink
        return Theme.textDim
    }

    Column {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 8

        Row {
            width: parent.width; spacing: 6
            Text { anchors.verticalCenter: parent.verticalCenter; text: "Import Activity"; color: Theme.text; font.pixelSize: 14; font.weight: Font.DemiBold }
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "Total " + activity.counts.total + " · Ready " + activity.counts.ready
                      + " · Pending " + activity.counts.pending + " · Failed " + activity.counts.failed
                      + " · Missing " + activity.counts.missing
                color: Theme.textDim; font.pixelSize: 10
            }
            Item { width: parent.width - 560; height: 1 }
            Rectangle {
                width: 100; height: 26; radius: 7; color: Theme.accent
                Text { anchors.centerIn: parent; text: "+ Import files"; color: "white"; font.pixelSize: 10; font.weight: Font.Bold }
                MouseArea { anchors.fill: parent; onClicked: importDialog.open() }
            }
            Rectangle {
                width: 76; height: 26; radius: 7; color: Theme.surface
                Text { anchors.centerIn: parent; text: "Clear"; color: Theme.text; font.pixelSize: 10 }
                MouseArea { anchors.fill: parent; onClicked: Mxu.importLedger.clear() }
            }
        }

        Row {
            width: parent.width; spacing: 6
            ComboBox {
                id: filterBox
                width: 130; height: 26
                model: activity.filters
                background: Rectangle { radius: 6; color: Theme.inset }
                contentItem: Text { text: filterBox.currentText; color: Theme.text; font.pixelSize: 10; verticalAlignment: Text.AlignVCenter }
            }
            Text { anchors.verticalCenter: parent.verticalCenter; text: "Status from SHA-256 verification against the original file"; color: Theme.textFaint; font.pixelSize: 9 }
        }

        Rectangle {
            width: parent.width
            height: parent.height - 70
            radius: 10
            color: Theme.card
            Flickable {
                anchors.fill: parent
                anchors.margins: 8
                contentHeight: entryList.implicitHeight
                clip: true
                Column {
                    id: entryList
                    width: parent.width
                    spacing: 4
                    Repeater {
                        model: Mxu.importLedger.entries
                        delegate: Rectangle {
                            width: parent.width
                            height: 44
                            radius: 7
                            color: "#2c2c30"
                            visible: filterBox.currentText === "all" || filterBox.currentText === modelData.status
                            Row {
                                anchors.fill: parent; anchors.leftMargin: 8; anchors.rightMargin: 8; spacing: 8
                                Column {
                                    width: parent.width - 300; anchors.verticalCenter: parent.verticalCenter
                                    Text { text: modelData.name; color: Theme.text; font.pixelSize: 11; font.weight: Font.Bold; elide: Text.ElideRight }
                                    Text { text: (modelData.path || "").slice(0, 60) + " · " + (modelData.hash || "").slice(0, 10); color: Theme.textDim; font.pixelSize: 9; elide: Text.ElideRight }
                                }
                                Text {
                                    width: 70; anchors.verticalCenter: parent.verticalCenter
                                    text: modelData.status
                                    color: activity.statusColor(modelData.status)
                                    font.pixelSize: 10; font.weight: Font.Bold
                                }
                                Text { width: 70; anchors.verticalCenter: parent.verticalCenter; text: (modelData.size / 1024).toFixed(0) + " KB"; color: Theme.textDim; font.pixelSize: 9 }
                                Rectangle {
                                    width: 54; height: 22; radius: 6; color: Theme.surface
                                    Text { anchors.centerIn: parent; text: "Verify"; color: Theme.text; font.pixelSize: 9 }
                                    MouseArea { anchors.fill: parent; onClicked: Mxu.importLedger.verify(modelData.id) }
                                }
                                Rectangle {
                                    width: 54; height: 22; radius: 6; color: Theme.surface
                                    Text { anchors.centerIn: parent; text: "Retry"; color: Theme.text; font.pixelSize: 9 }
                                    MouseArea { anchors.fill: parent; onClicked: Mxu.importLedger.retry(modelData.id) }
                                }
                                Rectangle {
                                    width: 22; height: 22; radius: 6; color: Theme.surface
                                    Text { anchors.centerIn: parent; text: "✕"; color: Theme.textDim; font.pixelSize: 9 }
                                    MouseArea { anchors.fill: parent; onClicked: Mxu.importLedger.remove(modelData.id) }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    FileDialog {
        id: importDialog
        title: "Import media files"
        fileMode: FileDialog.OpenFiles
        nameFilters: ["Images (*.png *.jpg *.jpeg)", "Videos (*.mp4 *.mov *.mkv)", "All files (*)"]
        onAccepted: {
            for (const file of selectedFiles) {
                Mxu.importLedger.record(file.toString())
                Mxu.mediaService.importFile(file.toString())
            }
        }
    }
}
