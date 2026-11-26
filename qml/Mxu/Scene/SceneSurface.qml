import QtQuick

// QML fallback used by static tooling; the real app registers the C++
// ScenePaintedItem type under the same module/name from main.cpp.
Rectangle {
    property var layers: []
    property var previousLayers: []
    property real transitionProgress: 1
    property string transitionKind: "dissolve"
    property color background: "black"
    color: "black"
}
