import QtQuick
import QtQuick.Controls
import QtQuick.Window
import "qrc:/qml/theme"

// Follow / backup pairing window (Mac FollowPairingSheet + SyncMonitor):
// LAN peer discovery, station links and the operation-log exchange state.
Window {
    id: follow
    width: 820
    height: 500
    minimumWidth: 680
    minimumHeight: 400
    title: "Follow & Sync — MxU Slides"
    color: Theme.bg
    flags: Qt.Window
    visible: false

    readonly property var modes: ["follow", "backup"]
    property string selectedPeerId: ""

    function open() { visible = true }

    Row {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 12

        Rectangle {
            width: 400
            height: parent.height
            radius: 10
            color: Theme.card
            Column {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 8

                Row {
                    width: parent.width
                    Text { anchors.verticalCenter: parent.verticalCenter; text: "LAN PEERS"; color: Theme.textDim; font.pixelSize: 10; font.weight: Font.Bold }
                    Rectangle {
                        anchors.right: parent.right
                        width: 86; height: 24; radius: 6
                        color: Mxu.discovery.running ? Theme.pink : Theme.accent
                        Text {
                            anchors.centerIn: parent
                            text: Mxu.discovery.running ? "Stop scan" : "Scan LAN"
                            color: "white"; font.pixelSize: 9; font.weight: Font.Bold
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: Mxu.discovery.running ? Mxu.discovery.stop() : Mxu.discovery.start()
                        }
                    }
                }
                Text {
                    width: parent.width
                    text: "This station: " + Mxu.discovery.deviceId
                    color: Theme.textFaint; font.pixelSize: 9; elide: Text.ElideMiddle
                }
                Flickable {
                    width: parent.width
                    height: parent.height - 190
                    contentHeight: peerList.implicitHeight
                    clip: true
                    Column {
                        id: peerList
                        width: parent.width
                        spacing: 4
                        Repeater {
                            model: Mxu.discovery.peers
                            delegate: Rectangle {
                                width: parent.width; height: 40; radius: 7
                                color: follow.selectedPeerId === (modelData.id || modelData.deviceId) ? "#303034" : "#2c2c30"
                                border.color: follow.selectedPeerId === (modelData.id || modelData.deviceId) ? Theme.accent : "transparent"
                                border.width: 1
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: follow.selectedPeerId = modelData.id || modelData.deviceId
                                }
                                Column {
                                    anchors.left: parent.left; anchors.leftMargin: 8
                                    anchors.verticalCenter: parent.verticalCenter
                                    Text { text: modelData.name || modelData.deviceId || "Peer"; color: Theme.text; font.pixelSize: 11; font.weight: Font.Bold }
                                    Text { text: (modelData.address || "") + " · " + (modelData.hostname || ""); color: Theme.textDim; font.pixelSize: 9; elide: Text.ElideRight }
                                }
                            }
                        }
                    }
                }
                Row {
                    width: parent.width; spacing: 6
                    ComboBox {
                        id: pairMode
                        width: 110; height: 26
                        model: follow.modes
                        background: Rectangle { radius: 6; color: Theme.inset }
                        contentItem: Text { text: pairMode.currentText; color: Theme.text; font.pixelSize: 10; verticalAlignment: Text.AlignVCenter }
                    }
                    Rectangle {
                        width: 120; height: 26; radius: 7; color: Theme.accent
                        Text { anchors.centerIn: parent; text: "+ Pair peer"; color: "white"; font.pixelSize: 10; font.weight: Font.Bold }
                        MouseArea { anchors.fill: parent; onClicked: Mxu.serviceLinks.add(follow.selectedPeerId, pairMode.currentText) }
                    }
                }
            }
        }

        Column {
            width: parent.width - 412
            height: parent.height
            spacing: 8

            Rectangle {
                width: parent.width
                height: 200
                radius: 10
                color: Theme.card
                Column {
                    anchors.fill: parent; anchors.margins: 12; spacing: 6
                    Text { text: "STATION LINKS"; color: Theme.textDim; font.pixelSize: 10; font.weight: Font.Bold }
                    Repeater {
                        model: Mxu.serviceLinks.rules
                        delegate: Rectangle {
                            width: parent.width; height: 34; radius: 7; color: "#2c2c30"
                            Row {
                                anchors.fill: parent; anchors.leftMargin: 8; anchors.rightMargin: 8; spacing: 8
                                Column {
                                    width: parent.width - 120; anchors.verticalCenter: parent.verticalCenter
                                    Text { text: modelData.peer; color: Theme.text; font.pixelSize: 11; elide: Text.ElideRight }
                                    Text { text: modelData.mode; color: Theme.textDim; font.pixelSize: 9 }
                                }
                                Rectangle {
                                    width: 44; height: 20; radius: 6; color: modelData.enabled ? Theme.green : Theme.surface
                                    Text { anchors.centerIn: parent; text: modelData.enabled ? "On" : "Off"; color: "white"; font.pixelSize: 9 }
                                    MouseArea { anchors.fill: parent; onClicked: Mxu.serviceLinks.toggle(modelData.id) }
                                }
                                Rectangle {
                                    width: 22; height: 20; radius: 6; color: Theme.surface
                                    Text { anchors.centerIn: parent; text: "✕"; color: Theme.textDim; font.pixelSize: 9 }
                                    MouseArea { anchors.fill: parent; onClicked: Mxu.serviceLinks.remove(modelData.id) }
                                }
                            }
                        }
                    }
                }
            }

            Rectangle {
                width: parent.width
                height: 168
                radius: 10
                color: Theme.card
                Column {
                    anchors.fill: parent; anchors.margins: 12; spacing: 6
                    Text { text: "SYNC LEDGER"; color: Theme.textDim; font.pixelSize: 10; font.weight: Font.Bold }
                    Text { text: "Device " + Mxu.syncLedger.deviceId; color: Theme.text; font.pixelSize: 10; elide: Text.ElideMiddle; width: parent.width }
                    Text { text: "Clock " + Mxu.syncLedger.clock + " · operations " + Mxu.syncLedger.operationCount; color: Theme.textDim; font.pixelSize: 11 }
                    Row { spacing: 6
                        Rectangle {
                            width: 110; height: 26; radius: 7; color: Theme.accent
                            Text { anchors.centerIn: parent; text: "Record sync"; color: "white"; font.pixelSize: 10 }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.syncLedger.append("manual", "sync", true) }
                        }
                        Rectangle {
                            width: 110; height: 26; radius: 7; color: Theme.surface
                            Text { anchors.centerIn: parent; text: "Export JSON"; color: Theme.text; font.pixelSize: 10 }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.diagnostics.log("sync.export " + Mxu.exportSyncJson().length + " chars") }
                        }
                        Rectangle {
                            width: 110; height: 26; radius: 7; color: Theme.surface
                            Text { anchors.centerIn: parent; text: "Apply JSON…"; color: Theme.text; font.pixelSize: 10 }
                            MouseArea { anchors.fill: parent; onClicked: syncInput.visible = !syncInput.visible }
                        }
                    }
                    Rectangle {
                        id: syncInput
                        visible: false
                        width: parent.width; height: 60; radius: 7; color: Theme.inset
                        TextEdit {
                            id: syncText
                            anchors.fill: parent; anchors.margins: 6
                            color: Theme.text; font.pixelSize: 9
                            wrapMode: TextEdit.WrapAnywhere
                        }
                        MouseArea {
                            anchors.right: parent.right; anchors.bottom: parent.bottom
                            width: 60; height: 20
                            onClicked: {
                                Mxu.importSyncJson(syncText.text)
                                syncInput.visible = false
                            }
                        }
                    }
                }
            }
        }
    }
}
