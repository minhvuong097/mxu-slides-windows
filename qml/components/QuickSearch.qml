import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "qrc:/qml/theme"

// Ctrl+K quick search over slides, cues, media and notes (FTS5-backed).
Rectangle {
    id: search
    width: 640
    height: 420
    radius: 12
    color: Theme.card
    border.color: "#3a3a3e"
    border.width: 1
    visible: false
    z: 20

    signal closeRequested()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 14
        spacing: 8

        RowLayout {
            Layout.preferredHeight: 34
            AppIcon { name: "search"; size: 16; color: Theme.textDim }
            TextField {
                id: input
                Layout.fillWidth: true
                placeholderText: "Search slides, media, notes…"
                placeholderTextColor: Theme.textDim
                color: Theme.text
                font.pixelSize: 13
                background: Rectangle { color: "transparent" }
                onTextChanged: results.model = Mxu.search(text)
                Keys.onEscapePressed: search.closeRequested()
                Component.onCompleted: forceActiveFocus()
            }
            Text { text: "Esc"; color: Theme.textFaint; font.pixelSize: 10 }
        }

        Rectangle { Layout.preferredHeight: 1; Layout.fillWidth: true; color: "#333" }

        ListView {
            id: results
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: []
            delegate: Rectangle {
                width: results.width
                height: 54
                color: area.containsMouse ? "#2c2c30" : "transparent"
                Column {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: 8
                    spacing: 3
                    Text {
                        text: modelData.kind + " · " + modelData.ref
                        color: Theme.text
                        font.pixelSize: 12
                        font.weight: Font.DemiBold
                        elide: Text.ElideRight
                    }
                    Text {
                        width: parent.width
                        text: modelData.text
                        color: Theme.textDim
                        font.pixelSize: 11
                        maximumLineCount: 1
                        elide: Text.ElideRight
                    }
                }
                MouseArea {
                    id: area
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: search.closeRequested()
                }
            }
        }
    }

    function open() {
        visible = true
        input.text = ""
        results.model = []
        input.forceActiveFocus()
    }
    function hide() { visible = false }
}
