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
    title: "MxU Slides — " + Mxu.serviceModel.serviceName

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

        MouseArea {
            anchors.fill: parent
            property real dragX: 0
            property real dragY: 0
            onPressed: { dragX = mouseX; dragY = mouseY }
            onPositionChanged: if (mouse.buttons & Qt.LeftButton) {
                window.x += mouseX - dragX
                window.y += mouseY - dragY
            }
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

    // edge resizing
    MouseArea {
        anchors.right: parent.right; anchors.top: parent.top; anchors.bottom: parent.bottom
        width: 6; cursorShape: Qt.SizeHorCursor
        property real lastX: 0
        onPressed: lastX = mouseX
        onPositionChanged: if (mouse.buttons & Qt.LeftButton)
            window.width = Math.max(window.minimumWidth, window.width + mouseX - lastX)
    }
    MouseArea {
        anchors.left: parent.left; anchors.top: parent.top; anchors.bottom: parent.bottom
        width: 6; cursorShape: Qt.SizeHorCursor
        property real lastX: 0
        onPressed: lastX = mouseX
        onPositionChanged: if (mouse.buttons & Qt.LeftButton) {
            const w = Math.max(window.minimumWidth, window.width + lastX - mouseX)
            window.x += window.width - w
            window.width = w
        }
    }
    MouseArea {
        anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right
        height: 6; cursorShape: Qt.SizeVerCursor
        property real lastY: 0
        onPressed: lastY = mouseY
        onPositionChanged: if (mouse.buttons & Qt.LeftButton)
            window.height = Math.max(window.minimumHeight, window.height + mouseY - lastY)
    }
    MouseArea {
        anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
        height: 6; cursorShape: Qt.SizeVerCursor
        property real lastY: 0
        onPressed: lastY = mouseY
        onPositionChanged: if (mouse.buttons & Qt.LeftButton) {
            const h = Math.max(window.minimumHeight, window.height + lastY - mouseY)
            window.y += window.height - h
            window.height = h
        }
    }

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
        anchors.centerIn: parent
        onCloseRequested: hide()
    }

    TimelinePanel {
        id: timelinePanel
        anchors.centerIn: parent
        onCloseRequested: hide()
    }

    QuickSearch {
        id: quickSearch
        anchors.centerIn: parent
        z: 10
        onCloseRequested: hide()
    }

    Shortcut { sequence: "Ctrl+K"; onActivated: quickSearch.open() }
    Shortcut { sequence: "Ctrl+T"; onActivated: timelinePanel.open() }
    Shortcut { sequence: "F8"; onActivated: notesPanel.open() }
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
