import QtQuick
import QtQuick.Controls
import QtQuick.Window
import "qrc:/qml/theme"
import "qrc:/qml/screens"
import "qrc:/qml/components"
import "qrc:/qml/windows"

// Frameless macOS-style shell. The five screens mirror the Claude mockup.
ApplicationWindow {
    id: window
    width: 1280
    height: 840
    minimumWidth: 1100
    minimumHeight: 700
    visible: true
    flags: Qt.Window | Qt.FramelessWindowHint
    color: "transparent"
    title: "ProSlides — " + Mxu.serviceModel.serviceName

    property Component presentComponent: PresentScreen {}
    property Component editComponent: EditScreen {}
    property Component stageComponent: StageScreen {}
    property Component libraryComponent: LibraryScreen {}
    property Component settingsComponent: SettingsScreen {}

    Rectangle {
        anchors.fill: parent
        color: Theme.bg
        radius: 12
        border.color: "#3a3a3e"
        border.width: 1
        clip: true

        // Drag the frameless window by any empty area (native move: DPI-safe,
        // works with Aero Snap, no cumulative-delta jitter).
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton
            onPressed: window.startSystemMove()
            onDoubleClicked: window.visibility = window.visibility === Window.Maximized
                                 ? Window.Windowed : Window.Maximized
        }

        Loader {
            anchors.fill: parent
            z: 1
            sourceComponent: {
                if (Mxu.screen === "edit") return window.editComponent
                if (Mxu.screen === "stage") return window.stageComponent
                if (Mxu.screen === "library") return window.libraryComponent
                if (Mxu.screen === "settings") return window.settingsComponent
                return window.presentComponent
            }
        }

        Rectangle {
            id: toast
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 24
            anchors.horizontalCenter: parent.horizontalCenter
            radius: 9
            color: "#2b2b2e"
            border.color: "#3c3c40"
            border.width: 1
            implicitWidth: toastText.implicitWidth + 30
            implicitHeight: 32
            opacity: 0
            visible: opacity > 0
            Behavior on opacity { NumberAnimation { duration: 180 } }
            Text {
                id: toastText
                anchors.centerIn: parent
                color: Theme.text
                font.pixelSize: 11
            }
            Timer {
                id: toastTimer
                interval: 2600
                onTriggered: toast.opacity = 0
            }
        }
    }

    // Edge / corner resizing through the native window manager.
    component ResizeGrip: MouseArea {
        required property int edges
        acceptedButtons: Qt.LeftButton
        hoverEnabled: true
        onPressed: window.startSystemResize(edges)
    }
    ResizeGrip { edges: Qt.RightEdge;  cursorShape: Qt.SizeHorCursor
        anchors { right: parent.right; top: parent.top; bottom: parent.bottom; topMargin: 8; bottomMargin: 8 } width: 6 }
    ResizeGrip { edges: Qt.LeftEdge;   cursorShape: Qt.SizeHorCursor
        anchors { left: parent.left; top: parent.top; bottom: parent.bottom; topMargin: 8; bottomMargin: 8 } width: 6 }
    ResizeGrip { edges: Qt.BottomEdge; cursorShape: Qt.SizeVerCursor
        anchors { bottom: parent.bottom; left: parent.left; right: parent.right; leftMargin: 8; rightMargin: 8 } height: 6 }
    ResizeGrip { edges: Qt.TopEdge;    cursorShape: Qt.SizeVerCursor
        anchors { top: parent.top; left: parent.left; right: parent.right; leftMargin: 8; rightMargin: 8 } height: 6 }
    ResizeGrip { edges: Qt.RightEdge | Qt.BottomEdge; cursorShape: Qt.SizeFDiagCursor
        anchors { right: parent.right; bottom: parent.bottom } width: 8; height: 8 }
    ResizeGrip { edges: Qt.LeftEdge | Qt.TopEdge;     cursorShape: Qt.SizeFDiagCursor
        anchors { left: parent.left; top: parent.top } width: 8; height: 8 }
    ResizeGrip { edges: Qt.RightEdge | Qt.TopEdge;    cursorShape: Qt.SizeBDiagCursor
        anchors { right: parent.right; top: parent.top } width: 8; height: 8 }
    ResizeGrip { edges: Qt.LeftEdge | Qt.BottomEdge;  cursorShape: Qt.SizeBDiagCursor
        anchors { left: parent.left; bottom: parent.bottom } width: 8; height: 8 }

    Connections {
        target: Mxu
        function onNotification(message) {
            toastText.text = message
            toast.opacity = 1
            toastTimer.restart()
        }
    }

    PresentationWindow { id: presentationOutput }
    StageOutputWindow { id: stageOutput }
    ConfidenceWindow { id: confidenceMonitor }

    NotesPanel {
        id: notesPanel
        x: 380
        y: 160
        width: 420
        height: 460
        visible: false
        onCloseRequested: hide()
    }

    TimelinePanel {
        id: timelinePanel
        x: 140
        y: 240
        width: 900
        height: 300
        visible: false
        onCloseRequested: hide()
    }

    QuickSearch {
        id: quickSearch
        x: 270
        y: 180
        width: 640
        height: 420
        visible: false
        onCloseRequested: hide()
    }

    Shortcut { sequence: "Ctrl+K"; context: Qt.ShortcutContext.Application; onActivated: quickSearch.open() }
    Shortcut { sequence: "Ctrl+T"; context: Qt.ShortcutContext.Application; onActivated: timelinePanel.open() }
    Shortcut { sequence: "F8"; context: Qt.ShortcutContext.Application; onActivated: notesPanel.open() }
    Shortcut { sequence: "F5"; onActivated: Mxu.togglePresenting() }
    Shortcut { sequence: "F6"; onActivated: Mxu.toggleStageOutput() }
    Shortcut { sequence: "F7"; onActivated: Mxu.toggleConfidence() }
    Shortcut { sequence: "Right"; onActivated: Mxu.next() }
    Shortcut { sequence: "Space"; onActivated: Mxu.next() }
    Shortcut { sequence: "Left"; onActivated: Mxu.previous() }
    Shortcut { sequence: "Ctrl+S"; onActivated: Mxu.saveDocument() }
    Shortcut { sequence: "Ctrl+1"; onActivated: Mxu.setScreen("present") }
    Shortcut { sequence: "Ctrl+2"; onActivated: Mxu.setScreen("edit") }
    Shortcut { sequence: "Ctrl+3"; onActivated: Mxu.setScreen("stage") }
    Shortcut { sequence: "Ctrl+4"; onActivated: Mxu.setScreen("library") }
    Shortcut { sequence: "Ctrl+5"; onActivated: Mxu.setScreen("settings") }
}
