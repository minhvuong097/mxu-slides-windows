pragma Singleton
import QtQuick

// Operator-local service timing (Mac ServiceTimingController parity).
// The first fire on this PC starts a local clock; clearing it stops the timers.
QtObject {
    property bool active: false
    property real firstFireMs: 0
    property real lastFireMs: 0
    property real nowMs: 0
    property int fireCount: 0
    property var fires: []

    readonly property string elapsedText: active ? stamp(nowMs - firstFireMs) : "--:--"

    function stamp(ms) {
        var total = Math.max(0, Math.floor(ms / 1000))
        var h = Math.floor(total / 3600)
        var m = Math.floor((total % 3600) / 60)
        var s = total % 60
        var pad = function (n) { return n < 10 ? "0" + n : "" + n }
        return h > 0 ? h + ":" + pad(m) + ":" + pad(s) : pad(m) + ":" + pad(s)
    }

    function tick() {
        if (active)
            nowMs = Date.now()
    }

    function fire(name) {
        var at = Date.now()
        if (!active) {
            active = true
            firstFireMs = at
        }
        lastFireMs = at
        nowMs = at
        fireCount += 1
        var list = fires.slice()
        list.push({ name: name || ("Item " + fireCount), at: at })
        fires = list
    }

    function clear() {
        active = false
        firstFireMs = 0
        lastFireMs = 0
        nowMs = 0
        fireCount = 0
        fires = []
    }
}
