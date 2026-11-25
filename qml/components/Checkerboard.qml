import QtQuick
import "qrc:/qml/theme"

// Dark checkerboard used by slide thumbnails and the editor canvas.
// A tiled 20px PNG is far cheaper than repainting the pattern on a Canvas.
Image {
    source: "qrc:/resources/icons/checker.png"
    fillMode: Image.Tile
    asynchronous: true
    cache: true
    smooth: false
}
