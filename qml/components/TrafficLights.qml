import QtQuick
import QtQuick.Window
import "qrc:/qml/theme"

// macOS-style window dots inside the sidebar header. On Windows they also
// perform the real window actions so the decoration stays functional.
Row {
    id: lights
    spacing: 8
    property var windowRef: null

    Repeater {
        model: [
            { color: Theme.trafficRed,   action: "close" },
            { color: Theme.trafficYellow, action: "minimize" },
            { color: Theme.trafficGreen,  action: "maximize" },
        ]
        delegate: Rectangle {
            width: 12; height: 12
            radius: 6
            color: modelData.color
            border.color: Qt.rgba(0, 0, 0, 0.35)
            border.width: 0.5
            Rectangle {
                anchors.fill: parent
                radius: 6
                color: Qt.rgba(0, 0, 0, 0.18)
                opacity: area.containsMouse ? 1 : 0
            }
            MouseArea {
                id: area
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    const w = lights.windowRef
                    if (!w) return
                    if (modelData.action === "close") w.close()
                    else if (modelData.action === "minimize") w.showMinimized()
                    else if (w.visibility === Window.Maximized) w.showNormal()
                    else w.showMaximized()
                }
            }
        }
    }
}
