import QtQuick
import QtQuick.Controls
import QtQuick.Window
import "qrc:/qml/theme"
import "qrc:/qml/components"

// Windows counterpart of the macOS Scheduler board: timed actions, enable /
// snooze (reset), manual fire, trigger list and a persisted fire history.
Window {
    id: scheduler
    width: 940
    height: 560
    minimumWidth: 760
    minimumHeight: 440
    title: "Scheduler — MxU Slides"
    color: Theme.bg
    flags: Qt.Window
    visible: false

    readonly property var actions: ["next", "previous", "clear", "present", "stop", "stage"]
    property string clockText: Qt.formatTime(new Date(), "hh:mm:ss")

    Timer {
        interval: 1000
        repeat: true
        running: scheduler.visible
        onTriggered: scheduler.clockText = Qt.formatTime(new Date(), "hh:mm:ss")
    }

    Row {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 12

        Rectangle {
            width: 520
            height: parent.height
            radius: 10
            color: Theme.card
            Column {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 8

                Text { text: "SCHEDULE BOARD"; color: Theme.text; font.pixelSize: 13; font.weight: Font.DemiBold }

                Row {
                    width: parent.width; spacing: 6
                    TextField {
                        id: draftName
                        width: 180; height: 28
                        placeholderText: "Schedule name"
                        color: Theme.text; font.pixelSize: 11
                        background: Rectangle { radius: 7; color: Theme.inset }
                    }
                    TextField {
                        id: draftTime
                        width: 62; height: 28
                        text: Qt.formatTime(new Date(), "hh:mm")
                        color: Theme.text; font.pixelSize: 11
                        background: Rectangle { radius: 7; color: Theme.inset }
                    }
                    ComboBox {
                        id: draftAction
                        width: 110; height: 28
                        model: scheduler.actions
                        background: Rectangle { radius: 7; color: Theme.inset }
                        contentItem: Text { text: draftAction.currentText; color: Theme.text; font.pixelSize: 11; verticalAlignment: Text.AlignVCenter }
                    }
                    Rectangle {
                        width: 90; height: 28; radius: 7; color: Theme.accent
                        Text { anchors.centerIn: parent; text: "+ Add"; color: "white"; font.pixelSize: 10; font.weight: Font.Bold }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if (Mxu.automation.addSchedule(draftName.text, draftTime.text, draftAction.currentText))
                                    draftName.text = ""
                            }
                        }
                    }
                }

                Flickable {
                    width: parent.width
                    height: parent.height - 90
                    contentHeight: scheduleList.implicitHeight
                    clip: true
                    Column {
                        id: scheduleList
                        width: parent.width
                        spacing: 6
                        Repeater {
                            model: Mxu.automation.schedules
                            delegate: Rectangle {
                                width: parent.width
                                height: 52
                                radius: 8
                                color: modelData.fired ? "#26262a" : "#2c2c30"
                                Row {
                                    anchors.fill: parent
                                    anchors.leftMargin: 10
                                    anchors.rightMargin: 10
                                    anchors.verticalCenter: parent.verticalCenter
                                    spacing: 8
                                    Text {
                                        width: 44
                                        anchors.verticalCenter: parent.verticalCenter
                                        text: modelData.time
                                        color: modelData.fired ? Theme.textFaint : Theme.green
                                        font.pixelSize: 13
                                        font.weight: Font.Bold
                                    }
                                    Column {
                                        width: 160
                                        anchors.verticalCenter: parent.verticalCenter
                                        Text { text: modelData.name; color: Theme.text; font.pixelSize: 11; font.weight: Font.Bold; elide: Text.ElideRight }
                                        Text { text: modelData.action + (modelData.fired ? " · fired" : ""); color: Theme.textDim; font.pixelSize: 10 }
                                    }
                                    Rectangle {
                                        width: 36; height: 24; radius: 6
                                        color: modelData.enabled === false ? Theme.surface : Theme.green
                                        Text { anchors.centerIn: parent; text: modelData.enabled === false ? "Off" : "On"; color: "white"; font.pixelSize: 9; font.weight: Font.Bold }
                                        MouseArea { anchors.fill: parent; onClicked: Mxu.automation.setScheduleEnabled(modelData.id, modelData.enabled === false) }
                                    }
                                    Rectangle {
                                        width: 44; height: 24; radius: 6; color: Theme.accent
                                        Text { anchors.centerIn: parent; text: "Fire"; color: "white"; font.pixelSize: 9; font.weight: Font.Bold }
                                        MouseArea { anchors.fill: parent; onClicked: Mxu.automation.fireSchedule(modelData.id) }
                                    }
                                    Rectangle {
                                        width: 44; height: 24; radius: 6; color: Theme.surface
                                        Text { anchors.centerIn: parent; text: "Reset"; color: Theme.text; font.pixelSize: 9 }
                                        MouseArea { anchors.fill: parent; onClicked: Mxu.automation.resetSchedule(modelData.id) }
                                    }
                                    Rectangle {
                                        width: 28; height: 24; radius: 6; color: Theme.surface
                                        Text { anchors.centerIn: parent; text: "✕"; color: Theme.textDim; font.pixelSize: 10 }
                                        MouseArea { anchors.fill: parent; onClicked: Mxu.automation.removeSchedule(modelData.id) }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        Column {
            width: parent.width - 532
            height: parent.height
            spacing: 8

            Rectangle {
                width: parent.width
                height: 92
                radius: 10
                color: Theme.card
                Column {
                    anchors.fill: parent
                    anchors.margins: 12
                    Text { text: "CLOCK"; color: Theme.textDim; font.pixelSize: 10; font.weight: Font.Bold }
                    Text { text: scheduler.clockText; color: Theme.text; font.pixelSize: 26; font.weight: Font.Bold }
                    Text { text: "Timecode " + Mxu.automation.timecode + " · " + Mxu.automation.timecodeSource; color: Theme.textDim; font.pixelSize: 10; elide: Text.ElideRight }
                }
            }

            Rectangle {
                width: parent.width
                height: 216
                radius: 10
                color: Theme.card
                Column {
                    anchors.fill: parent
                    anchors.margins: 12
                    spacing: 6
                    Row {
                        width: parent.width
                        Text { text: "FIRE HISTORY"; color: Theme.textDim; font.pixelSize: 10; font.weight: Font.Bold }
                        Rectangle {
                            anchors.right: parent.right
                            width: 52; height: 20; radius: 6; color: Theme.surface
                            Text { anchors.centerIn: parent; text: "Clear"; color: Theme.text; font.pixelSize: 9 }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.automation.clearHistory() }
                        }
                    }
                    Flickable {
                        width: parent.width
                        height: 160
                        contentHeight: historyList.implicitHeight
                        clip: true
                        Column {
                            id: historyList
                            width: parent.width
                            spacing: 4
                            Repeater {
                                model: Mxu.automation.history
                                delegate: Rectangle {
                                    width: parent.width; height: 26; radius: 6; color: "#2c2c30"
                                    Row {
                                        anchors.fill: parent; anchors.leftMargin: 8; anchors.rightMargin: 8; spacing: 8
                                        Text { width: 58; anchors.verticalCenter: parent.verticalCenter; text: modelData.at; color: Theme.textDim; font.pixelSize: 9 }
                                        Text { width: parent.width - 160; anchors.verticalCenter: parent.verticalCenter; text: modelData.name; color: Theme.text; font.pixelSize: 10; elide: Text.ElideRight }
                                        Text { width: 90; anchors.verticalCenter: parent.verticalCenter; text: modelData.source; color: Theme.accent; font.pixelSize: 9 }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Rectangle {
                width: parent.width
                height: parent.height - 324
                radius: 10
                color: Theme.card
                Column {
                    anchors.fill: parent
                    anchors.margins: 12
                    spacing: 6
                    Text { text: "TRIGGERS"; color: Theme.textDim; font.pixelSize: 10; font.weight: Font.Bold }
                    Flickable {
                        width: parent.width
                        height: parent.height - 20
                        contentHeight: triggerList.implicitHeight
                        clip: true
                        Column {
                            id: triggerList
                            width: parent.width
                            spacing: 4
                            Repeater {
                                model: Mxu.automation.triggers
                                delegate: Rectangle {
                                    width: parent.width; height: 26; radius: 6; color: "#2c2c30"
                                    Row {
                                        anchors.fill: parent; anchors.leftMargin: 8; anchors.rightMargin: 8; spacing: 8
                                        Text { width: 70; anchors.verticalCenter: parent.verticalCenter; text: modelData.kind; color: Theme.textDim; font.pixelSize: 9 }
                                        Text { width: parent.width - 140; anchors.verticalCenter: parent.verticalCenter; text: modelData.action + " ← " + modelData.value; color: Theme.text; font.pixelSize: 10; elide: Text.ElideRight }
                                        Rectangle {
                                            width: 44; height: 20; radius: 6; color: Theme.accent
                                            Text { anchors.centerIn: parent; text: "Fire"; color: "white"; font.pixelSize: 9 }
                                            MouseArea { anchors.fill: parent; onClicked: Mxu.automation.fire(modelData.action) }
                                        }
                                        Rectangle {
                                            width: 20; height: 20; radius: 6; color: Theme.surface
                                            Text { anchors.centerIn: parent; text: "✕"; color: Theme.textDim; font.pixelSize: 9 }
                                            MouseArea { anchors.fill: parent; onClicked: Mxu.automation.removeTrigger(modelData.id) }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
