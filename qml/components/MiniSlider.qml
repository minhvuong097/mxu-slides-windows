import QtQuick
import "qrc:/qml/theme"

// 56x4 track with a 20x12 thumb, as used in the Present toolbar.
Rectangle {
    id: slider
    property real value: 0.25
    signal sliderMoved(real value)

    width: 56; height: 4
    radius: 3
    color: "#3a3a3e"

    Rectangle {
        id: thumb
        x: Math.max(0, Math.min(slider.width - 20, slider.value * (slider.width - 20)))
        y: -4
        width: 20; height: 12
        radius: 6
        color: Theme.text
    }

    MouseArea {
        id: area
        anchors.fill: parent
        anchors.margins: -6
        hoverEnabled: true
        drag.target: thumb
        drag.axis: Drag.XAxis
        drag.minimumX: 0
        drag.maximumX: slider.width - 20
        onPositionChanged: {
            if (drag.active) {
                slider.value = Math.max(0, Math.min(1, thumb.x / (slider.width - 20)))
                slider.sliderMoved(slider.value)
            }
        }
    }
}
