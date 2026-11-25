import QtQuick
import QtQuick.Layouts
import "qrc:/qml/theme"
import "qrc:/qml/components"

Item {
    id: section
    property string text: ""
    property color labelColor: Theme.green
    property bool bothRules: false
    property bool showChevron: true
    height: 18

    RowLayout {
        anchors.fill: parent
        spacing: 6

        Rectangle {
            Layout.preferredWidth: section.bothRules ? 12 : 10
            Layout.preferredHeight: 1
            Layout.alignment: Qt.AlignVCenter
            visible: section.bothRules
            color: section.labelColor
            opacity: 0.45
        }
        Rectangle {
            Layout.preferredWidth: 10
            Layout.preferredHeight: 1
            Layout.alignment: Qt.AlignVCenter
            visible: !section.bothRules
            color: section.labelColor
            opacity: 0.45
        }
        AppIcon {
            Layout.alignment: Qt.AlignVCenter
            visible: section.showChevron
            name: "chevronDown"
            size: 10
            color: section.labelColor
        }
        Text {
            Layout.alignment: Qt.AlignVCenter
            text: section.text
            color: section.labelColor
            font.pixelSize: 9
            font.weight: Font.Bold
            font.letterSpacing: 0.72
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 1
            Layout.alignment: Qt.AlignVCenter
            color: section.labelColor
            opacity: 0.45
        }
    }
}
