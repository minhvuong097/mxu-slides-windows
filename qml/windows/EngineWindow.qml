import QtQuick
import QtQuick.Window
import "qrc:/qml/theme"
import "qrc:/qml/components"

// Windows counterpart of the macOS "Engine" window. Metal/SceneCanvas is
// replaced by the Qt Quick SceneView surface; the soak test advances the
// presentation and records breadcrumbs in DiagnosticsService.
Window {
    id: engine
    width: 900
    height: 560
    minimumWidth: 760
    minimumHeight: 420
    title: "Engine — MxU Slides"
    color: Theme.bg
    flags: Qt.Window

    property bool soaking: false
    property int soakAdvances: 0
    property real soakStartedMs: 0
    property real soakNowMs: 0
    readonly property string soakElapsedText: soaking ? formatElapsed(soakNowMs - soakStartedMs) : "00:00:00"

    function formatElapsed(ms) {
        const total = Math.max(0, Math.floor(ms / 1000))
        const pad = function (n) { return n < 10 ? "0" + n : "" + n }
        return pad(Math.floor(total / 3600)) + ":" + pad(Math.floor(total / 60) % 60) + ":" + pad(total % 60)
    }

    function startSoak() {
        soakAdvances = 0
        soakStartedMs = Date.now()
        soakNowMs = soakStartedMs
        soaking = true
        Mxu.diagnostics.log("engine.soak started")
    }

    function stopSoak() {
        soaking = false
        Mxu.diagnostics.log("engine.soak stopped: " + soakAdvances + " advances")
    }

    Row {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 12

        Rectangle {
            id: sidebar
            width: 260
            height: parent.height
            radius: 10
            color: Theme.card
            clip: true

            Flickable {
                anchors.fill: parent
                anchors.margins: 12
                contentWidth: width
                contentHeight: stack.implicitHeight
                clip: true

                Column {
                    id: stack
                    width: parent.width
                    spacing: 8

                    Text { text: "LAYER STACK"; color: Theme.textDim; font.pixelSize: 10; font.weight: Font.Bold }
                    Repeater {
                        model: Mxu.renderLayers
                        delegate: Rectangle {
                            width: parent.width
                            height: 30
                            radius: 6
                            color: "#2c2c30"
                            Row {
                                anchors.fill: parent
                                anchors.leftMargin: 8
                                anchors.rightMargin: 8
                                spacing: 6
                                Rectangle {
                                    width: 8; height: 8; radius: 4
                                    anchors.verticalCenter: parent.verticalCenter
                                    color: modelData.visible ? Theme.green : Theme.textFaint
                                }
                                Text {
                                    width: parent.width - 60
                                    anchors.verticalCenter: parent.verticalCenter
                                    text: modelData.kind
                                    color: Theme.text
                                    font.pixelSize: 11
                                    elide: Text.ElideRight
                                }
                                Text {
                                    anchors.verticalCenter: parent.verticalCenter
                                    text: modelData.items.length + ""
                                    color: Theme.textDim
                                    font.pixelSize: 10
                                }
                            }
                        }
                    }

                    Text { text: "OUTPUTS"; color: Theme.textDim; font.pixelSize: 10; font.weight: Font.Bold }
                    Repeater {
                        model: ["main", "stage", "confidence", "preview"]
                        delegate: Text {
                            width: parent.width
                            text: modelData + " · " + Mxu.outputs.assignment(modelData)
                            color: Theme.text
                            font.pixelSize: 11
                            elide: Text.ElideRight
                        }
                    }

                    Text { text: "RUNTIME"; color: Theme.textDim; font.pixelSize: 10; font.weight: Font.Bold }
                    Grid {
                        width: parent.width
                        columns: 2
                        spacing: 4
                        Text { text: "FPS"; color: Theme.textFaint; font.pixelSize: 10 }
                        Text { text: Mxu.diagnostics.fps.toFixed(1); color: Theme.green; font.pixelSize: 10 }
                        Text { text: "Uptime"; color: Theme.textFaint; font.pixelSize: 10 }
                        Text { text: Mxu.diagnostics.uptime; color: Theme.text; font.pixelSize: 10 }
                        Text { text: "Ticks"; color: Theme.textFaint; font.pixelSize: 10 }
                        Text { text: Mxu.diagnostics.tickCount + ""; color: Theme.text; font.pixelSize: 10 }
                        Text { text: "Hitches"; color: Theme.textFaint; font.pixelSize: 10 }
                        Text { text: Mxu.diagnostics.hitchCount + ""; color: Mxu.diagnostics.hitchCount > 0 ? Theme.pink : Theme.text; font.pixelSize: 10 }
                        Text { text: "Max frame"; color: Theme.textFaint; font.pixelSize: 10 }
                        Text { text: Mxu.diagnostics.maxFrameMs.toFixed(1) + " ms"; color: Theme.text; font.pixelSize: 10 }
                        Text { text: "Errors"; color: Theme.textFaint; font.pixelSize: 10 }
                        Text { text: Mxu.diagnostics.errorCount + ""; color: Mxu.diagnostics.errorCount > 0 ? Theme.pink : Theme.text; font.pixelSize: 10 }
                    }

                    Text { text: "MEDIA SOAK"; color: Theme.textDim; font.pixelSize: 10; font.weight: Font.Bold }
                    Rectangle {
                        width: 110
                        height: 26
                        radius: 7
                        color: engine.soaking ? Theme.pink : Theme.accent
                        Text {
                            anchors.centerIn: parent
                            text: engine.soaking ? "Stop soak" : "Start soak"
                            color: "white"
                            font.pixelSize: 10
                            font.weight: Font.Bold
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: engine.soaking ? engine.stopSoak() : engine.startSoak()
                        }
                    }
                    Text {
                        text: "Elapsed " + engine.soakElapsedText + " · " + engine.soakAdvances + " advances"
                        color: engine.soaking ? Theme.green : Theme.textFaint
                        font.pixelSize: 10
                    }
                }
            }
        }

        Rectangle {
            width: parent.width - sidebar.width - 12
            height: parent.height
            radius: 10
            color: "black"
            clip: true

            Item {
                id: canvas
                width: Math.min(parent.width, parent.height * 16 / 9)
                height: width * 9 / 16
                anchors.centerIn: parent
                SceneView { anchors.fill: parent }
            }

            Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                height: 28
                color: "#bb000000"
                Text {
                    anchors.centerIn: parent
                    text: Mxu.currentSlideName + " · FPS " + Mxu.diagnostics.fps.toFixed(1)
                          + " · " + Mxu.diagnostics.uptime
                    color: Theme.textDim
                    font.pixelSize: 10
                    elide: Text.ElideRight
                }
            }
        }
    }

    Timer {
        interval: 900
        repeat: true
        running: engine.soaking
        onTriggered: {
            Mxu.next()
            engine.soakAdvances += 1
            Mxu.diagnostics.log("engine.soak advance " + engine.soakAdvances)
        }
    }

    Timer {
        interval: 1000
        repeat: true
        running: engine.soaking
        onTriggered: engine.soakNowMs = Date.now()
    }
}
