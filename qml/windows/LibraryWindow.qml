import QtQuick
import QtQuick.Window
import "qrc:/qml/theme"
import "qrc:/qml/components"
import "qrc:/qml/screens"

// Operator library window (Mac LibraryWindow): hosts the library surface as a
// real OS window instead of the in-shell library screen.

Window {
    id: libraryWindow
    width: 1100
    height: 720
    visible: false
    flags: Qt.Window | Qt.FramelessWindowHint
            | (Mxu.outputs.alwaysOnTop ? Qt.WindowStaysOnTopHint : 0)

    function open() { visible = true }
    function hide() { visible = false }

    LibraryScreen {
        anchors.fill: parent
    }
}
