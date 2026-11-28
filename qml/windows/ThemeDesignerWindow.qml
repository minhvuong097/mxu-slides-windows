import QtQuick
import QtQuick.Controls
import QtQuick.Window
import "qrc:/qml/theme"

// Theme designer (Mac ThemeExplorerView / ThemeDesigns): editable color
// tokens, persisted presets and a live preview bound to Mxu.themeService.
Window {
    id: designer
    width: 760
    height: 480
    minimumWidth: 660
    minimumHeight: 400
    title: "Theme Designer — MxU Slides"
    color: Mxu.themeService.color("bg")
    flags: Qt.Window
    visible: false

    readonly property var keys: ["bg", "card", "accent", "text", "dim", "green", "pink", "yellow"]

    function open() { visible = true }

    Row {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 12

        Rectangle {
            width: 250
            height: parent.height
            radius: 10
            color: Mxu.themeService.color("card")
            Column {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 8
                Text { text: "THEMES"; color: Mxu.themeService.color("text"); font.pixelSize: 11; font.weight: Font.Bold }
                Repeater {
                    model: Mxu.themeService.themes
                    delegate: Rectangle {
                        width: parent.width; height: 42; radius: 8
                        color: Mxu.themeService.currentId === modelData.id ? "#38383c" : "#2c2c30"
                        border.color: Mxu.themeService.currentId === modelData.id ? Mxu.themeService.color("accent") : "transparent"
                        border.width: 1
                        Row {
                            anchors.fill: parent; anchors.leftMargin: 8; anchors.rightMargin: 8; spacing: 6
                            Rectangle { width: 20; height: 20; radius: 5; anchors.verticalCenter: parent.verticalCenter
                                        color: modelData.colors.accent || Mxu.themeService.color("accent") }
                            Text { width: 100; anchors.verticalCenter: parent.verticalCenter; text: modelData.name; color: Mxu.themeService.color("text"); font.pixelSize: 11; elide: Text.ElideRight }
                            Rectangle {
                                width: 42; height: 22; radius: 6; anchors.verticalCenter: parent.verticalCenter
                                color: Mxu.themeService.color("accent")
                                Text { anchors.centerIn: parent; text: "Apply"; color: "white"; font.pixelSize: 9 }
                                MouseArea { anchors.fill: parent; onClicked: Mxu.themeService.apply(modelData.id) }
                            }
                            Rectangle {
                                width: 22; height: 22; radius: 6; anchors.verticalCenter: parent.verticalCenter
                                color: "#38383c"
                                Text { anchors.centerIn: parent; text: "✕"; color: Mxu.themeService.color("dim"); font.pixelSize: 9 }
                                MouseArea { anchors.fill: parent; onClicked: Mxu.themeService.remove(modelData.id) }
                            }
                        }
                    }
                }
                Rectangle {
                    width: parent.width; height: 28; radius: 7; color: Mxu.themeService.color("accent")
                    Text { anchors.centerIn: parent; text: "+ Save as new theme"; color: "white"; font.pixelSize: 10; font.weight: Font.Bold }
                    MouseArea { anchors.fill: parent; onClicked: Mxu.themeService.addTheme("Custom " + (Mxu.themeService.themes.length + 1), Mxu.themeService.current) }
                }
            }
        }

        Flickable {
            width: parent.width - 262
            height: parent.height
            contentWidth: width
            contentHeight: editor.implicitHeight
            clip: true
            Column {
                id: editor
                width: parent.width
                spacing: 8

                Text { text: "COLOR TOKENS"; color: Mxu.themeService.color("text"); font.pixelSize: 11; font.weight: Font.Bold }
                Repeater {
                    model: designer.keys
                    delegate: Row {
                        width: parent.width; spacing: 8
                        Rectangle { width: 24; height: 24; radius: 6; color: Mxu.themeService.color(modelData); border.color: Theme.border }
                        Text { width: 70; anchors.verticalCenter: parent.verticalCenter; text: modelData; color: Mxu.themeService.color("text"); font.pixelSize: 11 }
                        TextField {
                            width: 130; height: 26
                            text: Mxu.themeService.color(modelData)
                            color: Mxu.themeService.color("text"); font.pixelSize: 11
                            background: Rectangle { radius: 6; color: Mxu.themeService.color("bg") }
                            onEditingFinished: Mxu.themeService.setColor(modelData, text)
                        }
                    }
                }

                Text { text: "PREVIEW"; color: Mxu.themeService.color("text"); font.pixelSize: 11; font.weight: Font.Bold }
                Rectangle {
                    width: parent.width; height: 120; radius: 10
                    color: Mxu.themeService.color("card")
                    Column {
                        anchors.fill: parent; anchors.margins: 12; spacing: 6
                        Text { text: "PROSLIDES"; color: Mxu.themeService.color("text"); font.pixelSize: 16; font.weight: Font.Bold }
                        Rectangle { width: 120; height: 26; radius: 7; color: Mxu.themeService.color("accent")
                            Text { anchors.centerIn: parent; text: "Present"; color: "white"; font.pixelSize: 10; font.weight: Font.Bold } }
                        Row { spacing: 6
                            Rectangle { width: 60; height: 12; radius: 4; color: Mxu.themeService.color("green") }
                            Rectangle { width: 60; height: 12; radius: 4; color: Mxu.themeService.color("yellow") }
                            Rectangle { width: 60; height: 12; radius: 4; color: Mxu.themeService.color("pink") }
                            Text { text: Mxu.accent; color: Mxu.themeService.color("dim"); font.pixelSize: 9 } }
                    }
                }
            }
        }
    }
}
