import QtQuick
import QtQuick.Shapes
import "qrc:/qml/theme"

// Renders the C++ RenderScene: ordered layers with per-layer/item opacity,
// text styling, chord overlays and clear state.
Item {
    id: view
    property real scaleX: {
        const sx = width / 1920
        const sy = height / 1080
        if (Mxu.outputScaleMode === "stretch") return sx
        if (Mxu.outputScaleMode === "fill") return Math.max(sx, sy)
        return Math.min(sx, sy)
    }
    property real scaleY: {
        const sx = width / 1920
        const sy = height / 1080
        if (Mxu.outputScaleMode === "stretch") return sy
        if (Mxu.outputScaleMode === "fill") return Math.max(sx, sy)
        return Math.min(sx, sy)
    }
    property real offsetX: (width - 1920 * scaleX) / 2
    property real offsetY: (height - 1080 * scaleY) / 2
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
                    x: view.offsetX + item.x * view.scaleX
                    y: view.offsetY + item.y * view.scaleY
                    width: item.width * view.scaleX
                    height: item.height * view.scaleY
                    opacity: item.opacity
                    z: item.z

                    Text {
                        visible: item.kind !== "shape"
                        anchors.centerIn: parent
                        width: parent.width
                        text: item.richText || item.text
                        textFormat: Text.RichText
                        color: item.colorHex
                        font.pixelSize: item.fontSize * view.scaleY
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
                            strokeWidth: item.strokeWidth * view.scaleX
                            strokeColor: item.strokeColor || "transparent"
                            fillColor: item.fillColor || "transparent"
                            capStyle: ShapePath.RoundCap
                            joinStyle: ShapePath.RoundJoin
                            PathSvg {
                                path: item.pathData !== ""
                                      ? item.pathData
                                      : (item.shapeKind === "ellipse"
                                         ? "M " + (item.width * view.scaleX / 2) + " 0 a "
                                           + (item.width * view.scaleX / 2) + " "
                                           + (item.height * view.scaleX / 2)
                                           + " 0 1 0 0.01 0 z"
                                         : "M0 0 H" + (item.width * view.scaleX)
                                           + " V" + (item.height * view.scaleX)
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
                        font.pixelSize: Math.max(14, item.fontSize * 0.6 * view.scaleX)
                        font.weight: Font.Bold
                    }
                }
            }
        }
    }

    Canvas {
        anchors.fill: parent
        visible: Mxu.outputMaskMode === "out" || Mxu.outputMaskMode === "in"
        onWidthChanged: requestPaint()
        onHeightChanged: requestPaint()
        onPaint: {
            const ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)
            ctx.globalCompositeOperation = "source-over"
            ctx.fillStyle = "black"
            const inset = Math.min(width, height) * 0.08
            const x = inset, y = inset
            const w = width - inset * 2, h = height - inset * 2
            if (Mxu.outputMaskMode === "out") {
                ctx.fillRect(0, 0, width, height)
                ctx.globalCompositeOperation = "destination-out"
                if (Mxu.outputMaskShape === "ellipse") {
                    ctx.beginPath()
                    ctx.ellipse(x + w / 2, y + h / 2, w / 2, h / 2, 0, 0, Math.PI * 2)
                    ctx.fill()
                } else {
                    ctx.fillRect(x, y, w, h)
                }
            } else {
                ctx.fillRect(x, y, w, h)
                ctx.globalCompositeOperation = "destination-out"
                if (Mxu.outputMaskShape === "ellipse") {
                    ctx.beginPath()
                    ctx.ellipse(x + w / 2, y + h / 2, w / 2 - 6, h / 2 - 6, 0, 0, Math.PI * 2)
                    ctx.fill()
                } else {
                    ctx.fillRect(x + 6, y + 6, w - 12, h - 12)
                }
            }
            ctx.globalCompositeOperation = "source-over"
        }
        z: 10
    }

    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: view.cleared ? 1 : 0
        visible: opacity > 0
        Behavior on opacity { NumberAnimation { duration: 200 } }
    }
}
