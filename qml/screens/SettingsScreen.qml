import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import "qrc:/qml/theme"
import "qrc:/qml/components"

// Settings — Outputs pane (1280x800 in the mockup).
Item {
    id: root
    property string pane: "Outputs"

    Row {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        // ---------------- categories ----------------
        Rectangle {
            width: Theme.sidebarWidth
            height: parent.height
            radius: 10
            color: Theme.card
            Column {
                anchors.fill: parent
                anchors.margins: 4
                spacing: 4

                Row {
                    width: parent.width
                    height: 34
                    TrafficLights { anchors.verticalCenter: parent.verticalCenter; windowRef: Window.window }
                    Item { width: 8; height: 1 }
                    IconButton { anchors.verticalCenter: parent.verticalCenter; icon: "sidebar"; onClicked: Mxu.toggleSidebar() }
                }
                Text { anchors.left: parent.left; anchors.leftMargin: 6; text: "Settings"; color: Theme.text; font.pixelSize: 13; font.weight: Font.DemiBold }

                Repeater {
                    model: [
                        { name: "General", color: "#8e8e93", icon: "settings" },
                        { name: "Outputs", color: "#0a84ff", icon: "monitor" },
                        { name: "Audio", color: "#ff375f", icon: "audio" },
                        { name: "Stream and NDI", color: "#bf5af2", icon: "ndi" },
                        { name: "MIDI and Timecode", color: "#ff9f0a", icon: "clock" },
                        { name: "Remote", color: "#30d158", icon: "remote" },
                        { name: "Shortcuts", color: "#5ac8fa", icon: "keyboard" },
                        { name: "About", color: "#8e8e93", icon: "info" },
                    ]
                    delegate: Rectangle {
                        width: parent.width
                        height: 30
                        radius: 7
                        color: modelData.name === root.pane ? Theme.hover : "transparent"
                        RowLayout {
                            anchors.fill: parent
                            anchors.leftMargin: 8
                            anchors.rightMargin: 8
                            spacing: 9
                            Rectangle {
                                width: 22; height: 22; radius: 6
                                color: modelData.color
                                AppIcon { anchors.centerIn: parent; name: modelData.icon; size: 13; color: "white" }
                            }
                            Text { Layout.fillWidth: true; text: modelData.name; color: Theme.text; font.pixelSize: 12 }
                        }
                        MouseArea { anchors.fill: parent; onClicked: root.pane = modelData.name }
                    }
                }
            }
        }

        // ---------------- output settings ----------------
        Item {
            width: parent.width - Theme.sidebarWidth - 260 - 20
            height: parent.height

            Column {
                anchors.fill: parent
                spacing: 10

                RowLayout {
                    width: parent.width
                    height: 32
                    Item { Layout.fillWidth: true; height: 1 }
                    Segmented {
                        id: settingsMode
                        model: ["Edit", "Present", "Stage"]
                        currentIndex: -1
                        onActivated: Mxu.setScreen(["edit", "present", "stage"][index])
                    }
                    Item { Layout.fillWidth: true; height: 1 }
                    PillButton { icon: "record"; iconSize: 16; onClicked: Mxu.toggleRecording() }
                }

                Rectangle {
                    visible: root.pane === "Outputs"
                    width: parent.width
                    height: parent.height - 42
                    radius: 10
                    color: Theme.card
                    Flickable {
                        anchors.fill: parent
                        anchors.margins: 12
                        clip: true
                        contentHeight: form.implicitHeight
                        Column {
                            id: form
                            width: parent.width
                            spacing: 2

                            Row {
                                width: parent.width
                                height: 36
                                spacing: 10
                                Rectangle {
                                    width: 28; height: 28; radius: 6; color: Theme.accent
                                    AppIcon { anchors.centerIn: parent; name: "monitor"; size: 16; color: "white" }
                                }
                                Text { anchors.verticalCenter: parent.verticalCenter; text: "Outputs"; color: Theme.text; font.pixelSize: 16; font.weight: Font.DemiBold }
                            }

                            Text { text: "DISPLAYS"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                            SettingRow { width: parent.width; label: "Main output"; value: Mxu.setting("mainOutput") }
                            SettingRow { width: parent.width; label: "Stage display"; value: Mxu.setting("stageDisplay"); fieldWidth: 120 }
                            SettingRow {
                                width: parent.width; label: "Confidence monitor"; toggle: true
                                checked: Mxu.setting("confidenceMonitor")
                                onToggled: Mxu.setSetting("confidenceMonitor", value)
                            }
                            SettingRow {
                                width: parent.width; label: "Always on top of taskbar"; toggle: true
                                checked: Mxu.setting("alwaysOnTop")
                                onToggled: Mxu.setSetting("alwaysOnTop", value)
                            }

                            Text { text: "VIDEO OUTPUT"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                            SettingRow {
                                width: parent.width; label: "NDI output"; toggle: true
                                checked: Mxu.setting("ndiOutput")
                                onToggled: Mxu.setSetting("ndiOutput", value)
                            }
                            SettingRow {
                                width: parent.width; label: "DeckLink output"; toggle: true
                                checked: Mxu.setting("decklinkOutput")
                                onToggled: Mxu.setSetting("decklinkOutput", value)
                            }
                            SettingRow {
                                width: parent.width; label: "Key output (alpha)"; toggle: true
                                checked: Mxu.setting("keyOutput")
                                onToggled: Mxu.setSetting("keyOutput", value)
                            }

                            Text { text: "PERFORMANCE"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                            SettingRow {
                                width: parent.width; label: "GPU acceleration (DirectX 12)"; toggle: true
                                checked: Mxu.setting("gpuAcceleration")
                                onToggled: Mxu.setSetting("gpuAcceleration", value)
                            }
                            SettingRow { width: parent.width; label: "Frame rate"; value: Mxu.setting("frameRate"); fieldWidth: 120 }
                        }
                    }
                }

                Rectangle {
                    visible: root.pane === "Remote"
                    width: parent.width
                    height: parent.height - 42
                    radius: 10
                    color: Theme.card
                    Column {
                        anchors.fill: parent
                        anchors.margins: 12
                        spacing: 6

                        Row {
                            width: parent.width
                            height: 36
                            spacing: 10
                            Rectangle {
                                width: 28; height: 28; radius: 6; color: Theme.green
                                AppIcon { anchors.centerIn: parent; name: "remote"; size: 16; color: "white" }
                            }
                            Text { anchors.verticalCenter: parent.verticalCenter; text: "Local API"; color: Theme.text; font.pixelSize: 16; font.weight: Font.DemiBold }
                        }

                        Text { text: "SERVER"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                        SettingRow {
                            width: parent.width; label: "Enable Local API"; toggle: true
                            checked: Mxu.localApiEnabled
                            onToggled: Mxu.setLocalApiEnabled(value)
                        }
                        SettingField { width: parent.width; label: "Address"; value: Mxu.localApiEnabled ? "http://127.0.0.1:6980" : "Off" }
                        SettingField { width: parent.width; label: "WebSocket"; value: "ws://127.0.0.1:6981" }

                        Text { text: "AUTHENTICATION"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                        Text {
                            width: parent.width
                            text: "Bearer token"
                            color: Theme.textDim
                            font.pixelSize: 11
                        }
                        Rectangle {
                            width: parent.width
                            height: 32
                            radius: 7
                            color: Theme.inset
                            Text {
                                anchors.fill: parent
                                anchors.margins: 8
                                text: Mxu.localApiToken
                                color: Theme.text
                                font.pixelSize: 11
                                elide: Text.ElideMiddle
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                        Rectangle {
                            width: 180; height: 30; radius: 9; color: Theme.accent
                            Text { anchors.centerIn: parent; text: "Regenerate token"; color: "white"; font.pixelSize: 12; font.weight: Font.DemiBold }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.regenerateLocalApiToken() }
                        }
                    }
                }
            }
        }

        // ---------------- preview + status ----------------
        Rectangle {
            width: 260
            height: parent.height
            radius: 10
            color: Theme.card
            Column {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 6

                Row {
                    spacing: 6
                    AppIcon { anchors.verticalCenter: parent.verticalCenter; name: "eye"; size: 14; color: Theme.textDim }
                    Text { anchors.verticalCenter: parent.verticalCenter; text: "Preview"; color: Theme.text; font.pixelSize: 13; font.weight: Font.DemiBold }
                }

                Rectangle {
                    width: parent.width
                    height: width * 9 / 16
                    radius: 6
                    color: "black"
                    gradient: Gradient {
                        GradientStop { position: 0; color: "#3b3b52" }
                        GradientStop { position: 0.7; color: "black" }
                    }
                    Text { anchors.centerIn: parent; text: "PROSLIDES"; color: Theme.text; font.pixelSize: 14; font.weight: Font.Bold; font.letterSpacing: 0.56 }
                }

                Text { text: "STATUS"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                RowLayout { width: parent.width; height: 28
                    Text { text: "Main output"; color: Theme.textDim; font.pixelSize: 12 }
                    Item { Layout.fillWidth: true; height: 1 }
                    Rectangle { width: 7; height: 7; radius: 4; color: Theme.green }
                    Text { text: "Ready"; color: Theme.green; font.pixelSize: 12; font.weight: Font.DemiBold } }
                RowLayout { width: parent.width; height: 28
                    Text { text: "NDI"; color: Theme.textDim; font.pixelSize: 12 }
                    Item { Layout.fillWidth: true; height: 1 }
                    Rectangle { width: 7; height: 7; radius: 4; color: Theme.green }
                    Text { text: Mxu.setting("ndiOutput") ? "Sending" : "Off"; color: Mxu.setting("ndiOutput") ? Theme.green : Theme.textDim; font.pixelSize: 12; font.weight: Font.DemiBold } }
                RowLayout { width: parent.width; height: 28
                    Text { text: "DeckLink"; color: Theme.textDim; font.pixelSize: 12 }
                    Item { Layout.fillWidth: true; height: 1 }
                    Rectangle { width: 7; height: 7; radius: 4; color: Theme.textFaint }
                    Text { text: Mxu.setting("decklinkOutput") ? "Sending" : "Off"; color: Mxu.setting("decklinkOutput") ? Theme.green : Theme.textDim; font.pixelSize: 12; font.weight: Font.DemiBold } }

                Rectangle {
                    width: parent.width
                    height: 34
                    radius: 9
                    color: Mxu.accent
                    Row {
                        anchors.centerIn: parent
                        spacing: 8
                        AppIcon { anchors.verticalCenter: parent.verticalCenter; name: "monitor"; size: 14; color: "white" }
                        Text { anchors.verticalCenter: parent.verticalCenter; text: "Identify displays"; color: "white"; font.pixelSize: 12; font.weight: Font.DemiBold }
                    }
                    MouseArea { anchors.fill: parent; onClicked: Mxu.identifyDisplays() }
                }
            }
        }
    }
}
