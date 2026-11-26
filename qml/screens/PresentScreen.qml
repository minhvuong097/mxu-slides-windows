import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import "qrc:/qml/theme"
import "qrc:/qml/components"

// Main "Service Flow — Present" screen (1280x840 in the Claude mockup).
Item {
    id: root
    property string controlTab: "timers"
    property var collapsedSections: []

    Row {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        // ============================================================
        // Left column — Service Flow outline + library browser
        // ============================================================
        Item {
            width: Theme.sidebarWidth
            height: parent.height

            Column {
                anchors.fill: parent
                spacing: 10

                Rectangle {
                    id: serviceCard
                    width: parent.width
                    height: parent.height - 262 - 10
                    radius: 10
                    color: Theme.card
                    clip: true

                    Column {
                        anchors.fill: parent

                        // window dots + quick actions
                        Row {
                            width: parent.width
                            height: 34
                            anchors.leftMargin: 4
                            spacing: 0
                            TrafficLights { anchors.verticalCenter: parent.verticalCenter; anchors.leftMargin: 4; windowRef: Window.window }
                            Item { width: 8; height: 1 }
                            IconButton { anchors.verticalCenter: parent.verticalCenter; icon: "sidebar"; onClicked: Mxu.toggleSidebar() }
                            IconButton { anchors.verticalCenter: parent.verticalCenter; icon: "bell"; iconSize: 18 }
                            IconButton { anchors.verticalCenter: parent.verticalCenter; icon: "cloud"; iconSize: 18 }
                            Item { Layout.fillWidth: true; width: Math.max(0, serviceCard.width - 190); height: 1 }
                            Text {
                                anchors.verticalCenter: parent.verticalCenter
                                text: "Service Flow"
                                color: Theme.textDim
                                font.pixelSize: 11
                                font.weight: Font.DemiBold
                            }
                        }

                        // service + date
                        RowLayout {
                            width: parent.width
                            height: 26
                            anchors.leftMargin: 4
                            anchors.rightMargin: 4
                            spacing: 8
                            Rectangle {
                                Layout.fillWidth: true
                                Layout.preferredHeight: 22
                                radius: 7
                                color: Theme.inset
                                RowLayout {
                                    anchors.fill: parent
                                    anchors.leftMargin: 8
                                    anchors.rightMargin: 8
                                    Text {
                                        Layout.fillWidth: true
                                        text: Mxu.serviceModel.serviceName
                                        color: Theme.text
                                        font.pixelSize: 11
                                        font.weight: Font.DemiBold
                                        elide: Text.ElideRight
                                    }
                                    AppIcon { name: "chevronDown"; size: 12; color: Theme.textDim }
                                }
                            }
                            Text { text: Mxu.serviceModel.serviceDate; color: Theme.textDim; font.pixelSize: 11 }
                        }

                        // service time
                        Row {
                            width: parent.width
                            height: 28
                            anchors.leftMargin: 4
                            Rectangle {
                                radius: 7
                                color: Theme.inset
                                implicitWidth: timeRow.implicitWidth + 16
                                implicitHeight: 22
                                RowLayout {
                                    id: timeRow
                                    anchors.centerIn: parent
                                    Text { text: Mxu.serviceModel.serviceTime; color: Theme.text; font.pixelSize: 11 }
                                    Text { text: Mxu.serviceModel.serviceTimeBadge; color: Theme.orange; font.pixelSize: 11; font.weight: Font.Bold }
                                    AppIcon { name: "chevronDown"; size: 12; color: Theme.textDim }
                                }
                            }
                        }

                        // scrollable outline
                        Flickable {
                            id: outline
                            width: parent.width
                            height: serviceCard.height - 34 - 26 - 28 - 28
                            clip: true
                            contentHeight: outlineColumn.implicitHeight + 8
                            Column {
                                id: outlineColumn
                                width: parent.width
                                spacing: 2
                                Repeater {
                                    model: Mxu.serviceModel.sections
                                    delegate: Column {
                                        id: sectionColumn
                                        property string sectionName: modelData.name
                                        width: parent.width
                                        spacing: 2
                                        Item {
                                            width: parent.width
                                            height: 18
                                            SectionLabel {
                                                anchors.fill: parent
                                                text: modelData.name
                                                labelColor: modelData.color
                                            }
                                            MouseArea {
                                                anchors.fill: parent
                                                onClicked: {
                                                    const idx = sectionColumn.sectionName
                                                    const list = root.collapsedSections
                                                    const at = list.indexOf(idx)
                                                    if (at >= 0) list.splice(at, 1)
                                                    else list.push(idx)
                                                    root.collapsedSections = list
                                                }
                                            }
                                        }
                                        Repeater {
                                            visible: root.collapsedSections.indexOf(sectionColumn.sectionName) < 0
                                            model: modelData.items
                                            delegate: Rectangle {
                                                id: serviceItemRow
                                                width: parent.width
                                                height: 24
                                                radius: 6
                                                color: modelData.selected ? Theme.hover : "transparent"
                                                RowLayout {
                                                    anchors.fill: parent
                                                    anchors.leftMargin: 8
                                                    anchors.rightMargin: 8
                                                    spacing: 6
                                                    Text {
                                                        Layout.fillWidth: true
                                                        text: modelData.name
                                                        color: Theme.text
                                                        font.pixelSize: 12
                                                        elide: Text.ElideRight
                                                    }
                                                    Text {
                                                        visible: (modelData.note || "") !== ""
                                                        text: modelData.note
                                                        color: Theme.textDim
                                                        font.pixelSize: 10
                                                    }
                                                    AppIcon { name: "copy"; size: 17; color: Theme.textIcon }
                                                }
                                                MouseArea {
                                                    anchors.fill: parent
                                                    drag.target: serviceItemRow
                                                    drag.axis: Drag.YAxis
                                                    drag.smoothed: false
                                                    onReleased: {
                                                        const target = Math.max(0, Math.min(Mxu.serviceModel.itemCount - 1,
                                                            Math.round(serviceItemRow.y / 26)))
                                                        Mxu.moveServiceItem(modelData.index, target)
                                                        serviceItemRow.y = modelData.index * 26
                                                    }
                                                    onClicked: Mxu.goToCue(modelData.index)
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        // footer
                        RowLayout {
                            width: parent.width
                            height: 28
                            anchors.leftMargin: 4
                            anchors.rightMargin: 4
                            AppIcon { name: "plus"; size: 12; color: Theme.textDim }
                            Rectangle {
                                Layout.preferredWidth: 92
                                Layout.preferredHeight: 20
                                color: "transparent"
                                Row {
                                    anchors.centerIn: parent
                                    spacing: 5
                                    Text { text: "Add Item"; color: Theme.textDim; font.pixelSize: 11 }
                                    AppIcon { name: "chevronDown"; size: 12; color: Theme.textDim }
                                }
                                MouseArea { anchors.fill: parent; onClicked: addItemPopup.visible = true }
                            }
                            Item { Layout.fillWidth: true; height: 1 }
                            Text { text: Mxu.serviceModel.itemCount + " items"; color: Theme.textDim; font.pixelSize: 11 }
                        }
                    }
                }

                // ---------------- libraries card -----------------------
                Rectangle {
                    width: parent.width
                    height: 262
                    radius: 10
                    color: Theme.card
                    clip: true

                    Column {
                        anchors.fill: parent

                        RowLayout {
                            width: parent.width
                            height: 36
                            anchors.leftMargin: 10
                            anchors.rightMargin: 10
                            spacing: 8
                            Text { text: "Libraries"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.DemiBold }
                            TextField {
                                Layout.fillWidth: true
                                Layout.preferredHeight: 24
                                placeholderText: "Search"
                                color: Theme.text
                                placeholderTextColor: Theme.textDim
                                font.pixelSize: 11
                                leftPadding: 8
                                rightPadding: 8
                                background: Rectangle { radius: 8; color: Theme.searchField }
                                onTextChanged: Mxu.libraryModel.search = text
                            }
                            AppIcon { name: "filter"; size: 15; color: Theme.textDim }
                        }

                        Item {
                            width: parent.width
                            height: 30
                            Segmented {
                                id: libraryTabs
                                anchors.centerIn: parent
                                model: ["Slides", "Media", "Overlays"]
                                currentIndex: 2
                                compact: true
                                width: parent.width - 20
                            }
                            AppIcon {
                                anchors.right: parent.right
                                anchors.rightMargin: 14
                                anchors.verticalCenter: parent.verticalCenter
                                name: "more"
                                size: 14
                                color: Theme.textDim
                            }
                        }

                        Row {
                            width: parent.width
                            height: 24
                            anchors.leftMargin: 12
                            spacing: 3
                            AppIcon { anchors.verticalCenter: parent.verticalCenter; name: "chevronLeft"; size: 11; color: Theme.textDim }
                            Text { anchors.verticalCenter: parent.verticalCenter; text: "Drive"; color: Theme.textDim; font.pixelSize: 10 }
                            AppIcon { anchors.verticalCenter: parent.verticalCenter; name: "chevronRight"; size: 9; color: Theme.textDim }
                            Text { anchors.verticalCenter: parent.verticalCenter; text: "Bold Blocks"; color: Theme.textDim; font.pixelSize: 10 }
                            AppIcon { anchors.verticalCenter: parent.verticalCenter; name: "chevronRight"; size: 9; color: Theme.textDim }
                            Text { anchors.verticalCenter: parent.verticalCenter; text: "Side Thirds"; color: Theme.text; font.pixelSize: 10; font.weight: Font.DemiBold }
                        }

                        Item {
                            width: parent.width
                            height: parent.height - 36 - 30 - 24 - 22 - 30
                            clip: true
                            Grid {
                                id: overlayGrid
                                anchors.fill: parent
                                anchors.leftMargin: 12
                                anchors.rightMargin: 16
                                anchors.topMargin: 2
                                columns: 2
                                spacing: 8
                                property real cellW: (overlayGrid.width - 28) / 2
                                Repeater {
                                    model: [
                                        { title: "Call to Action", stripe: false, accent: true },
                                        { title: "Point (Side Third)", stripe: true, accent: false },
                                        { title: "Verse + Reference (Sid…", stripe: true, accent: false },
                                    ]
                                    delegate: Column {
                                        width: overlayGrid.cellW
                                        Rectangle {
                                            width: overlayGrid.cellW
                                            height: width * 9 / 16
                                            radius: 8
                                            color: Theme.checkerBase
                                            border.color: "#333"
                                            border.width: 1
                                            clip: true
                                            Checkerboard { anchors.fill: parent }
                                            Rectangle {
                                                anchors.right: parent.right
                                                anchors.rightMargin: 20
                                                anchors.top: parent.top
                                                anchors.topMargin: 10
                                                width: 46
                                                height: 64
                                                Column {
                                                    anchors.fill: parent
                                                    spacing: 2
                                                    Rectangle { width: modelData.accent ? 20 : 22; height: 3; color: modelData.accent ? Theme.yellow : Theme.text; opacity: modelData.accent ? 1 : 0.8 }
                                                    Rectangle { width: 40; height: 2; color: Theme.text; opacity: 0.8 }
                                                    Rectangle { width: 36; height: 2; color: Theme.text; opacity: 0.8 }
                                                    Rectangle { width: 30; height: 2; color: Theme.text; opacity: 0.8 }
                                                    Rectangle { width: 18; height: modelData.accent ? 5 : 2; color: modelData.accent ? Theme.yellow : Theme.text; opacity: modelData.accent ? 1 : 0.8 }
                                                }
                                            }
                                            Rectangle {
                                                visible: modelData.stripe
                                                anchors.right: parent.right
                                                anchors.rightMargin: 34
                                                anchors.top: parent.top
                                                anchors.bottom: parent.bottom
                                                width: 2
                                                color: Theme.yellow
                                            }
                                            AppIcon {
                                                anchors.right: parent.right
                                                anchors.rightMargin: 5
                                                anchors.top: parent.top
                                                anchors.topMargin: 5
                                                name: "checkCircle"
                                                size: 12
                                                color: Theme.textDim
                                            }
                                        }
                                        Text {
                                            width: parent.width
                                            text: modelData.title
                                            color: Theme.textDim
                                            font.pixelSize: 10
                                            elide: Text.ElideRight
                                        }
                                    }
                                }
                            }
                        }

                        Rectangle {
                            width: parent.width
                            height: 22
                            color: Theme.statusStrip
                            Text {
                                anchors.left: parent.left
                                anchors.leftMargin: 12
                                anchors.verticalCenter: parent.verticalCenter
                                text: "Imported 1 of 1 files"
                                color: Theme.textDim
                                font.pixelSize: 10
                            }
                        }

                        Row {
                            width: parent.width
                            height: 30
                            anchors.leftMargin: 12
                            spacing: 14
                            Row { anchors.verticalCenter: parent.verticalCenter; AppIcon { name: "plus"; size: 13; color: Theme.textDim } Text { text: "New"; color: Theme.textDim; font.pixelSize: 11 } }
                            Row { anchors.verticalCenter: parent.verticalCenter; AppIcon { name: "newFolder"; size: 14; color: Theme.textDim } Text { text: "New Folder"; color: Theme.textDim; font.pixelSize: 11 } }
                            Item { width: Math.max(0, serviceCard.width - 240); height: 1 }
                            AppIcon { anchors.verticalCenter: parent.verticalCenter; name: "grid"; size: 14; color: Theme.textDim }
                            AppIcon { anchors.verticalCenter: parent.verticalCenter; name: "sliders"; size: 14; color: Theme.textDim }
                        }
                    }
                }
            }
        }

        // ============================================================
        // Centre column — toolbar, cue flow, transport
        // ============================================================
        Item {
            width: parent.width - Theme.sidebarWidth - 290 - 20
            height: parent.height

            Column {
                anchors.fill: parent
                spacing: 8

                // toolbar
                RowLayout {
                    width: parent.width
                    height: 32
                    spacing: 10
                    Row {
                        spacing: 10
                        AppIcon { anchors.verticalCenter: parent.verticalCenter; name: "sliders"; size: 17; color: Theme.textDim }
                        AppIcon { anchors.verticalCenter: parent.verticalCenter; name: "image"; size: 17; color: Theme.textDim }
                        MiniSlider { anchors.verticalCenter: parent.verticalCenter; value: 0.25 }
                        AppIcon { anchors.verticalCenter: parent.verticalCenter; name: "copy"; size: 17; color: Theme.textDim }
                        MiniSlider { anchors.verticalCenter: parent.verticalCenter; value: 0.1 }
                    }
                    Item { Layout.fillWidth: true; height: 1 }
                    Segmented {
                        id: modeSwitch
                        model: ["Edit", "Present", "Stage"]
                        currentIndex: 1
                        outlined: true
                        onActivated: Mxu.setScreen(["edit", "present", "stage"][index])
                    }
                    Item { Layout.fillWidth: true; height: 1 }
                    Row {
                        spacing: 6
                        PillButton {
                            anchors.verticalCenter: parent.verticalCenter
                            icon: "record"; iconSize: 16
                            onClicked: Mxu.toggleRecording()
                        }
                        PillButton {
                            anchors.verticalCenter: parent.verticalCenter
                            icon: "monitor"; text: "Default — All…"
                            onClicked: profilePopup.open()
                        }
                        PillButton {
                            anchors.verticalCenter: parent.verticalCenter
                            icon: "clear"; text: "Clear"; success: true
                            onClicked: Mxu.toggleClear()
                        }
                    }
                }

                // cue flow
                Flickable {
                    id: flow
                    width: parent.width - 18
                    height: parent.height - 32 - 54 - 16
                    clip: true
                    contentHeight: flowColumn.implicitHeight + 8

                    Rectangle {
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        width: 10
                        radius: 5
                        color: Theme.scrollTrack
                        Rectangle {
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.top: parent.top
                            anchors.topMargin: 2
                            height: 44
                            radius: 5
                            color: "#8e8e93"
                        }
                        z: 2
                    }

                    Column {
                        id: flowColumn
                        width: parent.width
                        spacing: 8
                        Repeater {
                            model: Mxu.cueModel.cues
                            delegate: Column {
                                width: parent.width
                                spacing: 8
                                SectionLabel {
                                    visible: modelData.index === 1 || modelData.index === 3
                                    width: parent.width
                                    text: modelData.section
                                    labelColor: modelData.sectionColor
                                    bothRules: modelData.index === 3
                                }
                                CueCard {
                                    width: parent.width
                                    cue: modelData
                                    current: modelData.index === Mxu.cueModel.currentCueIndex
                                    onNotesClicked: Mxu.goToCue(modelData.index)
                                    onSlideClicked: Mxu.cueModel.selectSlide(index)
                                }
                            }
                        }
                    }
                }

                // transport
                RowLayout {
                    width: parent.width
                    height: 54
                    spacing: 10
                    Row {
                        Layout.preferredWidth: 150
                        AppIcon { anchors.verticalCenter: parent.verticalCenter; name: "layers"; size: 15; color: Theme.textDim }
                        Text { anchors.verticalCenter: parent.verticalCenter; text: "Foreground Videos"; color: Theme.textDim; font.pixelSize: 11 }
                        AppIcon { anchors.verticalCenter: parent.verticalCenter; name: "chevronDown"; size: 11; color: Theme.textDim }
                    }
                    Item { Layout.fillWidth: true; height: 1 }
                    Row {
                        spacing: 10
                        Rectangle {
                            width: 34; height: 34
                            radius: 9
                            color: Theme.surfaceAlt
                            AppIcon { anchors.centerIn: parent; name: "play"; size: 13; color: Theme.textFaint }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.next() }
                        }
                        Column {
                            width: 160
                            anchors.verticalCenter: parent.verticalCenter
                            spacing: 4
                            Text { text: "No video playing"; color: Theme.textDim; font.pixelSize: 10 }
                            Rectangle { width: parent.width; height: 3; radius: 2; color: "#2e2e31" }
                            Text { text: "0:00 / 0:00"; color: Theme.textDim; font.pixelSize: 11 }
                        }
                        Rectangle {
                            width: 34; height: 38
                            radius: 9
                            color: Theme.surfaceAlt
                            Column {
                                anchors.centerIn: parent
                                spacing: 1
                                AppIcon { anchors.horizontalCenter: parent.horizontalCenter; name: "skipBack"; size: 15; color: Theme.textFaint }
                                Text { text: "-10"; color: Theme.textFaint; font.pixelSize: 9 }
                            }
                            MouseArea { anchors.fill: parent; onClicked: Mxu.previous() }
                        }
                    }
                    Item { Layout.fillWidth: true; height: 1 }
                    Row {
                        Layout.preferredWidth: 150
                        layoutDirection: Qt.RightToLeft
                        Rectangle {
                            radius: 10
                            color: Theme.surfaceAlt
                            implicitWidth: heldRow.implicitWidth + 20
                            implicitHeight: 34
                            Row {
                                id: heldRow
                                anchors.centerIn: parent
                                spacing: 7
                                Rectangle {
                                    width: 15; height: 15
                                    radius: 8
                                    color: Theme.text
                                    Row {
                                        anchors.centerIn: parent
                                        spacing: 2
                                        Rectangle { width: 1.5; height: 7; color: Theme.bg }
                                        Rectangle { width: 1.5; height: 7; color: Theme.bg }
                                    }
                                }
                                Column {
                                    spacing: 1
                                    Text { text: "Advance held"; color: Theme.textDim; font.pixelSize: 10 }
                                    Text { text: Mxu.advanceHeld; color: Theme.text; font.pixelSize: 12; font.weight: Font.DemiBold }
                                }
                            }
                        }
                    }
                }
            }
        }

        // ============================================================
        // Right column — output preview + service controls
        // ============================================================
        Item {
            width: 290
            height: parent.height

            Column {
                anchors.fill: parent
                spacing: 10

                // output preview
                Rectangle {
                    width: parent.width
                    height: 392
                    radius: 10
                    color: Theme.card

                    Column {
                        anchors.fill: parent
                        anchors.margins: 10

                        RowLayout {
                            width: parent.width
                            height: 22
                            Text { text: "Output Preview"; color: Theme.textDim; font.pixelSize: 11; font.weight: Font.DemiBold }
                            Item { Layout.fillWidth: true; height: 1 }
                            Rectangle {
                                radius: 7
                                color: Theme.inset
                                implicitWidth: 150
                                implicitHeight: 20
                                RowLayout {
                                    anchors.fill: parent
                                    anchors.leftMargin: 8
                                    anchors.rightMargin: 8
                                    Text { Layout.fillWidth: true; text: "MultiView — Tall Stack"; color: Theme.textDim; font.pixelSize: 11; elide: Text.ElideRight }
                                    AppIcon { name: "chevronDown"; size: 12; color: Theme.textDim }
                                }
                            }
                        }

                        Rectangle {
                            width: parent.width
                            height: parent.height - 22
                            radius: 10
                            color: "black"
                            border.color: "#2a2a2c"
                            border.width: 1
                            clip: true

                            Column {
                                anchors.fill: parent
                                anchors.margins: 4

                                Rectangle {
                                    width: parent.width
                                    height: 136
                                    border.color: "#555"
                                    border.width: 1
                                    gradient: Gradient {
                                        GradientStop { position: 0; color: Theme.stageTop }
                                        GradientStop { position: 1; color: Theme.checkerBase }
                                    }
                                    Text {
                                        anchors.centerIn: parent
                                        text: "PROSLIDES"
                                        color: Theme.text
                                        font.pixelSize: 15
                                        font.weight: Font.ExtraBold
                                        font.letterSpacing: 0.75
                                    }
                                    Row {
                                        Repeater {
                                            model: [0.2, 0.6, 0.86]
                                            delegate: Rectangle {
                                                x: 136 * modelData * 0.2 + modelData * 200
                                                y: modelData * 24
                                                width: 2; height: 2
                                                radius: 1
                                                color: "white"
                                            }
                                        }
                                    }
                                }
                                Text {
                                    width: parent.width
                                    text: "Live Stream"
                                    color: Theme.textMid
                                    font.pixelSize: 13
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignHCenter
                                }
                                Rectangle {
                                    width: parent.width
                                    height: 148
                                    color: "black"
                                    border.color: Theme.borderMid
                                    border.width: 1
                                    Column {
                                        anchors.fill: parent
                                        anchors.margins: 8
                                        Row {
                                            width: parent.width
                                            Text { width: parent.width * 0.38; text: Mxu.serviceTimerText; color: Theme.textMid; font.pixelSize: 9; font.weight: Font.Bold; horizontalAlignment: Text.AlignHCenter }
                                            Text { width: parent.width * 0.24; text: Mxu.previewClock; color: Theme.textMid; font.pixelSize: 9; font.weight: Font.Bold; horizontalAlignment: Text.AlignHCenter }
                                        }
                                        Rectangle {
                                            width: parent.width
                                            height: 56
                                            radius: 8
                                            color: "transparent"
                                            border.color: Theme.text
                                            border.width: 1
                                            Text {
                                                anchors.bottom: parent.bottom
                                                anchors.bottomMargin: -5
                                                anchors.horizontalCenter: parent.horizontalCenter
                                                text: "CURRENT SLIDE"
                                                color: Theme.text
                                                font.pixelSize: 7
                                                font.weight: Font.ExtraBold
                                                font.letterSpacing: 0.28
                                            }
                                        }
                                        Rectangle {
                                            width: parent.width
                                            height: 56
                                            radius: 8
                                            color: "transparent"
                                            border.color: Theme.goldBorder
                                            border.width: 1
                                            anchors.topMargin: 6
                                            Column {
                                                anchors.fill: parent
                                                anchors.leftMargin: 8
                                                anchors.rightMargin: 8
                                                Text { text: Mxu.currentChord; color: Theme.gold; font.pixelSize: 9; font.weight: Font.Bold }
                                                Text { text: Mxu.currentSlideText; color: Theme.text; font.pixelSize: 12; font.weight: Font.Bold }
                                                Text { anchors.left: parent.left; anchors.leftMargin: parent.width * 0.42; text: Mxu.nextChord; color: Theme.gold; font.pixelSize: 9; font.weight: Font.Bold }
                                                Text { text: Mxu.nextSlideText; color: Theme.text; font.pixelSize: 12; font.weight: Font.Bold }
                                            }
                                            Text {
                                                anchors.bottom: parent.bottom
                                                anchors.bottomMargin: -5
                                                anchors.horizontalCenter: parent.horizontalCenter
                                                text: "NEXT SLIDE"
                                                color: Theme.gold
                                                font.pixelSize: 7
                                                font.weight: Font.ExtraBold
                                                font.letterSpacing: 0.28
                                            }
                                        }
                                    }
                                }
                                Text {
                                    width: parent.width
                                    text: "Confidence Monitor"
                                    color: Theme.textMid
                                    font.pixelSize: 13
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignHCenter
                                }
                            }
                        }
                    }
                }

                // service controls
                Rectangle {
                    width: parent.width
                    height: parent.height - 402
                    radius: 10
                    color: Theme.card
                    clip: true

                    Column {
                        anchors.fill: parent
                        anchors.margins: 10

                        RowLayout {
                            width: parent.width
                            height: 20
                            Text { text: "Service Controls"; color: Theme.text; font.pixelSize: 11; font.weight: Font.DemiBold }
                            Item { Layout.fillWidth: true; height: 1 }
                            AppIcon { name: "expand"; size: 12; color: Theme.textDim }
                        }

                        Row {
                            width: parent.width
                            height: 28
                            spacing: 2
                            Rectangle {
                                radius: 10
                                color: root.controlTab === "combos" ? "#1b1b1d" : Theme.segmentedBg
                                width: (parent.width - 44) / 2
                                height: 28
                                Row {
                                    anchors.centerIn: parent
                                    spacing: 6
                                    AppIcon { anchors.verticalCenter: parent.verticalCenter; name: "bolt"; size: 12; color: root.controlTab === "combos" ? Theme.green : Theme.textDim }
                                    Text { anchors.verticalCenter: parent.verticalCenter; text: "Combos"; color: root.controlTab === "combos" ? Theme.green : Theme.textDim; font.pixelSize: 11 }
                                }
                                MouseArea { anchors.fill: parent; onClicked: root.controlTab = "combos" }
                            }
                            Rectangle {
                                radius: 10
                                color: root.controlTab === "timers" ? "#1b1b1d" : Theme.segmentedBg
                                width: (parent.width - 44) / 2
                                height: 28
                                Row {
                                    anchors.centerIn: parent
                                    spacing: 6
                                    AppIcon { anchors.verticalCenter: parent.verticalCenter; name: "timer"; size: 12; color: Theme.green }
                                    Text { anchors.verticalCenter: parent.verticalCenter; text: "Timers"; color: Theme.green; font.pixelSize: 11 }
                                }
                                MouseArea { anchors.fill: parent; onClicked: root.controlTab = "timers" }
                            }
                            Rectangle {
                                width: 44; height: 28
                                radius: 10
                                color: "#1b1b1d"
                                AppIcon { anchors.centerIn: parent; name: "more"; size: 14; color: Theme.green }
                            }
                        }

                        SettingField { width: parent.width; label: "Now"; value: Mxu.currentServiceItem }
                        SettingField { width: parent.width; label: "Next"; value: Mxu.nextServiceItem }

                        Rectangle { width: parent.width - 20; height: 1; color: "#3a3a3d"; anchors.left: parent.left; anchors.leftMargin: 10 }

                        RowLayout {
                            visible: root.controlTab === "timers"
                            width: parent.width
                            height: 36
                            Item { Layout.fillWidth: true; height: 1 }
                            Text { text: "9:00 AM"; color: Theme.text; font.pixelSize: 11; font.weight: Font.DemiBold }
                            Text { text: Mxu.timerState; color: Theme.textDim; font.pixelSize: 11 }
                            Rectangle {
                                radius: 8
                                color: Theme.startButton
                                implicitWidth: startRow.implicitWidth + 28
                                implicitHeight: 28
                                Row {
                                    id: startRow
                                    anchors.centerIn: parent
                                    spacing: 7
                                    AppIcon { anchors.verticalCenter: parent.verticalCenter; name: "pauseCircle"; size: 15; color: Theme.text }
                                    AppIcon { anchors.verticalCenter: parent.verticalCenter; name: "play"; size: 8; color: Theme.bg }
                                    Text { anchors.verticalCenter: parent.verticalCenter; text: Mxu.timerRunning ? "Pause" : "Start"; color: Theme.text; font.pixelSize: 11; font.weight: Font.DemiBold }
                                }
                                MouseArea { anchors.fill: parent; onClicked: Mxu.toggleTimer() }
                            }
                        }

                        Text { visible: root.controlTab === "timers"; text: "Pre-Service Preroll"; color: Theme.text; font.pixelSize: 11; font.weight: Font.DemiBold }
                        Row {
                            visible: root.controlTab === "timers"
                            spacing: 8
                            Text { text: Mxu.serviceTimerText; color: Theme.text; font.pixelSize: 30; font.weight: Font.DemiBold }
                            Text { anchors.verticalCenter: parent.verticalCenter; text: Mxu.serviceTimerDelta; color: Theme.textDim; font.pixelSize: 11 }
                        }

                        Repeater {
                            model: Mxu.timerRows
                            delegate: Row {
                                visible: root.controlTab === "timers"
                                width: parent.width
                                height: 22
                                Text { width: parent.width * 0.5; anchors.verticalCenter: parent.verticalCenter; text: modelData.label; color: Theme.textDim; font.pixelSize: 11; elide: Text.ElideRight }
                                Text { width: parent.width * 0.28; anchors.verticalCenter: parent.verticalCenter; text: modelData.delta; color: Theme.textDim; font.pixelSize: 11; horizontalAlignment: Text.AlignRight }
                                Text { width: parent.width * 0.22; anchors.verticalCenter: parent.verticalCenter; text: modelData.value; color: Theme.text; font.pixelSize: 11; font.weight: Font.DemiBold; horizontalAlignment: Text.AlignRight }
                            }
                        }

                        Text {
                            visible: root.controlTab === "timers"
                            width: parent.width
                            text: "Preview only: a run of this plan from now. Nothing is saved, and the real service starts fresh."
                            color: Theme.textDim
                            font.pixelSize: 10
                            wrapMode: Text.WordWrap
                            lineHeight: 1.35
                        }

                        Rectangle {
                            visible: root.controlTab === "timers"
                            width: parent.width
                            height: 90
                            color: "transparent"
                            Column {
                                anchors.fill: parent
                                spacing: 4
                                Repeater {
                                    model: Mxu.timerBoard.timers
                                    delegate: Row {
                                        width: parent.width
                                        height: 26
                                        Text { width: parent.width * 0.5; text: modelData.name; color: Theme.text; font.pixelSize: 10; elide: Text.ElideRight }
                                        Text { width: parent.width * 0.2; text: (modelData.remaining / 60).toFixed(0) + ":" + String(modelData.remaining % 60).padStart(2, "0"); color: modelData.warned ? Theme.yellow : Theme.text; font.pixelSize: 11; font.weight: Font.DemiBold }
                                        Rectangle {
                                            width: 44; height: 20; radius: 6; color: Theme.surface
                                            Text { anchors.centerIn: parent; text: modelData.running ? "Pause" : "Start"; color: Theme.text; font.pixelSize: 9 }
                                            MouseArea {
                                                anchors.fill: parent
                                                onClicked: modelData.running ? Mxu.timerBoard.pause(modelData.id) : Mxu.timerBoard.start(modelData.id)
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        Rectangle {
                            visible: root.controlTab === "combos"
                            width: parent.width
                            height: Math.max(120, parent.height - 90)
                            color: "transparent"
                            Column {
                                anchors.fill: parent
                                spacing: 4
                                Repeater {
                                    model: Mxu.automation.triggers
                                    delegate: Rectangle {
                                        width: parent.width
                                        height: 32
                                        radius: 7
                                        color: Theme.inset
                                        RowLayout {
                                            anchors.fill: parent
                                            anchors.leftMargin: 8
                                            anchors.rightMargin: 8
                                            Text { Layout.fillWidth: true; text: modelData.action; color: Theme.text; font.pixelSize: 11 }
                                            Text { text: modelData.kind === "key" ? modelData.value : "MIDI " + modelData.value; color: Theme.textDim; font.pixelSize: 10 }
                                            Rectangle {
                                                radius: 6; color: Theme.accent
                                                implicitWidth: 36; implicitHeight: 22
                                                Text { anchors.centerIn: parent; text: "Fire"; color: "white"; font.pixelSize: 10 }
                                                MouseArea { anchors.fill: parent; onClicked: Mxu.automation.fire(modelData.action) }
                                            }
                                        }
                                    }
                                }
                                Text {
                                    visible: Mxu.automation.triggers.length === 0
                                    text: "No combos yet. Add them in Settings › Shortcuts."
                                    color: Theme.textDim
                                    font.pixelSize: 11
                                }

                                Rectangle { height: 6; width: 1; color: "transparent" }

                                Text { text: "ALERT"; color: Theme.textDim; font.pixelSize: 9; font.weight: Font.Bold; font.letterSpacing: 0.72 }
                                TextField {
                                    id: alertText
                                    width: parent.width
                                    placeholderText: "Message for stage / audience"
                                    placeholderTextColor: Theme.textDim
                                    color: Theme.text
                                    font.pixelSize: 11
                                    background: Rectangle { radius: 7; color: Theme.inset }
                                }
                                Row { spacing: 6
                                    Rectangle {
                                        radius: 9; color: Theme.pink
                                        implicitWidth: 82; implicitHeight: 26
                                        Text { anchors.centerIn: parent; text: "Fire alert"; color: "white"; font.pixelSize: 11; font.weight: Font.DemiBold }
                                        MouseArea { anchors.fill: parent; onClicked: Mxu.alerts.fire(alertText.text, "both") }
                                    }
                                    Rectangle {
                                        radius: 9; color: Theme.surface
                                        implicitWidth: 70; implicitHeight: 26
                                        Text { anchors.centerIn: parent; text: "Dismiss"; color: Theme.text; font.pixelSize: 11 }
                                        MouseArea { anchors.fill: parent; onClicked: Mxu.alerts.dismiss() }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        id: addItemPopup
        anchors.centerIn: parent
        width: 320
        height: 130
        radius: 12
        color: Theme.card
        border.color: "#3a3a3e"
        border.width: 1
        visible: false
        z: 20
        Column {
            anchors.fill: parent
            anchors.margins: 14
            spacing: 8
            Text { text: "New service item"; color: Theme.text; font.pixelSize: 13; font.weight: Font.DemiBold }
            TextField {
                id: newItemName
                width: parent.width
                placeholderText: "Item name"
                placeholderTextColor: Theme.textDim
                color: Theme.text
                font.pixelSize: 12
                background: Rectangle { radius: 7; color: Theme.inset }
            }
            Rectangle {
                width: 100; height: 28; radius: 9; color: Theme.accent
                Text { anchors.centerIn: parent; text: "Add"; color: "white"; font.pixelSize: 11; font.weight: Font.DemiBold }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (Mxu.addServiceItem(newItemName.text, 0))
                            addItemPopup.visible = false
                    }
                }
            }
        }
    }

    OutputProfilePopup {
        id: profilePopup
        anchors.centerIn: parent
        onCloseRequested: hide()
    }
}
