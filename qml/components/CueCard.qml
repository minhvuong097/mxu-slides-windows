import QtQuick
import QtQuick.Layouts
import "qrc:/qml/theme"
import "qrc:/qml/components"

Rectangle {
    id: card
    property var cue: ({})
    property bool current: false
    property real cellW: Math.max(80, (card.width - 40) / 3)
    signal notesClicked()
    signal slideClicked(int index)

    radius: 10
    color: Theme.card
    border.color: current ? Qt.rgba(10/255, 132/255, 1, 0.35) : "transparent"
    border.width: current ? 1 : 0

    implicitHeight: content.implicitHeight + 20

    Column {
        id: content
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10
        spacing: 0

        // ---- header ----------------------------------------------------
        Row {
            width: parent.width
            height: 26
            spacing: 6

            AppIcon { anchors.verticalCenter: parent.verticalCenter; name: "copy"; size: 18; color: Theme.textDim }
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: card.cue.title || ""
                color: Theme.text
                font.pixelSize: 12
                font.weight: Font.DemiBold
            }
            Rectangle {
                anchors.verticalCenter: parent.verticalCenter
                radius: 7
                color: "transparent"
                implicitWidth: metaText.implicitWidth + 16
                implicitHeight: 20
                Text {
                    id: metaText
                    anchors.centerIn: parent
                    text: card.cue.meta || ""
                    color: Theme.textDim
                    font.pixelSize: 11
                }
            }
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: card.cue.key || ""
                color: Theme.textDim
                font.pixelSize: 11
            }
            Item { width: 4; height: 1 }
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: card.cue.slideLabel || ""
                color: Theme.textDim
                font.pixelSize: 11
            }
            Item { Layout.fillWidth: true; width: Math.max(0, content.width - x - 34); height: 1 }
            Rectangle {
                anchors.verticalCenter: parent.verticalCenter
                width: 26; height: 26
                radius: 7
                color: card.cue.notesHighlighted ? Qt.rgba(10/255, 132/255, 1, 0.16) : Theme.iconButton
                border.color: card.cue.notesHighlighted ? Qt.rgba(10/255, 132/255, 1, 0.4) : "transparent"
                border.width: card.cue.notesHighlighted ? 1 : 0
                AppIcon {
                    anchors.centerIn: parent
                    name: "notes"
                    size: 14
                    color: card.cue.notesHighlighted ? Theme.accent : Theme.textDim
                }
                MouseArea { anchors.fill: parent; onClicked: card.notesClicked() }
            }
        }

        // ---- description ----------------------------------------------
        Rectangle {
            visible: (card.cue.description || "") !== ""
            width: parent.width
            radius: 7
            color: Theme.inset
            implicitHeight: descCol.implicitHeight + 14
            anchors.topMargin: 8
            Column {
                id: descCol
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 10
                Text {
                    text: "Description"
                    color: Theme.textDim
                    font.pixelSize: 11
                    font.weight: Font.DemiBold
                }
                Text {
                    width: parent.width - 20
                    text: card.cue.description || ""
                    color: Theme.text
                    font.pixelSize: 11
                    lineHeight: 1.5
                    wrapMode: Text.WordWrap
                }
            }
            AppIcon {
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.top: parent.top
                anchors.topMargin: 8
                name: "notes"
                size: 16
                color: Theme.textDim
            }
        }

        // ---- picture show (Pre-roll) -----------------------------------
        Grid {
            visible: !!card.cue.pictureShow
            width: parent.width
            columns: 3
            spacing: 10
            anchors.topMargin: 8

            Repeater {
                model: card.cue.posters || []
                delegate: Column {
                    width: card.cellW
                    GradientThumb {
                        width: card.cellW
                        height: width * 9 / 16
                        from: modelData.from
                        to: modelData.to
                        label: modelData.title
                        labelSize: 18
                    }
                    Text {
                        width: parent.width
                        text: modelData.caption
                        color: Theme.textDim
                        font.pixelSize: 11
                        elide: Text.ElideRight
                    }
                }
            }
        }

        // ---- lyric cue: chips ------------------------------------------
        Row {
            visible: !card.cue.pictureShow
            width: parent.width
            height: 26
            anchors.topMargin: 6
            spacing: 4
            clip: true
            Repeater {
                model: card.cue.chips || []
                delegate: Rectangle {
                    radius: 99
                    color: modelData.color
                    implicitWidth: chipText.implicitWidth + 14
                    implicitHeight: 19
                    Text {
                        id: chipText
                        anchors.centerIn: parent
                        text: modelData.name
                        color: "white"
                        font.pixelSize: 10
                        font.weight: Font.DemiBold
                    }
                }
            }
            Rectangle {
                radius: 99
                color: "transparent"
                implicitWidth: 24; implicitHeight: 19
                Row {
                    anchors.centerIn: parent
                    spacing: 1
                    AppIcon { name: "plus"; size: 17; color: Theme.textBright }
                    AppIcon { name: "chevronDown"; size: 11; color: Theme.textBright }
                }
            }
        }

        // ---- lyric cue: slide grid -------------------------------------
        Grid {
            visible: !card.cue.pictureShow
            width: parent.width
            columns: 3
            spacing: 10
            anchors.topMargin: 4

            Repeater {
                model: card.cue.slides || []
                delegate: Column {
                    property int slideIndex: modelData.index
                    width: card.cellW
                    Rectangle {
                        width: card.cellW
                        height: width * 9 / 16
                        radius: 8
                        color: Theme.checkerBase
                        border.width: modelData.selected ? 2 : 2
                        border.color: modelData.selected ? Mxu.accent : "#333333"
                        clip: true

                        Checkerboard { anchors.fill: parent; anchors.margins: 2 }

                        Rectangle {
                            anchors.left: parent.left
                            anchors.top: parent.top
                            anchors.margins: 5
                            radius: 5
                            color: modelData.tagColor
                            implicitWidth: tagText.implicitWidth + 12
                            implicitHeight: 16
                            Text {
                                id: tagText
                                anchors.centerIn: parent
                                text: modelData.tag
                                color: "white"
                                font.pixelSize: 9
                                font.weight: Font.DemiBold
                            }
                        }
                        Text {
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.top: parent.top
                            anchors.topMargin: 22
                            anchors.leftMargin: 8
                            anchors.rightMargin: 8
                            text: modelData.text || ""
                            color: Theme.text
                            font.pixelSize: 10
                            font.weight: Font.Bold
                            lineHeight: 1.4
                            horizontalAlignment: Text.AlignHCenter
                            wrapMode: Text.WordWrap
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: card.slideClicked(slideIndex)
                        }
                    }
                    Text {
                        width: parent.width
                        text: slideIndex + 1
                        color: Theme.textDim
                        font.pixelSize: 11
                    }
                }
            }
        }
    }
}
