import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Dialogs
import "qrc:/qml/theme"
import "qrc:/qml/components"

// Media library screen (1280x800 in the mockup).
Item {
    id: root
    property int gridColumns: 4
    signal editMediaRequested(int index)

    Row {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        // ---------------- sidebar ----------------
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

                Rectangle {
                    width: parent.width
                    height: 28
                    radius: 7
                    color: Theme.inset
                    RowLayout {
                        anchors.fill: parent
                        anchors.leftMargin: 8
                        anchors.rightMargin: 8
                        AppIcon { name: "search"; size: 13; color: Theme.textDim }
                        TextField {
                            id: librarySearch
                            Layout.fillWidth: true
                            text: Mxu.libraryModel.search
                            color: Theme.text
                            font.pixelSize: 12
                            placeholderText: "Search"
                            placeholderTextColor: Theme.textDim
                            padding: 0
                            background: Rectangle { color: "transparent" }
                            onTextChanged: Mxu.libraryModel.search = text
                        }
                    }
                }

                Repeater {
                    model: Mxu.libraryModel.categories
                    delegate: Rectangle {
                        width: parent.width
                        height: 30
                        radius: 7
                        color: Mxu.libraryModel.category === modelData ? Theme.hover : "transparent"
                        Text { anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter; text: modelData; color: Theme.text; font.pixelSize: 12 }
                        MouseArea { anchors.fill: parent; onClicked: Mxu.libraryModel.category = modelData }
                    }
                }

                SectionLabel { width: parent.width; text: "FOLDERS"; labelColor: Theme.textDim; bothRules: true; showChevron: false }

                Repeater {
                    model: Mxu.libraryModel.folders
                    delegate: Rectangle {
                        width: parent.width
                        height: 30
                        radius: 7
                        color: "transparent"
                        Text { anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter; text: modelData; color: Theme.text; font.pixelSize: 12 }
                    }
                }

                Item { width: 1; height: Math.max(0, parent.height - 320) }
                Row {
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                    spacing: 16
                    Text { text: "+ New"; color: Theme.textDim; font.pixelSize: 12 }
                    Text { text: "+ New Folder"; color: Theme.textDim; font.pixelSize: 12
                        MouseArea { anchors.fill: parent; onClicked: folderDialog.open() } }
                }
            }
        }

        // ---------------- library grid ----------------
        Item {
            width: parent.width - Theme.sidebarWidth - 270 - 20
            height: parent.height

            Column {
                anchors.fill: parent
                spacing: 10

                RowLayout {
                    width: parent.width
                    height: 32
                    Item { Layout.fillWidth: true; Layout.preferredHeight: 1 }
                    Segmented {
                        id: libraryMode
                        model: ["Edit", "Present", "Stage"]
                        currentIndex: -1
                        onActivated: Mxu.setScreen(["edit", "present", "stage"][index])
                    }
                    Item { Layout.fillWidth: true; Layout.preferredHeight: 1 }
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
                        Text { text: "Drive"; color: Theme.textDim; font.pixelSize: 12 }
                        Text { text: "/"; color: Theme.textDim; font.pixelSize: 12 }
                        Text { text: Mxu.libraryModel.category; color: Theme.text; font.pixelSize: 12 }
                        Item { Layout.fillWidth: true; Layout.preferredHeight: 1 }
                        Rectangle {
                            radius: 7; color: Theme.surface
                            implicitWidth: 62; implicitHeight: 28
                            Text { anchors.centerIn: parent; text: "Import"; color: Theme.text; font.pixelSize: 12 }
                            MouseArea { anchors.fill: parent; onClicked: importDialog.open() }
                        }
                        Rectangle {
                            radius: 7; color: Theme.surface
                            implicitWidth: 52; implicitHeight: 28
                            Text { anchors.centerIn: parent; text: "Grid"; color: Theme.text; font.pixelSize: 12 }
                            MouseArea { anchors.fill: parent; onClicked: root.gridColumns = root.gridColumns === 4 ? 2 : 4 }
                        }
                    }
                }

                Rectangle {
                    width: parent.width
                    height: parent.height - 32 - 48 - 20
                    radius: 10
                    color: Theme.card
                    clip: true
                    Flickable {
                        anchors.fill: parent
                        anchors.margins: 12
                        clip: true
                        contentHeight: grid.implicitHeight
                        Grid {
                            id: grid
                            width: parent.width
                            columns: root.gridColumns
                            spacing: 16
                            property real cellW: (grid.width - (root.gridColumns - 1) * 16) / root.gridColumns
                            Repeater {
                                model: Mxu.mediaService.items
                                delegate: Column {
                                    width: grid.cellW
                                    Rectangle {
                                        width: grid.cellW
                                        height: width * 9 / 16
                                        radius: 8
                                        border.color: modelData.selected ? Mxu.accent : "#3a3a3e"
                                        border.width: modelData.selected ? 2 : 1
                                        gradient: Gradient {
                                            orientation: Gradient.Horizontal
                                            GradientStop { position: 0; color: modelData.from }
                                            GradientStop { position: 1; color: modelData.to }
                                        }
                                        Image {
                                            anchors.fill: parent
                                            source: modelData.thumbnail || ""
                                            fillMode: Image.PreserveAspectCrop
                                            asynchronous: true
                                        }
                                        MouseArea {
                                            anchors.fill: parent
                                            onClicked: Mxu.libraryModel.selectItem(modelData.index)
                                        }
                                    }
                                    Text {
                                        width: parent.width
                                        text: modelData.name
                                        color: Theme.text
                                        font.pixelSize: 12
                                        elide: Text.ElideRight
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        // ---------------- details ----------------
        Rectangle {
            width: 270
            height: parent.height
            radius: 10
            color: Theme.card
            Column {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 6

                Text { text: "Details"; color: Theme.text; font.pixelSize: 12; font.weight: Font.DemiBold }

                Rectangle {
                    width: parent.width
                    height: width * 9 / 16
                    radius: 8
                    border.color: "#3a3a3e"
                    border.width: 1
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0; color: Mxu.libraryModel.selectedItem.from || "#333" }
                        GradientStop { position: 1; color: Mxu.libraryModel.selectedItem.to || "#111" }
                    }
                }
                Text { text: Mxu.libraryModel.selectedItem.name; color: Theme.text; font.pixelSize: 12; font.weight: Font.DemiBold }

                Text { text: "INFO"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                RowLayout { width: parent.width
                    Text { text: "Type"; color: Theme.textDim; font.pixelSize: 12 }
                    Item { Layout.fillWidth: true; Layout.preferredHeight: 1 }
                    Text { text: Mxu.libraryModel.selectedItem.type; color: Theme.text; font.pixelSize: 12 } }
                RowLayout { width: parent.width
                    Text { text: "Size"; color: Theme.textDim; font.pixelSize: 12 }
                    Item { Layout.fillWidth: true; Layout.preferredHeight: 1 }
                    Text { text: Mxu.libraryModel.selectedItem.size; color: Theme.text; font.pixelSize: 12 } }
                RowLayout { width: parent.width
                    Text { text: "File"; color: Theme.textDim; font.pixelSize: 12 }
                    Item { Layout.fillWidth: true; Layout.preferredHeight: 1 }
                    Text { text: Mxu.libraryModel.selectedItem.fileSize; color: Theme.text; font.pixelSize: 12 } }

                Text { text: "ACTIONS"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                Rectangle {
                    width: parent.width; height: 30; radius: 9; color: Theme.surface
                    Text { anchors.centerIn: parent; text: "Open in Media Editor"; color: Theme.text; font.pixelSize: 11; font.weight: Font.DemiBold }
                    MouseArea { anchors.fill: parent; onClicked: root.editMediaRequested(Mxu.libraryModel.selectedIndex) }
                }
                Rectangle {
                    width: parent.width; height: 30; radius: 9; color: Mxu.accent
                    Text { anchors.centerIn: parent; text: "Add to Service Flow"; color: "white"; font.pixelSize: 12; font.weight: Font.DemiBold }
                    MouseArea { anchors.fill: parent; onClicked: Mxu.libraryModel.addToServiceFlow(Mxu.libraryModel.selectedIndex) }
                }
                Rectangle {
                    width: parent.width; height: 30; radius: 9; color: Theme.surface
                    Text { anchors.centerIn: parent; text: "Set as background"; color: Theme.text; font.pixelSize: 12 }
                    MouseArea { anchors.fill: parent; onClicked: Mxu.mediaService.setBackground(Mxu.libraryModel.selectedItem.name) }
                }
                Rectangle {
                    width: parent.width; height: 28; radius: 9; color: "#3a2326"
                    Text { anchors.centerIn: parent; text: "Remove"; color: Theme.pink; font.pixelSize: 11 }
                    MouseArea { anchors.fill: parent; onClicked: Mxu.mediaService.removeMedia(Mxu.libraryModel.selectedIndex) }
                }
            }
        }
    }

    FolderDialog {
        id: folderDialog
        title: "Import folder"
        onAccepted: Mxu.mediaService.importFolder(selectedFolder)
    }

    FileDialog {
        id: importDialog
        title: "Import media"
        nameFilters: ["Images (*.png *.jpg *.jpeg)", "Videos (*.mp4 *.mov *.mkv)", "All files (*)"]
        onAccepted: Mxu.mediaService.importFile(selectedFile)
    }
}
