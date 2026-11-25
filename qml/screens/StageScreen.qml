import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import "qrc:/qml/theme"
import "qrc:/qml/components"

// Stage display configuration screen (1280x800 in the mockup).
Item {
    id: root

    Row {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        // ---------------- layouts ----------------
        Rectangle {
            width: Theme.sidebarWidth
            height: parent.height
            radius: 10
            color: Theme.card
            Column {
                anchors.fill: parent
                anchors.margins: 4
                spacing: 2

                Row {
                    width: parent.width
                    height: 34
                    TrafficLights { anchors.verticalCenter: parent.verticalCenter; windowRef: Window.window }
                    Item { width: 8; height: 1 }
                    IconButton { anchors.verticalCenter: parent.verticalCenter; icon: "sidebar"; onClicked: Mxu.toggleSidebar() }
                }
                Text { anchors.left: parent.left; anchors.leftMargin: 6; text: "Stage Layouts"; color: Theme.text; font.pixelSize: 13; font.weight: Font.DemiBold }

                Repeater {
                    model: ["Lyrics + Next", "Chords", "Timer only", "Message wall"]
                    delegate: Rectangle {
                        width: parent.width
                        height: 36
                        radius: 7
                        color: Mxu.stageLayout === modelData ? Theme.hover : "transparent"
                        Text { anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter; text: modelData; color: Theme.text; font.pixelSize: 14 }
                        MouseArea { anchors.fill: parent; onClicked: Mxu.setStageLayout(modelData) }
                    }
                }

                Item { width: 1; height: Math.max(0, parent.height - 210) }
                Text { anchors.left: parent.left; anchors.leftMargin: 6; text: Mxu.connectedScreens; color: Theme.textDim; font.pixelSize: 11 }
            }
        }

        // ---------------- stage preview ----------------
        Item {
            width: parent.width - Theme.sidebarWidth - 270 - 20
            height: parent.height

            Column {
                anchors.fill: parent
                spacing: 10

                RowLayout {
                    width: parent.width
                    height: 32
                    Item { Layout.fillWidth: true; height: 1 }
                    Segmented {
                        id: stageMode
                        model: ["Edit", "Present", "Stage"]
                        currentIndex: 2
                        onActivated: Mxu.setScreen(["edit", "present", "stage"][index])
                    }
                    Item { Layout.fillWidth: true; height: 1 }
                    PillButton { icon: "record"; iconSize: 16; onClicked: Mxu.toggleRecording() }
                }

                Rectangle {
                    width: parent.width
                    height: 48
                    radius: 10
                    color: Theme.card
                    RowLayout {
                        anchors.fill: parent
                        anchors.leftMargin: 12
                        anchors.rightMargin: 12
                        Text { text: "Stage Display — " + Mxu.stageLayout; color: Theme.text; font.pixelSize: 13; font.weight: Font.DemiBold }
                        Item { Layout.fillWidth: true; height: 1 }
                        Text { text: "1920 x 1080 · Display 3"; color: Theme.textDim; font.pixelSize: 12 }
                    }
                }

                Rectangle {
                    width: parent.width
                    height: parent.height - 32 - 48 - 20
                    radius: 10
                    color: "black"
                    border.color: "#444"
                    border.width: 1
                    clip: true

                    Column {
                        anchors.fill: parent
                        anchors.margins: 18
                        spacing: 14

                        RowLayout {
                            width: parent.width
                            Text { text: Mxu.serviceClock; color: Theme.text; font.pixelSize: 30; font.weight: Font.Bold }
                            Item { Layout.fillWidth: true; height: 1 }
                            Text { visible: Mxu.sectionTimerVisible; text: Mxu.serviceTimerText; color: Theme.green; font.pixelSize: 30; font.weight: Font.Bold }
                        }

                        Rectangle {
                            width: parent.width
                            height: Math.max(160, parent.height - 250)
                            radius: 8
                            color: Theme.checkerBase
                            border.color: "white"
                            border.width: 2
                            Checkerboard { anchors.fill: parent; anchors.margins: 2 }
                            Text {
                                anchors.centerIn: parent
                                width: parent.width - 20
                                text: "AMAZING GRACE, HOW SWEET THE SOUND\nTHAT SAVED A WRETCH LIKE ME"
                                color: Theme.text
                                font.pixelSize: Mxu.lyricsFontSize
                                font.weight: Font.Bold
                                lineHeight: 1.4
                                horizontalAlignment: Text.AlignHCenter
                            }
                            Text {
                                anchors.left: parent.left
                                anchors.leftMargin: 12
                                anchors.top: parent.top
                                anchors.topMargin: 8
                                text: Mxu.currentChord
                                color: Theme.yellow
                                font.pixelSize: 20
                            }
                            Rectangle {
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin: -11
                                anchors.horizontalCenter: parent.horizontalCenter
                                color: "black"
                                Text { text: "CURRENT SLIDE"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.DemiBold }
                            }
                        }

                        Rectangle {
                            width: parent.width
                            height: 64
                            radius: 8
                            border.color: Theme.yellow
                            border.width: 2
                            color: "transparent"
                            Text {
                                anchors.centerIn: parent
                                width: parent.width - 20
                                text: Mxu.nextSlideText
                                color: Theme.text
                                font.pixelSize: 20
                                font.weight: Font.DemiBold
                                horizontalAlignment: Text.AlignHCenter
                                elide: Text.ElideRight
                            }
                            Rectangle {
                                anchors.top: parent.top
                                anchors.topMargin: -10
                                anchors.right: parent.right
                                anchors.rightMargin: 12
                                color: "black"
                                Text { text: "NEXT SLIDE"; color: Theme.textDim; font.pixelSize: 11 }
                            }
                        }

                        Rectangle {
                            width: parent.width
                            height: 38
                            radius: 8
                            color: Mxu.accent
                            Text {
                                anchors.centerIn: parent
                                width: parent.width - 28
                                text: "Message: " + Mxu.stageMessage
                                color: "white"
                                font.pixelSize: 13
                                font.weight: Font.DemiBold
                                elide: Text.ElideRight
                            }
                        }
                    }
                }
            }
        }

        // ---------------- stage settings ----------------
        Rectangle {
            width: 270
            height: parent.height
            radius: 10
            color: Theme.card
            Flickable {
                anchors.fill: parent
                anchors.margins: 12
                clip: true
                contentHeight: settingsColumn.implicitHeight

                Column {
                    id: settingsColumn
                    width: parent.width
                    spacing: 2

                    Text { text: "Stage Settings"; color: Theme.text; font.pixelSize: 13; font.weight: Font.DemiBold }

                    Text { text: "DISPLAY"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                    SettingField { width: parent.width; label: "Output"; value: "Display 3" }

                    Text { text: "LAYOUT"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                    SettingField { width: parent.width; label: Mxu.stageLayout; value: "Change" }

                    Text { text: "SHOW"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                    SettingField { width: parent.width; label: "Chords"; value: Mxu.chordsVisible ? "On" : "Off" }
                    SettingField { width: parent.width; label: "Clock"; value: Mxu.clockVisible ? "On" : "Off" }
                    SettingField { width: parent.width; label: "Section timer"; value: Mxu.sectionTimerVisible ? "On" : "Off" }

                    Text { text: "FONT SIZE"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                    SettingField { width: parent.width; label: "Lyrics"; value: Mxu.lyricsFontSize + " px" }

                    Text { text: "STAGE MESSAGE"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                    Rectangle {
                        width: parent.width
                        height: 60
                        radius: 7
                        color: Theme.inset
                        TextInput {
                            id: stageMessageInput
                            anchors.fill: parent
                            anchors.margins: 10
                            text: Mxu.stageMessage
                            color: Theme.text
                            font.pixelSize: 12
                            wrapMode: TextInput.WordWrap
                        }
                    }
                    Rectangle {
                        width: parent.width
                        height: 30
                        radius: 9
                        color: Mxu.accent
                        Text { anchors.centerIn: parent; text: "Send to stage"; color: "white"; font.pixelSize: 12; font.weight: Font.DemiBold }
                        MouseArea { anchors.fill: parent; onClicked: Mxu.sendStageMessage(stageMessageInput.text) }
                    }
                }
            }
        }
    }
}
