import QtQuick
import QtQuick.Shapes
import "qrc:/qml/theme"

// Renders the C++ RenderScene: ordered layers with per-layer/item opacity,
// text styling, chord overlays and clear state.
Item {
    id: view
    property real scaleFactor: width / 1920
    property bool cleared: false

    Repeater {
        model: Mxu.renderLayers
        delegate: Item {
            property var layerData: modelData
            visible: layerData.visible && !view.cleared
            opacity: layerData.opacity
            z: layerData.z + 1

            Repeater {
                model: layerData.items
                delegate: Item {
                    property var item: modelData
                    x: item.x * view.scaleFactor
                    y: item.y * view.scaleFactor
                    width: item.width * view.scaleFactor
                    height: item.height * view.scaleFactor
                    opacity: item.opacity
                    z: item.z

                    Text {
                        visible: item.kind !== "shape"
                        anchors.centerIn: parent
                        width: parent.width
                        text: item.text
                        color: item.colorHex
                        font.pixelSize: item.fontSize * view.scaleFactor
                        font.family: Theme.fontFamily
                        font.weight: Font.Bold
                        lineHeight: 1.35
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.WordWrap
                    }

                    Shape {
                        visible: item.kind === "shape"
                        anchors.fill: parent
                        antialiasing: true
                        ShapePath {
                            strokeWidth: item.strokeWidth * view.scaleFactor
                            strokeColor: item.strokeColor || "transparent"
                            fillColor: item.fillColor || "transparent"
                            capStyle: ShapePath.RoundCap
                            joinStyle: ShapePath.RoundJoin
                            PathSvg {
                                path: item.pathData !== ""
                                      ? item.pathData
                                      : (item.shapeKind === "ellipse"
                                         ? "M " + (item.width * view.scaleFactor / 2) + " 0 a "
                                           + (item.width * view.scaleFactor / 2) + " "
                                           + (item.height * view.scaleFactor / 2)
                                           + " 0 1 0 0.01 0 z"
                                         : "M0 0 H" + (item.width * view.scaleFactor)
                                           + " V" + (item.height * view.scaleFactor)
                                           + " H0 Z")
                            }
                        }
                    }
                    Text {
                        anchors.left: parent.left
                        anchors.top: parent.top
                        visible: item.chord && Mxu.chordsVisible
                        text: item.chord
                        color: Theme.yellow
                        font.pixelSize: Math.max(14, item.fontSize * 0.6 * view.scaleFactor)
                        font.weight: Font.Bold
                    }
                }
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: view.cleared ? 1 : 0
        visible: opacity > 0
        Behavior on opacity { NumberAnimation { duration: 200 } }
    }
}
