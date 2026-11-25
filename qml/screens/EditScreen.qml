import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import "qrc:/qml/theme"
import "qrc:/qml/components"

// Visual slide editor (1280x800 in the mockup).
Item {
    id: root
    property int selectedSlide: 1
    property real zoom: 1.0

    Row {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        // ---------------- slide rail ----------------
        Rectangle {
            width: Theme.sidebarWidth
            height: parent.height
            radius: 10
            color: Theme.card
            clip: true

            Column {
                anchors.fill: parent
                anchors.margins: 4
                spacing: 14

                Row {
                    width: parent.width
                    height: 34
                    TrafficLights { anchors.verticalCenter: parent.verticalCenter; windowRef: Window.window }
                    Item { width: 8; height: 1 }
                    IconButton { anchors.verticalCenter: parent.verticalCenter; icon: "sidebar"; onClicked: Mxu.toggleSidebar() }
                }

                Text {
                    anchors.left: parent.left
                    anchors.leftMargin: 4
                    text: "Amazing Grace"
                    color: Theme.text
                    font.pixelSize: 13
                    font.weight: Font.DemiBold
                }

                Flickable {
                    width: parent.width
                    height: parent.height - 48
                    clip: true
                    contentHeight: railColumn.implicitHeight
                    Column {
                        id: railColumn
                        width: parent.width
                        spacing: 8
                        Repeater {
                            model: [
                                { text: "", n: 1 },
                                { text: "AMAZING GRACE, HOW SWEET THE SOUND", n: 2 },
                                { text: "I ONCE WAS LOST, BUT NOW AM FOUND", n: 3 },
                                { text: "TWAS GRACE THAT TAUGHT MY HEART", n: 4 },
                                { text: "MY CHAINS ARE GONE", n: 5 },
                            ]
                            delegate: Item {
                                width: railColumn.width
                                height: thumb.height + 16
                                Rectangle {
                                    id: thumb
                                    width: parent.width
                                    height: width * 9 / 16
                                    radius: 8
                                    color: Theme.checkerBase
                                    border.width: 2
                                    border.color: modelData.n === root.selectedSlide + 1 ? Mxu.accent : "#333"
                                    Checkerboard { anchors.fill: parent; anchors.margins: 2 }
                                    Text {
                                        anchors.centerIn: parent
                                        width: parent.width - 8
                                        text: modelData.text
                                        color: Theme.text
                                        font.pixelSize: 7
                                        font.weight: Font.Bold
                                        horizontalAlignment: Text.AlignHCenter
                                        wrapMode: Text.WordWrap
                                    }
                                    MouseArea {
                                        anchors.fill: parent
                                        onClicked: root.selectedSlide = modelData.n - 1
                                    }
                                }
                                Text {
                                    anchors.left: parent.left
                                    anchors.bottom: parent.bottom
                                    text: modelData.n
                                    color: Theme.textDim
                                    font.pixelSize: 10
                                }
                            }
                        }
                    }
                }
            }
        }

        // ---------------- editor ----------------
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
                        id: editorMode
                        model: ["Edit", "Present", "Stage"]
                        currentIndex: 0
                        onActivated: Mxu.setScreen(["edit", "present", "stage"][index])
                    }
                    Item { Layout.fillWidth: true; height: 1 }
                    PillButton { icon: "record"; iconSize: 16; onClicked: Mxu.toggleRecording() }
                }

                Rectangle {
                    width: parent.width
                    height: 46
                    radius: 10
                    color: Theme.card
                    Row {
                        anchors.fill: parent
                        anchors.leftMargin: 12
                        anchors.rightMargin: 12
                        spacing: 6
                        ToolButton { anchors.verticalCenter: parent.verticalCenter; text: "T"; onClicked: {} }
                        ToolButton { anchors.verticalCenter: parent.verticalCenter; icon: "shape"; onClicked: {} }
                        ToolButton { anchors.verticalCenter: parent.verticalCenter; icon: "image"; onClicked: {} }
                        ToolButton { anchors.verticalCenter: parent.verticalCenter; icon: "video"; onClicked: {} }
                        Item { width: Math.max(0, editorMode.width - 220); height: 1 }
                        Rectangle {
                            anchors.verticalCenter: parent.verticalCenter
                            radius: 7
                            color: Theme.surface
                            implicitWidth: undoText.implicitWidth + 20; implicitHeight: 26
                            Text { id: undoText; anchors.centerIn: parent; text: "Undo"; color: Theme.text; font.pixelSize: 11 }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.undo() }
                        }
                        Rectangle {
                            anchors.verticalCenter: parent.verticalCenter
                            radius: 7
                            color: Theme.surface
                            implicitWidth: redoText.implicitWidth + 20; implicitHeight: 26
                            Text { id: redoText; anchors.centerIn: parent; text: "Redo"; color: Theme.text; font.pixelSize: 11 }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.redo() }
                        }
                        Text { anchors.verticalCenter: parent.verticalCenter; text: "Zoom 100%"; color: Theme.textDim; font.pixelSize: 11 }
                    }
                }

                Rectangle {
                    width: parent.width
                    height: parent.height - 32 - 46 - 20
                    radius: 10
                    color: Theme.card
                    Item {
                        anchors.centerIn: parent
                        width: 640 * root.zoom
                        height: 360 * root.zoom
                        Rectangle {
                            anchors.fill: parent
                            radius: 6
                            color: Theme.checkerBase
                            border.color: "#444"
                            border.width: 1
                            clip: true
                            Checkerboard { anchors.fill: parent; anchors.margins: 1 }

                            Rectangle {
                                x: 70 * root.zoom
                                y: 130 * root.zoom
                                width: 500 * root.zoom
                                height: 100 * root.zoom
                                border.color: Mxu.accent
                                border.width: 2
                                color: "transparent"
                                Text {
                                    anchors.centerIn: parent
                                    width: parent.width - 10
                                    text: "AMAZING GRACE, HOW SWEET THE SOUND\nTHAT SAVED A WRETCH LIKE ME"
                                    color: Theme.text
                                    font.pixelSize: 22 * root.zoom
                                    font.weight: Font.Bold
                                    lineHeight: 1.4
                                    horizontalAlignment: Text.AlignHCenter
                                    wrapMode: Text.WordWrap
                                }
                                Repeater {
                                    model: [
                                        { x: -5, y: -5 }, { x: 1, y: -5 },
                                        { x: -5, y: 1 }, { x: 1, y: 1 },
                                    ]
                                    delegate: Rectangle {
                                        x: modelData.x === -5 ? -5 : parent.width - 4
                                        y: modelData.y === -5 ? -5 : parent.height - 4
                                        width: 9; height: 9
                                        color: "white"
                                        border.color: Mxu.accent
                                        border.width: 1.5
                                    }
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    drag.target: parent
                                    drag.axis: Drag.XAndYAxis
                                }
                            }
                        }
                    }
                }
            }
        }

        // ---------------- inspector ----------------
        Rectangle {
            width: 270
            height: parent.height
            radius: 10
            color: Theme.card
            clip: true
            Flickable {
                anchors.fill: parent
                anchors.margins: 12
                clip: true
                contentHeight: inspector.implicitHeight
                Column {
                    id: inspector
                    width: parent.width
                    spacing: 6
                    Text { text: "Inspector"; color: Theme.text; font.pixelSize: 13; font.weight: Font.DemiBold }

                    Text { text: "POSITION"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                    Row { width: parent.width; spacing: 6
                        SettingField { width: (parent.width - 6) / 2; label: "X"; value: "70" }
                        SettingField { width: (parent.width - 6) / 2; label: "Y"; value: "130" }
                    }

                    Text { text: "TEXT"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                    SettingField { width: parent.width; label: "Segoe UI Variable"; value: "Bold"; icon: "text" }
                    Row { width: parent.width; spacing: 6
                        SettingField { width: (parent.width - 6) / 2; label: "Size"; value: "22" }
                        SettingField { width: (parent.width - 6) / 2; label: "Color"; value: "FFFFFF" }
                    }

                    Text { text: "FILL AND STROKE"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                    SettingField { width: parent.width; label: "Fill"; value: "None" }
                    SettingField { width: parent.width; label: "Stroke"; value: "0 px" }

                    Text { text: "ANIMATION"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                    SettingField { width: parent.width; label: "Fade in"; value: "0.4 s" }

                    Text { text: "TRANSITION"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                    SettingField { width: parent.width; label: "Dissolve"; value: "0.6 s" }

                    Text { text: "LAYER"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                    Row { width: parent.width; spacing: 6
                        Rectangle { width: (parent.width - 6) / 2; height: 28; radius: 7; color: Theme.surface
                            Text { anchors.centerIn: parent; text: "Group"; color: Theme.text; font.pixelSize: 11 } }
                        Rectangle { width: (parent.width - 6) / 2; height: 28; radius: 7; color: Theme.surface
                            Text { anchors.centerIn: parent; text: "Bring forward"; color: Theme.text; font.pixelSize: 11 } }
                    }
                }
            }
        }
    }
}
