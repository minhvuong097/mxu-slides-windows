import QtQuick
import QtQuick.Shapes
import "qrc:/qml/theme"

// Vector 16x16 icon. `size` scales the glyph without changing its geometry.
Item {
    id: root
    property string name: ""
    property color color: Theme.textDim
    property real stroke: 1.4
    property real size: 16

    width: size
    height: size

    Shape {
        width: 16
        height: 16
        anchors.centerIn: parent
        scale: root.size / 16
        transformOrigin: Item.Center
        antialiasing: true

        ShapePath {
            strokeColor: Icons.filled(root.name) ? "transparent" : root.color
            strokeWidth: root.stroke
            fillColor: Icons.filled(root.name) ? root.color : "transparent"
            capStyle: ShapePath.RoundCap
            joinStyle: ShapePath.RoundJoin
            PathSvg { path: Icons.path(root.name) }
        }
    }
}
