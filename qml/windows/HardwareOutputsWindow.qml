import QtQuick
import QtQuick.Controls
import QtQuick.Window
import "qrc:/qml/theme"

// Hardware output control surface for the runtime-loaded NDI sender and the
// DeckLink backend. Metal is macOS-only; Windows renders through Qt RHI.
Window {
    id: hardware
    width: 720
    height: 440
    minimumWidth: 620
    minimumHeight: 360
    title: "Hardware Outputs — MxU Slides"
    color: Theme.bg
    flags: Qt.Window
    visible: false

    function open() { visible = true }

    Row {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 12

        Rectangle {
            width: (parent.width - 12) / 2
            height: parent.height
            radius: 10
            color: Theme.card
            Column {
                anchors.fill: parent; anchors.margins: 12; spacing: 8
                Text { text: "NDI"; color: Theme.text; font.pixelSize: 13; font.weight: Font.DemiBold }
                Row {
                    spacing: 6
                    Rectangle { width: 8; height: 8; radius: 4; anchors.verticalCenter: parent.verticalCenter
                               color: Mxu.ndiDynamic.available ? Theme.green : Theme.pink }
                    Text { anchors.verticalCenter: parent.verticalCenter; text: Mxu.ndiDynamic.available ? "Runtime available" : "Runtime not installed"; color: Theme.textDim; font.pixelSize: 10 }
                }
                Text { width: parent.width; text: "Library: " + Mxu.ndiDynamic.libraryPath; color: Theme.textDim; font.pixelSize: 9; wrapMode: Text.WordWrap }
                TextField {
                    id: ndiName
                    width: parent.width; placeholderText: "Sender name"
                    text: "MxuSlides"
                    color: Theme.text; font.pixelSize: 11
                    background: Rectangle { radius: 7; color: Theme.inset }
                }
                Row { spacing: 6
                    Rectangle {
                        width: 90; height: 28; radius: 7; color: Theme.accent
                        Text { anchors.centerIn: parent; text: "Start NDI"; color: "white"; font.pixelSize: 10; font.weight: Font.Bold }
                        MouseArea { anchors.fill: parent; onClicked: Mxu.ndiDynamic.start(ndiName.text) }
                    }
                    Rectangle {
                        width: 90; height: 28; radius: 7; color: Theme.surface
                        Text { anchors.centerIn: parent; text: "Stop"; color: Theme.text; font.pixelSize: 10 }
                        MouseArea { anchors.fill: parent; onClicked: Mxu.ndiDynamic.stop() }
                    }
                }
                Text { text: "Status: " + (Mxu.ndiDynamic.active ? "On air" : "Idle"); color: Mxu.ndiDynamic.active ? Theme.green : Theme.textDim; font.pixelSize: 10 }
                Text {
                    width: parent.width
                    text: "NDIlib is resolved at runtime (no SDK build dependency). Install the NDI runtime to activate."
                    color: Theme.textFaint; font.pixelSize: 9; wrapMode: Text.WordWrap
                }
            }
        }

        Rectangle {
            width: (parent.width - 12) / 2
            height: parent.height
            radius: 10
            color: Theme.card
            Column {
                anchors.fill: parent; anchors.margins: 12; spacing: 8
                Text { text: "DECKLINK"; color: Theme.text; font.pixelSize: 13; font.weight: Font.DemiBold }
                Row {
                    spacing: 6
                    Rectangle { width: 8; height: 8; radius: 4; anchors.verticalCenter: parent.verticalCenter
                               color: Mxu.deckLinkWindows.available ? Theme.green : Theme.pink }
                    Text { anchors.verticalCenter: parent.verticalCenter; text: Mxu.deckLinkWindows.available ? "SDK available" : "SDK not available"; color: Theme.textDim; font.pixelSize: 10 }
                }
                Rectangle {
                    width: 80; height: 26; radius: 7; color: Theme.surface
                    Text { anchors.centerIn: parent; text: "Refresh"; color: Theme.text; font.pixelSize: 10 }
                    MouseArea { anchors.fill: parent; onClicked: Mxu.deckLinkWindows.refresh() }
                }
                Repeater {
                    model: Mxu.deckLinkWindows.devices
                    delegate: Rectangle {
                        width: parent.width; height: 32; radius: 7; color: "#2c2c30"
                        Row {
                            anchors.fill: parent; anchors.leftMargin: 8; anchors.rightMargin: 8; spacing: 8
                            Text { width: parent.width - 70; anchors.verticalCenter: parent.verticalCenter; text: modelData.name || modelData.model || "DeckLink"; color: Theme.text; font.pixelSize: 10; elide: Text.ElideRight }
                            Rectangle {
                                width: 50; height: 22; radius: 6; color: Theme.accent
                                Text { anchors.centerIn: parent; text: "Start"; color: "white"; font.pixelSize: 9 }
                                MouseArea { anchors.fill: parent; onClicked: Mxu.deckLinkWindows.start(modelData.index || 0) }
                            }
                        }
                    }
                }
                Rectangle {
                    width: 90; height: 26; radius: 7; color: Theme.surface
                    Text { anchors.centerIn: parent; text: "Stop output"; color: Theme.text; font.pixelSize: 10 }
                    MouseArea { anchors.fill: parent; onClicked: Mxu.deckLinkWindows.stop() }
                }
                Text {
                    width: parent.width
                    text: "Full DeckLink features require Blackmagic Desktop Video + SDK at build time. Metal/macOS rendering has no Windows equivalent — Qt RHI is used."
                    color: Theme.textFaint; font.pixelSize: 9; wrapMode: Text.WordWrap
                }
            }
        }
    }
}
