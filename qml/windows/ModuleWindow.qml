import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Window
import "qrc:/qml/theme"
import "qrc:/qml/components"

// Operator module window (Mac ModuleWindow). Hosts module-scoped control
// surfaces by module name (Mac ModuleWindowView switch):
// timers / audio / alerts / combos / confidence / outputs / timecode.

Window {
    id: moduleWindow
    width: 360
    height: 460
    visible: false
    flags: Qt.Window | Qt.FramelessWindowHint
            | (Mxu.outputs.alwaysOnTop ? Qt.WindowStaysOnTopHint : 0)

    property string module: "timers"

    function modeLabel(mode) {
        if (mode === "countUp")
            return "Count-up"
        if (mode === "countdownToTime")
            return "Countdown to time"
        return "Countdown"
    }

    Rectangle {
        anchors.fill: parent
        color: Theme.card

        Column {
            anchors.fill: parent
            anchors.margins: 16
            spacing: 10

            Text {
                id: header
                text: "Module — " + module
                color: Theme.text
                font.pixelSize: 18
                font.weight: Font.DemiBold
            }

            Loader {
                id: moduleLoader
                anchors.top: header.bottom
                anchors.bottom: parent.bottom
                width: parent.width
                sourceComponent: module === "timers" ? timersModule
                                 : module === "track" ? trackingModule
                                 : module === "audio" ? audioModule
                                 : module === "mixer" ? mixerModule
                                 : module === "alerts" ? alertsModule
                                 : module === "combos" ? combosModule
                                 : module === "confidence" ? confidenceModule
                                 : module === "outputs" ? outputsModule
                                 : module === "timecode" ? timecodeModule
                                 : null
            }
        }
    }

    Component {
        id: timersModule
        Rectangle {
            width: moduleLoader.width
            height: moduleLoader.height
            color: "transparent"
            Column {
                anchors.fill: parent
                anchors.margins: 0
                spacing: 8
                Repeater {
                    model: Mxu.timerBoard.timers
                    delegate: Rectangle {
                        id: row
                        width: parent.width
                        height: 56
                        radius: 10
                        color: "#2c2c30"
                        Row {
                            anchors.fill: parent
                            anchors.leftMargin: 12
                            anchors.rightMargin: 12
                            spacing: 8
                            Column {
                                width: parent.width - 132
                                Text {
                                    text: modelData.name
                                    color: Theme.text
                                    font.pixelSize: 13
                                    font.weight: Font.Bold
                                    elide: Text.ElideRight
                                }
                                Text {
                                    text: modeLabel(modelData.mode) + " · " + (modelData.remaining / 60).toFixed(0) + " min"
                                    color: Theme.textDim
                                    font.pixelSize: 11
                                }
                            }

                            Rectangle {
                                width: 40
                                height: 28
                                radius: 8
                                color: Theme.accent
                                Text { anchors.centerIn: parent; text: modelData.running ? "Pause" : "Start"; color: "white"; font.pixelSize: 11; font.weight: Font.Bold }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: modelData.running ? Mxu.timerBoard.pause(modelData.id) : Mxu.timerBoard.start(modelData.id)
                                }
                            }
                            Rectangle {
                                width: 40
                                height: 28
                                radius: 8
                                color: Theme.surface
                                Text { anchors.centerIn: parent; text: "Reset"; color: Theme.text; font.pixelSize: 11; font.weight: Font.Bold }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: Mxu.timerBoard.reset(modelData.id)
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Component {
        id: audioModule
        Rectangle {
            width: moduleLoader.width
            height: moduleLoader.height
            color: "transparent"
            Column {
                anchors.fill: parent
                anchors.margins: 0
                spacing: 8
                Repeater {
                    model: Mxu.audioChannels
                    delegate: Rectangle {
                        id: row
                        width: parent.width
                        height: 56
                        radius: 10
                        color: "#2c2c30"
                        Row {
                            anchors.fill: parent
                            anchors.leftMargin: 12
                            anchors.rightMargin: 12
                            spacing: 8
                            Column {
                                width: parent.width - 140
                                Text {
                                    text: modelData.name
                                    color: Theme.text
                                    font.pixelSize: 13
                                    font.weight: Font.Bold
                                    elide: Text.ElideRight
                                }
                                Text {
                                    text: (modelData.playing ? "Playing" : "Ready") + (modelData.muted ? " · Muted" : "")
                                    color: Theme.textDim
                                    font.pixelSize: 11
                                }
                            }
                            Rectangle {
                                width: 40
                                height: 28
                                radius: 8
                                color: Theme.accent
                                Text { anchors.centerIn: parent; text: modelData.playing ? "Stop" : "Play"; color: "white"; font.pixelSize: 11; font.weight: Font.Bold }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: modelData.playing ? Mxu.audioService.stop(modelData.id) : Mxu.audioService.play(modelData.id)
                                }
                            }
                            Rectangle {
                                width: 28
                                height: 28
                                radius: 8
                                color: modelData.muted ? Theme.pink : Theme.surface
                                Text { anchors.centerIn: parent; text: "M"; color: "white"; font.pixelSize: 11; font.weight: Font.Bold }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: Mxu.audioService.toggleMute(modelData.id)
                                }
                            }
                            Rectangle {
                                width: 28
                                height: 28
                                radius: 8
                                color: modelData.solo ? Theme.yellow : Theme.surface
                                Text { anchors.centerIn: parent; text: "S"; color: "white"; font.pixelSize: 11; font.weight: Font.Bold }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: Mxu.audioService.toggleSolo(modelData.id)
                                }
                            }
                        }
                    }
                }
                Rectangle {
                    width: parent.width
                    height: 64
                    radius: 10
                    color: "#2c2c30"
                    Row {
                        anchors.fill: parent
                        anchors.leftMargin: 12
                        anchors.rightMargin: 12
                        spacing: 8
                        Column {
                            width: parent.width - 200
                            Text { text: "Crossfade"; color: Theme.text; font.pixelSize: 13; font.weight: Font.Bold }
                            Text { text: "From " + (Mxu.audioChannels[0] ? Mxu.audioChannels[0].name : "") + " → " + (Mxu.audioChannels[1] ? Mxu.audioChannels[1].name : ""); color: Theme.textDim; font.pixelSize: 11; elide: Text.ElideRight }
                        }
                        NumberField {
                            id: crossfadeDuration
                            label: "Sec"
                            width: 64
                            value: 5
                            onCommitted: Mxu.audioService.crossfade(Mxu.audioChannels[0].id, Mxu.audioChannels[1].id, crossfadeDuration.value)
                        }
                        Rectangle {
                            width: 90
                            height: 28
                            radius: 8
                            color: Theme.accent
                            Text { anchors.centerIn: parent; text: "Fire"; color: "white"; font.pixelSize: 11; font.weight: Font.Bold }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.audioService.crossfade(Mxu.audioChannels[0].id, Mxu.audioChannels[1].id, crossfadeDuration.value) }
                        }
                    }
                }
                Rectangle {
                    width: parent.width
                    height: 48
                    radius: 10
                    color: "#2c2c30"
                    Row {
                        anchors.fill: parent
                        anchors.leftMargin: 12
                        anchors.rightMargin: 12
                        spacing: 8
                        Rectangle {
                            width: 90
                            height: 28
                            radius: 8
                            color: Theme.accent
                            Text { anchors.centerIn: parent; text: "Play All"; color: "white"; font.pixelSize: 11; font.weight: Font.Bold }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.audioService.playAll() }
                        }
                        Rectangle {
                            width: 90
                            height: 28
                            radius: 8
                            color: Theme.surface
                            Text { anchors.centerIn: parent; text: "Stop All"; color: Theme.text; font.pixelSize: 11; font.weight: Font.Bold }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.audioService.stopAll() }
                        }
                        Rectangle {
                            width: 90
                            height: 28
                            radius: 8
                            color: Theme.surface
                            Text { anchors.centerIn: parent; text: "Add"; color: Theme.text; font.pixelSize: 11; font.weight: Font.Bold }
                            MouseArea { anchors.fill: parent; onClicked: addChannelDialog.open() }
                        }
                    }
                    FileDialog {
                        id: addChannelDialog
                        title: "Select audio file"
                        onAccepted: Mxu.audioService.addChannel("", acceptedUrl.toString())
                    }
                }
            }
        }
    }

    Component {
        id: mixerModule
        Rectangle {
            width: moduleLoader.width
            height: moduleLoader.height
            color: "transparent"
            Column {
                anchors.fill: parent
                anchors.margins: 0
                spacing: 8
                Repeater {
                    model: Mxu.audioChannels
                    delegate: Rectangle {
                        id: row
                        width: parent.width
                        height: 60
                        radius: 10
                        color: "#2c2c30"
                        Row {
                            anchors.fill: parent
                            anchors.leftMargin: 12
                            anchors.rightMargin: 12
                            spacing: 8
                            Column {
                                width: parent.width - 140
                                Text {
                                    text: modelData.name
                                    color: Theme.text
                                    font.pixelSize: 13
                                    font.weight: Font.Bold
                                    elide: Text.ElideRight
                                }
                                Text {
                                    text: "Vol " + Math.round(modelData.volume * 100) + "%"
                                    color: Theme.textDim
                                    font.pixelSize: 11
                                }
                            }
                            MiniSlider {
                                anchors.verticalCenter: parent.verticalCenter
                                value: modelData.volume
                            }
                            Rectangle {
                                width: 28
                                height: 28
                                radius: 8
                                color: modelData.muted ? Theme.pink : Theme.surface
                                Text { anchors.centerIn: parent; text: "M"; color: "white"; font.pixelSize: 11; font.weight: Font.Bold }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: Mxu.audioService.toggleMute(modelData.id)
                                }
                            }
                            Rectangle {
                                width: 28
                                height: 28
                                radius: 8
                                color: modelData.solo ? Theme.yellow : Theme.surface
                                Text { anchors.centerIn: parent; text: "S"; color: "white"; font.pixelSize: 11; font.weight: Font.Bold }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: Mxu.audioService.toggleSolo(modelData.id)
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Component {
        id: alertsModule
        Rectangle {
            width: moduleLoader.width
            height: moduleLoader.height
            color: "transparent"
            Column {
                anchors.fill: parent
                anchors.margins: 0
                spacing: 8
                Repeater {
                    model: Mxu.alertPresets.presets
                    delegate: Rectangle {
                        width: parent.width
                        height: 48
                        radius: 10
                        color: "#2c2c30"
                        Row {
                            anchors.fill: parent
                            anchors.leftMargin: 12
                            anchors.rightMargin: 12
                            spacing: 8
                            Column {
                                width: parent.width - 100
                                Text {
                                    text: modelData.name
                                    color: Theme.text
                                    font.pixelSize: 13
                                    font.weight: Font.Bold
                                    elide: Text.ElideRight
                                }
                            }
                            Rectangle {
                                width: 90
                                height: 26
                                radius: 8
                                color: Theme.pink
                                Text { anchors.centerIn: parent; text: "Fire"; color: "white"; font.pixelSize: 11; font.weight: Font.Bold }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: Mxu.alerts.fire(modelData.value, "both")
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Component {
        id: combosModule
        Rectangle {
            width: moduleLoader.width
            height: moduleLoader.height
            color: "transparent"
            Column {
                anchors.fill: parent
                anchors.margins: 0
                spacing: 8
                Repeater {
                    model: Mxu.automation.triggers
                    delegate: Rectangle {
                        width: parent.width
                        height: 48
                        radius: 10
                        color: "#2c2c30"
                        Row {
                            anchors.fill: parent
                            anchors.leftMargin: 12
                            anchors.rightMargin: 12
                            spacing: 8
                            Text {
                                width: parent.width - 100
                                text: modelData.action
                                color: Theme.text
                                font.pixelSize: 13
                                font.weight: Font.Bold
                                elide: Text.ElideRight
                            }
                            Rectangle {
                                width: 90
                                height: 26
                                radius: 8
                                color: Theme.accent
                                Text { anchors.centerIn: parent; text: "Fire"; color: "white"; font.pixelSize: 11; font.weight: Font.Bold }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: Mxu.automation.fire(modelData.action)
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Component {
        id: confidenceModule
        Rectangle {
            width: moduleLoader.width
            height: moduleLoader.height
            color: "transparent"
            Column {
                anchors.fill: parent
                anchors.margins: 0
                spacing: 8
                Repeater {
                    model: Mxu.confidenceLayout.nodes
                    delegate: Rectangle {
                        width: parent.width
                        height: 48
                        radius: 10
                        color: "#2c2c30"
                        Column {
                            width: parent.width
                            Text { text: modelData.source; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold }
                            Text { text: modelData.title; color: Theme.text; font.pixelSize: 13; font.weight: Font.Bold; elide: Text.ElideRight }
                        }
                    }
                }
            }
        }
    }

    Component {
        id: outputsModule
        Rectangle {
            width: moduleLoader.width
            height: moduleLoader.height
            color: "transparent"
            Column {
                anchors.fill: parent
                anchors.margins: 0
                spacing: 8
                Text { text: "SCREENS"; width: parent.width; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold }
                Repeater {
                    model: Mxu.outputs.screens
                    delegate: Rectangle {
                        id: row
                        width: parent.width
                        height: 48
                        radius: 10
                        color: "#2c2c30"
                        Row {
                            anchors.fill: parent
                            anchors.leftMargin: 12
                            anchors.rightMargin: 12
                            spacing: 8
                            Column {
                                width: parent.width - 100
                                Text { text: modelData.name; color: Theme.text; font.pixelSize: 13; font.weight: Font.Bold; elide: Text.ElideRight }
                                Text { text: modelData.geometry; color: Theme.textDim; font.pixelSize: 11; elide: Text.ElideRight }
                            }
                            Rectangle {
                                width: 90
                                height: 26
                                radius: 8
                                color: Theme.accent
                                Text { anchors.centerIn: parent; text: "Stage"; color: "white"; font.pixelSize: 11; font.weight: Font.Bold }
                                MouseArea { anchors.fill: parent; onClicked: Mxu.outputs.assign("stage", modelData.index) }
                            }
                        }
                    }
                }
                Rectangle { width: parent.width; height: 1; color: "#333" }
                Text { text: "PRESETS"; width: parent.width; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold }
                Repeater {
                    model: Mxu.outputPresets.presets
                    delegate: Rectangle {
                        width: parent.width
                        height: 48
                        radius: 10
                        color: "#2c2c30"
                        Row {
                            anchors.centerIn: parent
                            spacing: 8
                            Column {
                                width: parent.width - 110
                                Text { text: modelData.name; color: Theme.text; font.pixelSize: 13; font.weight: Font.Bold; elide: Text.ElideRight }
                                Text { text: modelData.value; color: Theme.textDim; font.pixelSize: 11; elide: Text.ElideRight }
                            }
                            Rectangle {
                                width: 90
                                height: 26
                                radius: 8
                                color: Theme.accent
                                Text { anchors.centerIn: parent; text: "Apply"; color: "white"; font.pixelSize: 11; font.weight: Font.Bold }
                                MouseArea { anchors.fill: parent; onClicked: Mxu.outputPresets.apply(modelData.id) }
                            }
                        }
                    }
                }
            }
        }
    }

    Component {
        id: trackingModule
        Rectangle {
            width: moduleLoader.width
            height: moduleLoader.height
            color: "transparent"
            Column {
                anchors.fill: parent
                anchors.margins: 0
                spacing: 8
                Rectangle {
                    width: parent.width
                    height: 64
                    radius: 10
                    color: "#2c2c30"
                    Column {
                        anchors.fill: parent
                        anchors.margins: 12
                        spacing: 4
                        Text { text: Mxu.currentServiceItem; color: Theme.text; font.pixelSize: 16; font.weight: Font.Bold; elide: Text.ElideRight }
                        Text { text: "Item " + Mxu.serviceModel.currentItemIndex + " of " + Mxu.serviceModel.itemCount; color: Theme.textDim; font.pixelSize: 11 }
                        Text { text: Mxu.serviceModel.serviceName; color: Theme.textFaint; font.pixelSize: 11 }
                        Text { text: Mxu.serviceModel.serviceDate; color: Theme.textFaint; font.pixelSize: 11 }
                        Text { text: Mxu.serviceTimerText; color: Theme.green; font.pixelSize: 24; font.weight: Font.Bold; horizontalAlignment: Text.AlignCenter }
                    }
                }
                Rectangle {
                    width: parent.width
                    height: 56
                    radius: 10
                    color: "#2c2c30"
                    Row {
                        anchors.fill: parent
                        anchors.leftMargin: 12
                        anchors.rightMargin: 12
                        spacing: 8
                        Column {
                            width: parent.width - 110
                            Text { text: "NEXT"; color: Theme.textDim; font.pixelSize: 10; font.weight: Font.Bold }
                            Text { text: Mxu.nextServiceItem; color: Theme.text; font.pixelSize: 13; font.weight: Font.Bold; elide: Text.ElideRight }
                        }
                        Rectangle {
                            width: 40
                            height: 28
                            radius: 8
                            color: Theme.accent
                            Text { anchors.centerIn: parent; text: "Next"; color: "white"; font.pixelSize: 11; font.weight: Font.Bold }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.serviceModel.nextItem() }
                        }
                        Rectangle {
                            width: 40
                            height: 28
                            radius: 8
                            color: Theme.surface
                            Text { anchors.centerIn: parent; text: "Prev"; color: Theme.text; font.pixelSize: 11; font.weight: Font.Bold }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.serviceModel.previousItem() }
                        }
                    }
                }
                Repeater {
                    model: Mxu.timerRows
                    delegate: Rectangle {
                        width: parent.width
                        height: 48
                        radius: 10
                        color: "#2c2c30"
                        Row {
                            anchors.fill: parent
                            anchors.leftMargin: 12
                            anchors.rightMargin: 12
                            spacing: 8
                            Column {
                                width: parent.width - 110
                                Text { text: modelData.label; color: Theme.text; font.pixelSize: 12; font.weight: Font.Bold; elide: Text.ElideRight }
                                Text { text: modelData.value; color: Theme.textDim; font.pixelSize: 11; elide: Text.ElideRight }
                            }
                            Text { text: modelData.delta; color: Theme.textFaint; font.pixelSize: 11; elide: Text.ElideRight }
                        }
                    }
                }
            }
        }
    }

    Component {
        id: timecodeModule
        Rectangle {
            width: moduleLoader.width
            height: moduleLoader.height
            color: "transparent"
            Column {
                anchors.fill: parent
                anchors.margins: 0
                spacing: 8
                Rectangle {
                    width: parent.width
                    height: 80
                    radius: 10
                    color: "#2c2c30"
                    Column {
                        anchors.fill: parent
                        anchors.margins: 12
                        spacing: 4
                        Text { text: Mxu.serviceClock; color: Theme.green; font.pixelSize: 28; font.weight: Font.Bold; horizontalAlignment: Text.AlignCenter }
                        Text { text: "Timecode module"; color: Theme.textDim; font.pixelSize: 11; horizontalAlignment: Text.AlignCenter }
                    }
                }
            }
        }
    }
}
