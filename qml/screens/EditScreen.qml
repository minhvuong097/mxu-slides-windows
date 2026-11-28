import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Dialogs
import "qrc:/qml/theme"
import "qrc:/qml/components"

// Visual slide editor — bound to the generated SlideObject model.
Item {
    id: root
    property real zoom: 1.0
    property real scale: 0.3333  // 1920x1080 document -> 640x360 canvas

    readonly property var animationKinds: ["In", "Out", "Emphasis", "Morph"]
    readonly property var animationEffects: ["Fade", "Move", "Scale", "Wipe", "Blur", "Burn", "Glitch", "Draw", "Type", "Pulse", "Color"]
    readonly property var animationTriggers: ["OnClick", "WithPrevious", "AfterPrevious", "OnDismiss"]
    readonly property var blendModes: ["normal", "multiply", "screen", "add"]
    readonly property var transitionKinds: ["cut", "dissolve", "fadeBlack", "fadeWhite", "fadeColor", "blurDissolve", "filmBurn"]
    readonly property var shapeKinds: ["Rectangle", "RoundedRectangle", "Ellipse", "Path"]

    function animationSteps() {
        return (Mxu.selectedObject.animationSteps || []).map(function (step) {
            return Object.assign({}, step)
        })
    }

    function setAnimationStep(index, key, value) {
        const steps = animationSteps()
        if (index < 0 || index >= steps.length)
            return
        steps[index][key] = value
        Mxu.updateObject({ "animationSteps": steps })
    }

    function addAnimationStep() {
        const steps = animationSteps()
        steps.push({ "kind": "In", "animation": "Fade", "trigger": "OnClick", "durationSeconds": 0.4, "delaySeconds": 0 })
        Mxu.updateObject({ "animationSteps": steps })
    }

    function removeAnimationStep(id) {
        Mxu.updateObject({ "animationSteps": animationSteps().filter(function (step) { return step.id !== id }) })
    }

    Row {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        // ---------------- slide rail ----------------
        Rectangle {
            width: Theme.sidebarWidth
            height: parent.height
            radius: 10
            color: Theme.card
            clip: true

            Column {
                anchors.fill: parent
                anchors.margins: 4
                spacing: 8

                Row {
                    width: parent.width
                    height: 34
                    TrafficLights { anchors.verticalCenter: parent.verticalCenter; windowRef: Window.window }
                    Item { width: 8; height: 1 }
                    IconButton { anchors.verticalCenter: parent.verticalCenter; icon: "sidebar"; onClicked: Mxu.toggleSidebar() }
                }

                Text {
                    anchors.left: parent.left
                    anchors.leftMargin: 4
                    text: "Amazing Grace"
                    color: Theme.text
                    font.pixelSize: 12
                    font.weight: Font.DemiBold
                }

                Flickable {
                    width: parent.width
                    height: parent.height - 48
                    clip: true
                    contentHeight: rail.implicitHeight
                    Column {
                        id: rail
                        width: parent.width
                        spacing: 14
                        Repeater {
                            model: Mxu.slides
                            delegate: Item {
                                id: slideRow
                                property int slideIndex: index
                                width: rail.width
                                height: thumb.height + 16
                                Rectangle {
                                    id: thumb
                                    width: parent.width
                                    height: width * 9 / 16
                                    radius: 8
                                    color: Theme.checkerBase
                                    border.width: 2
                                    border.color: slideIndex === Mxu.selectedSlideIndex ? Mxu.accent : "#333"
                                    Checkerboard { anchors.fill: parent; anchors.margins: 2 }
                                    Text {
                                        anchors.centerIn: parent
                                        width: parent.width - 8
                                        text: modelData.text
                                        color: Theme.text
                                        font.pixelSize: 7
                                        font.weight: Font.Bold
                                        horizontalAlignment: Text.AlignHCenter
                                        wrapMode: Text.WordWrap
                                        maximumLineCount: 3
                                        elide: Text.ElideRight
                                    }
                                    MouseArea {
                                        anchors.fill: parent
                                        drag.target: slideRow
                                        drag.axis: Drag.YAxis
                                        drag.smoothed: false
                                        onReleased: {
                                            const target = Math.max(0, Math.min(Mxu.slides.length - 1,
                                                Math.round(slideRow.y / (thumb.height + 8))))
                                            Mxu.moveSlide(index, target)
                                            slideRow.y = index * (thumb.height + 8)
                                        }
                                        onClicked: Mxu.selectSlide(index)
                                    }
                                }
                                Text {
                                    anchors.left: parent.left
                                    anchors.bottom: parent.bottom
                                    text: index + 1
                                    color: Theme.textDim
                                    font.pixelSize: 10
                                }
                            }
                        }
                    }
                }
            }
        }

        // ---------------- editor ----------------
        Item {
            width: parent.width - Theme.sidebarWidth - 270 - 20
            height: parent.height

            Column {
                anchors.fill: parent
                spacing: 10

                RowLayout {
                    width: parent.width
                    height: 32
                    Item { Layout.fillWidth: true; Layout.preferredHeight: 1 }
                    Segmented {
                        id: editorMode
                        model: ["Edit", "Present", "Stage"]
                        currentIndex: 0
                        onActivated: Mxu.setScreen(["edit", "present", "stage"][index])
                    }
                    Item { Layout.fillWidth: true; Layout.preferredHeight: 1 }
                    PillButton { icon: "record"; iconSize: 16; onClicked: Mxu.toggleRecording() }
                }

                Rectangle {
                    width: parent.width
                    height: 46
                    radius: 10
                    color: Theme.card
                    Row {
                        anchors.fill: parent
                        anchors.leftMargin: 12
                        anchors.rightMargin: 12
                        spacing: 6
                        ToolButton { anchors.verticalCenter: parent.verticalCenter; text: "T"; onClicked: Mxu.addTextObject() }
                        ToolButton { anchors.verticalCenter: parent.verticalCenter; icon: "shape"; onClicked: {} }
                        ToolButton { anchors.verticalCenter: parent.verticalCenter; icon: "image"; onClicked: {} }
                        ToolButton { anchors.verticalCenter: parent.verticalCenter; icon: "video"; onClicked: {} }
                        Item { width: Math.max(0, editorMode.width - 220); height: 1 }
                        Rectangle {
                            anchors.verticalCenter: parent.verticalCenter
                            opacity: Mxu.canUndo ? 1 : 0.4
                            radius: 7; color: Theme.surface
                            implicitWidth: 54; implicitHeight: 26
                            Text { anchors.centerIn: parent; text: "Undo"; color: Theme.text; font.pixelSize: 11 }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.undo() }
                        }
                        Rectangle {
                            anchors.verticalCenter: parent.verticalCenter
                            opacity: Mxu.canRedo ? 1 : 0.4
                            radius: 7; color: Theme.surface
                            implicitWidth: 54; implicitHeight: 26
                            Text { anchors.centerIn: parent; text: "Redo"; color: Theme.text; font.pixelSize: 11 }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.redo() }
                        }
                        Rectangle {
                            anchors.verticalCenter: parent.verticalCenter
                            radius: 7; color: Theme.surface
                            implicitWidth: 88; implicitHeight: 26
                            Text { anchors.centerIn: parent; text: "Export PNG"; color: Theme.text; font.pixelSize: 11 }
                            MouseArea { anchors.fill: parent; onClicked: exportDialog.open() }
                        }
                        Rectangle {
                            anchors.verticalCenter: parent.verticalCenter
                            radius: 7; color: Theme.surface
                            implicitWidth: 96; implicitHeight: 26
                            Text { anchors.centerIn: parent; text: "Full ▾"; color: Theme.text; font.pixelSize: 11 }
                            MouseArea { anchors.fill: parent; onClicked: arrangementPopup.visible = true }
                        }
                        Text { anchors.verticalCenter: parent.verticalCenter; text: "Zoom 100%"; color: Theme.textDim; font.pixelSize: 11 }
                    }
                }

                Rectangle {
                    width: parent.width
                    height: parent.height - 32 - 46 - 20
                    radius: 10
                    color: Theme.card
                    Item {
                        anchors.centerIn: parent
                        width: 640 * root.zoom
                        height: 360 * root.zoom
                        Rectangle {
                            anchors.fill: parent
                            radius: 6
                            color: Theme.checkerBase
                            border.color: "#444"
                            border.width: 1
                            clip: true
                            Checkerboard { anchors.fill: parent; anchors.margins: 1 }

                            Repeater {
                                model: Mxu.slideObjects
                                delegate: Rectangle {
                                    property var obj: modelData
                                    x: obj.x * root.scale * root.zoom
                                    y: obj.y * root.scale * root.zoom
                                    width: obj.width * root.scale * root.zoom
                                    height: obj.height * root.scale * root.zoom
                                    color: "transparent"
                                    border.width: obj.selected ? 2 : 1
                                    border.color: obj.selected ? Mxu.accent : "#555"
                                    Text {
                                        anchors.centerIn: parent
                                        width: parent.width - 8
                                        text: obj.text
                                        color: obj.colorHex
                                        font.pixelSize: obj.fontSize * root.scale * root.zoom
                                        font.family: obj.fontName
                                        font.weight: Font.Bold
                                        lineHeight: 1.35
                                        horizontalAlignment: Text.AlignHCenter
                                        wrapMode: Text.WordWrap
                                    }
                                    MouseArea {
                                        anchors.fill: parent
                                        drag.target: parent
                                        onPressed: Mxu.selectObject(obj.id)
                                        onReleased: Mxu.updateObject({
                                            "x": parent.x / (root.scale * root.zoom),
                                            "y": parent.y / (root.scale * root.zoom),
                                        })
                                    }
                                    Rectangle {
                                        visible: obj.selected
                                        width: 9; height: 9; color: "white"
                                        border.color: Mxu.accent; border.width: 1.5
                                        anchors.left: parent.left; anchors.leftMargin: -5
                                        anchors.top: parent.top; anchors.topMargin: -5
                                    }
                                    Rectangle {
                                        visible: obj.selected
                                        width: 9; height: 9; color: "white"
                                        border.color: Mxu.accent; border.width: 1.5
                                        anchors.right: parent.right; anchors.rightMargin: -5
                                        anchors.top: parent.top; anchors.topMargin: -5
                                    }
                                    Rectangle {
                                        visible: obj.selected
                                        width: 9; height: 9; color: "white"
                                        border.color: Mxu.accent; border.width: 1.5
                                        anchors.left: parent.left; anchors.leftMargin: -5
                                        anchors.bottom: parent.bottom; anchors.bottomMargin: -5
                                    }
                                    Rectangle {
                                        visible: obj.selected
                                        width: 9; height: 9; color: "white"
                                        border.color: Mxu.accent; border.width: 1.5
                                        anchors.right: parent.right; anchors.rightMargin: -5
                                        anchors.bottom: parent.bottom; anchors.bottomMargin: -5
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        // ---------------- inspector ----------------
        Rectangle {
            width: 270
            height: parent.height
            radius: 10
            color: Theme.card
            clip: true
            Flickable {
                anchors.fill: parent
                anchors.margins: 12
                clip: true
                contentHeight: inspector.implicitHeight
                Column {
                    id: inspector
                    width: parent.width
                    spacing: 6

                    Text { text: "Inspector"; color: Theme.text; font.pixelSize: 12; font.weight: Font.DemiBold }

                    Text { text: "POSITION"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                    Row {
                        width: parent.width; spacing: 6
                        NumberField { width: (parent.width - 6) / 2; label: "X"; value: Mxu.selectedObject.x ?? 0; onCommitted: Mxu.updateObject({ "x": value }) }
                        NumberField { width: (parent.width - 6) / 2; label: "Y"; value: Mxu.selectedObject.y ?? 0; onCommitted: Mxu.updateObject({ "y": value }) }
                    }
                    Row {
                        width: parent.width; spacing: 6
                        NumberField { width: (parent.width - 6) / 2; label: "W"; value: Mxu.selectedObject.width ?? 0; onCommitted: Mxu.updateObject({ "width": value }) }
                        NumberField { width: (parent.width - 6) / 2; label: "H"; value: Mxu.selectedObject.height ?? 0; onCommitted: Mxu.updateObject({ "height": value }) }
                    }

                    Text { text: "TEXT"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                    TextField {
                        width: parent.width
                        text: Mxu.selectedObject.text || ""
                        color: Theme.text
                        font.pixelSize: 11
                        background: Rectangle { radius: 7; color: Theme.inset }
                        onAccepted: Mxu.updateObject({ "text": text })
                        onEditingFinished: Mxu.updateObject({ "text": text })
                    }
                    ComboBox {
                        id: fontBox
                        width: parent.width
                        model: Mxu.fontService.families
                        currentIndex: Math.max(0, model.indexOf(Mxu.selectedObject.fontName || "Segoe UI"))
                        onActivated: Mxu.updateObject({ "fontName": fontBox.currentText })
                        background: Rectangle { radius: 7; color: Theme.inset }
                        contentItem: Text { text: fontBox.currentText; color: Theme.text; font.pixelSize: 11; verticalAlignment: Text.AlignVCenter }
                    }
                    Text { text: "STYLE RUNS"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                    Row {
                        width: parent.width; spacing: 6
                        NumberField { id: runLine; width: 52; label: "Line"; value: 0 }
                        NumberField { id: runColumn; width: 56; label: "Col"; value: 0 }
                        NumberField { id: runLength; width: 56; label: "Len"; value: 5 }
                    }
                    Row {
                        width: parent.width; spacing: 6
                        TextField {
                            id: runColor
                            width: parent.width - 92
                            text: "#ffd60a"
                            color: Theme.text
                            font.pixelSize: 11
                            background: Rectangle { radius: 7; color: Theme.inset }
                        }
                        Rectangle {
                            width: 86; height: 24; radius: 7; color: Theme.surface
                            Text { anchors.centerIn: parent; text: "+ Add run"; color: Theme.text; font.pixelSize: 10 }
                            MouseArea {
                                anchors.fill: parent
                                onClicked: Mxu.addStyleRun(runLine.value, runColumn.value, runLength.value, runColor.text)
                            }
                        }
                    }
                    Repeater {
                        model: Mxu.selectedObject.styleRuns || []
                        delegate: Rectangle {
                            width: parent.width; height: 22; radius: 6; color: Theme.inset
                            RowLayout {
                                anchors.fill: parent; anchors.leftMargin: 6; anchors.rightMargin: 6
                                Rectangle { Layout.preferredWidth: 10; Layout.preferredHeight: 10; radius: 2; color: modelData.colorHex || Theme.text }
                                Text { Layout.fillWidth: true; text: "L" + modelData.line + " C" + modelData.column + " ×" + modelData.length; color: Theme.textDim; font.pixelSize: 10 }
                            }
                        }
                    }
                    NumberField { width: parent.width; label: "Size"; value: Mxu.selectedObject.fontSize ?? 0; onCommitted: Mxu.updateObject({ "fontSize": value }) }
                    TextField {
                        width: parent.width
                        text: Mxu.selectedObject.colorHex || "#FFFFFF"
                        color: Theme.text
                        font.pixelSize: 11
                        background: Rectangle { radius: 7; color: Theme.inset }
                        onEditingFinished: Mxu.updateObject({ "colorHex": text })
                    }

                    Text { text: "FILL AND STROKE"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                    TextField {
                        width: parent.width
                        placeholderText: "Fill #RRGGBB"
                        text: Mxu.selectedObject.fillColor || ""
                        color: Theme.text
                        font.pixelSize: 11
                        background: Rectangle { radius: 7; color: Theme.inset }
                        onEditingFinished: Mxu.updateObject({ "fillColor": text })
                    }
                    Row {
                        width: parent.width; spacing: 6
                        TextField {
                            id: strokeColor
                            width: parent.width - 66
                            placeholderText: "Stroke #RRGGBB"
                            text: Mxu.selectedObject.strokeColor || ""
                            color: Theme.text
                            font.pixelSize: 11
                            background: Rectangle { radius: 7; color: Theme.inset }
                            onEditingFinished: Mxu.updateObject({ "strokeColor": text })
                        }
                        NumberField {
                            width: 60; label: "px"; value: Mxu.selectedObject.strokeWidth || 0
                            onCommitted: Mxu.updateObject({ "strokeWidth": value })
                        }
                    }
                    TextField {
                        width: parent.width
                        placeholderText: "Shadow #RRGGBB"
                        text: Mxu.selectedObject.shadowColor || ""
                        color: Theme.text
                        font.pixelSize: 11
                        background: Rectangle { radius: 7; color: Theme.inset }
                        onEditingFinished: Mxu.updateObject({ "shadowColor": text })
                    }
                    Row {
                        width: parent.width; spacing: 6
                        Repeater {
                            model: ["#ffffff", "#ffd60a", "#ff453a", "#30d158", "#0a84ff", "#bf5af2"]
                            delegate: Rectangle {
                                width: 26; height: 20; radius: 5; color: modelData
                                border.color: Theme.border; border.width: 1
                                MouseArea { anchors.fill: parent; onClicked: Mxu.updateObject({ "fillColor": modelData }) }
                            }
                        }
                    }

                    Text { text: "OBJECT"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                    Row {
                        width: parent.width; spacing: 6
                        NumberField { width: (parent.width - 6) / 2; label: "Opacity"; value: Mxu.selectedObject.opacity ?? 1; onCommitted: Mxu.updateObject({ "opacity": value }) }
                        NumberField { width: (parent.width - 6) / 2; label: "Rotate"; value: Mxu.selectedObject.rotationDegrees ?? 0; onCommitted: Mxu.updateObject({ "rotationDegrees": value }) }
                    }
                    ComboBox {
                        id: blendBox
                        width: parent.width
                        model: root.blendModes
                        currentIndex: Math.max(0, model.indexOf(Mxu.selectedObject.blendMode || "normal"))
                        onActivated: Mxu.updateObject({ "blendMode": blendBox.currentText })
                        background: Rectangle { radius: 7; color: Theme.inset }
                        contentItem: Text { text: blendBox.currentText; color: Theme.text; font.pixelSize: 11; verticalAlignment: Text.AlignVCenter }
                    }
                    ComboBox {
                        id: shapeBox
                        width: parent.width
                        model: root.shapeKinds
                        currentIndex: model.indexOf(Mxu.selectedObject.shapeKind || "")
                        onActivated: Mxu.updateObject({ "shapeKind": shapeBox.currentText })
                        background: Rectangle { radius: 7; color: Theme.inset }
                        contentItem: Text { text: shapeBox.currentIndex >= 0 ? shapeBox.currentText : "Shape"; color: Theme.text; font.pixelSize: 11; verticalAlignment: Text.AlignVCenter }
                    }
                    TextField {
                        width: parent.width
                        placeholderText: "Group id"
                        text: Mxu.selectedObject.groupId || ""
                        color: Theme.text
                        font.pixelSize: 11
                        background: Rectangle { radius: 7; color: Theme.inset }
                        onEditingFinished: Mxu.updateObject({ "groupId": text })
                    }

                    Text { text: "ANIMATION"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                    Repeater {
                        model: Mxu.selectedObject.animationSteps || []
                        delegate: Rectangle {
                            width: parent.width
                            height: 104
                            radius: 8
                            color: Theme.inset
                            Column {
                                anchors.fill: parent
                                anchors.margins: 6
                                spacing: 3
                                Row {
                                    width: parent.width; spacing: 4
                                    ComboBox {
                                        id: kindBox; width: (parent.width - 8) / 3
                                        model: root.animationKinds
                                        currentIndex: Math.max(0, model.indexOf(modelData.kind))
                                        onActivated: root.setAnimationStep(index, "kind", kindBox.currentText)
                                        background: Rectangle { radius: 6; color: Theme.surface }
                                        contentItem: Text { text: kindBox.currentText; color: Theme.text; font.pixelSize: 10; verticalAlignment: Text.AlignVCenter }
                                    }
                                    ComboBox {
                                        id: triggerBox; width: (parent.width - 8) / 3
                                        model: root.animationTriggers
                                        currentIndex: Math.max(0, model.indexOf(modelData.trigger))
                                        onActivated: root.setAnimationStep(index, "trigger", triggerBox.currentText)
                                        background: Rectangle { radius: 6; color: Theme.surface }
                                        contentItem: Text { text: triggerBox.currentText; color: Theme.text; font.pixelSize: 9; verticalAlignment: Text.AlignVCenter }
                                    }
                                    Rectangle {
                                        width: (parent.width - 8) / 3; height: 24; radius: 6; color: Theme.surface
                                        Text { anchors.centerIn: parent; text: "✕ Remove"; color: Theme.textDim; font.pixelSize: 10 }
                                        MouseArea { anchors.fill: parent; onClicked: root.removeAnimationStep(modelData.id) }
                                    }
                                }
                                ComboBox {
                                    id: effectBox; width: parent.width
                                    model: root.animationEffects
                                    currentIndex: Math.max(0, model.indexOf(modelData.animation))
                                    onActivated: root.setAnimationStep(index, "animation", effectBox.currentText)
                                    background: Rectangle { radius: 6; color: Theme.surface }
                                    contentItem: Text { text: effectBox.currentText; color: Theme.text; font.pixelSize: 10; verticalAlignment: Text.AlignVCenter }
                                }
                                Row {
                                    width: parent.width; spacing: 4
                                    NumberField { width: (parent.width - 4) / 2; label: "Sec"; value: modelData.durationSeconds; onCommitted: root.setAnimationStep(index, "durationSeconds", value) }
                                    NumberField { width: (parent.width - 4) / 2; label: "Delay"; value: modelData.delaySeconds; onCommitted: root.setAnimationStep(index, "delaySeconds", value) }
                                }
                            }
                        }
                    }
                    Rectangle {
                        width: 120; height: 24; radius: 7; color: Theme.surface
                        Text { anchors.centerIn: parent; text: "+ Animation"; color: Theme.text; font.pixelSize: 10 }
                        MouseArea { anchors.fill: parent; onClicked: root.addAnimationStep() }
                    }

                    Text { text: "TRANSITION"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                    ComboBox {
                        id: transitionBox
                        width: parent.width
                        model: root.transitionKinds
                        currentIndex: Math.max(0, model.indexOf(Mxu.transitionKind))
                        onActivated: Mxu.transitionKind = transitionBox.currentText
                        background: Rectangle { radius: 7; color: Theme.inset }
                        contentItem: Text { text: transitionBox.currentText; color: Theme.text; font.pixelSize: 11; verticalAlignment: Text.AlignVCenter }
                    }
                    Row {
                        width: parent.width; spacing: 6
                        NumberField { width: 78; label: "Sec"; value: Mxu.transitionDuration; onCommitted: Mxu.transitionDuration = value }
                        Rectangle {
                            width: 80; height: 24; radius: 7; color: Theme.accent
                            Text { anchors.centerIn: parent; text: "Preview"; color: "white"; font.pixelSize: 10; font.weight: Font.Bold }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.playTransition() }
                        }
                    }

                    Text { text: "VERSIONS"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                    Repeater {
                        model: Mxu.slideVersions
                        delegate: Rectangle {
                            width: parent.width; height: 24; radius: 6; color: "transparent"
                            RowLayout {
                                anchors.fill: parent; anchors.leftMargin: 6; anchors.rightMargin: 6
                                Text { Layout.fillWidth: true; text: modelData.reason; color: Theme.text; font.pixelSize: 10 }
                                Text { text: modelData.at.slice(0, 10); color: Theme.textDim; font.pixelSize: 9 }
                                Rectangle {
                                    Layout.preferredWidth: 44; Layout.preferredHeight: 18; radius: 5; color: Theme.surface
                                    Text { anchors.centerIn: parent; text: "Restore"; color: Theme.text; font.pixelSize: 9 }
                                    MouseArea { anchors.fill: parent; onClicked: Mxu.restoreSlideVersion(modelData.id) }
                                }
                            }
                        }
                    }
                    Rectangle {
                        width: 110; height: 24; radius: 7; color: Theme.surface
                        Text { anchors.centerIn: parent; text: "+ Save version"; color: Theme.text; font.pixelSize: 10 }
                        MouseArea { anchors.fill: parent; onClicked: Mxu.saveSlideVersion("Manual") }
                    }

                    Text { text: "ACTIONS"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                    Repeater {
                        model: Mxu.currentSlideActions
                        delegate: Rectangle {
                            width: parent.width; height: 26; radius: 6; color: Theme.inset
                            RowLayout {
                                anchors.fill: parent; anchors.leftMargin: 8; anchors.rightMargin: 8
                                Text { Layout.fillWidth: true; text: modelData.kind; color: Theme.text; font.pixelSize: 11 }
                                Rectangle {
                                    radius: 6; color: Theme.accent
                                    implicitWidth: 36; implicitHeight: 20
                                    Text { anchors.centerIn: parent; text: "Fire"; color: "white"; font.pixelSize: 10 }
                                    MouseArea { anchors.fill: parent; onClicked: Mxu.fireSlideAction(modelData.id) }
                                }
                            }
                        }
                    }
                    Grid {
                        width: parent.width; columns: 2; spacing: 6
                        Rectangle {
                            width: (parent.width - 6) / 2; height: 26; radius: 7; color: Theme.surface
                            Text { anchors.centerIn: parent; text: "+ Advance"; color: Theme.text; font.pixelSize: 10 }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.addSlideAction("advance", "") }
                        }
                        Rectangle {
                            width: (parent.width - 6) / 2; height: 26; radius: 7; color: Theme.surface
                            Text { anchors.centerIn: parent; text: "+ Fire alert"; color: Theme.text; font.pixelSize: 10 }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.addSlideAction("fireAlert", "Please wrap up") }
                        }
                        Rectangle {
                            width: (parent.width - 6) / 2; height: 26; radius: 7; color: Theme.surface
                            Text { anchors.centerIn: parent; text: "+ Clear layer"; color: Theme.text; font.pixelSize: 10 }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.addSlideAction("clearLayer", "slide") }
                        }
                        Rectangle {
                            width: (parent.width - 6) / 2; height: 26; radius: 7; color: Theme.surface
                            Text { anchors.centerIn: parent; text: "+ Restore"; color: Theme.text; font.pixelSize: 10 }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.addSlideAction("restore", "") }
                        }
                        Rectangle {
                            width: (parent.width - 6) / 2; height: 26; radius: 7; color: Theme.surface
                            Text { anchors.centerIn: parent; text: "+ Timer"; color: Theme.text; font.pixelSize: 10 }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.addSlideAction("timerStart", "section") }
                        }
                        Rectangle {
                            width: (parent.width - 6) / 2; height: 26; radius: 7; color: Theme.surface
                            Text { anchors.centerIn: parent; text: "+ Combo"; color: Theme.text; font.pixelSize: 10 }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.addSlideAction("combo", "wrapUp") }
                        }
                    }

                    Text { text: "VISIBILITY"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.Bold; font.letterSpacing: 0.66 }
                    Row {
                        width: parent.width; spacing: 6
                        Rectangle {
                            width: 86; height: 26; radius: 7
                            color: Mxu.selectedObject.hidden ? Theme.pink : Theme.surface
                            Text { anchors.centerIn: parent; text: Mxu.selectedObject.hidden ? "Hidden" : "Visible"; color: "white"; font.pixelSize: 10 }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.updateObject({ "hidden": !Mxu.selectedObject.hidden }) }
                        }
                        NumberField {
                            width: 100; label: "Radius"; value: Mxu.selectedObject.cornerRadius || 0
                            onCommitted: Mxu.updateObject({ "cornerRadius": value })
                        }
                        Rectangle {
                            width: 92; height: 26; radius: 7; color: Theme.surface
                            Text { anchors.centerIn: parent; text: "Reset xform"; color: Theme.text; font.pixelSize: 10 }
                            MouseArea {
                                anchors.fill: parent
                                onClicked: Mxu.updateObject({ "x": 0, "y": 0, "rotationDegrees": 0, "opacity": 1 })
                            }
                        }
                    }
                }
            }
        }
    }

    FileDialog {
        id: exportDialog
        title: "Export slide"
        fileMode: FileDialog.SaveFile
        defaultSuffix: "png"
        nameFilters: ["PNG images (*.png)"]
        onAccepted: Mxu.exportSlideImage(selectedFile)
    }

    Rectangle {
        id: arrangementPopup
        anchors.centerIn: parent
        width: 280
        height: 220
        radius: 12
        color: Theme.card
        border.color: "#3a3a3e"
        border.width: 1
        visible: false
        z: 20
        Column {
            anchors.fill: parent
            anchors.margins: 12
            spacing: 6
            Text { text: "Arrangement"; color: Theme.text; font.pixelSize: 12; font.weight: Font.DemiBold }
            Repeater {
                model: Mxu.arrangements.arrangements
                delegate: Rectangle {
                    width: parent.width; height: 28; radius: 6; color: "transparent"
                    Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter; text: modelData.name; color: Theme.text; font.pixelSize: 11 }
                    MouseArea { anchors.fill: parent; onClicked: { Mxu.arrangements.apply(modelData.id); arrangementPopup.visible = false } }
                }
            }
            Rectangle {
                width: parent.width; height: 28; radius: 8; color: Theme.accent
                Text { anchors.centerIn: parent; text: "Save 'Full'"; color: "white"; font.pixelSize: 11 }
                MouseArea { anchors.fill: parent; onClicked: Mxu.arrangements.save("Full", [0, 1, 2]) }
            }
        }
    }
}
