pragma Singleton
import QtQuick

// 16x16 line icons matching the mockup's inline SVG glyphs. Paths are drawn
// with QtQuick.Shapes by AppIcon.qml; no external icon font is required.
QtObject {
    function path(name) {
        switch (name) {
        case "sidebar":     return "M1 1h16v14H1z M6.5 1v14"
        case "bell":        return "M8 2.5A3.5 3.5 0 0 0 4.5 6v2.2L3 10.5h10l-1.5-2.3V6A3.5 3.5 0 0 0 8 2.5z M6.5 12.5a1.5 1.5 0 0 0 3 0"
        case "cloud":       return "M4.5 12.5a3 3 0 0 1-.3-6 4 4 0 0 1 7.6 1 2.5 2.5 0 0 1-.3 5z"
        case "search":      return "M7 2.5a4.5 4.5 0 1 0 0 9 4.5 4.5 0 1 0 0-9 M10.5 10.5L14 14"
        case "filter":      return "M2 4h12 M4 8h8 M6 12h4"
        case "chevronDown": return "M4 6l4 4 4-4"
        case "chevronUp":   return "M4 10l4-4 4 4"
        case "chevronRight":return "M6 4l4 4-4 4"
        case "chevronLeft": return "M10 3.5L5.5 8l4.5 4.5"
        case "copy":        return "M6 6h8.5v8.5H6z M11 4.6V4.4A2.4 2.4 0 0 0 8.6 2H4.4A2.4 2.4 0 0 0 2 4.4v4.2A2.4 2.4 0 0 0 4.4 11h.2"
        case "notes":       return "M1.8 2.5h12.4v11H1.8z M4.8 6h6.4 M4.8 8.3h6.4 M4.8 10.6h3.6"
        case "record":      return "M8 1.7a6.3 6.3 0 1 0 0 12.6 6.3 6.3 0 1 0 0-12.6"
        case "recordDot":   return "M8 5.4a2.6 2.6 0 1 0 0 5.2 2.6 2.6 0 1 0 0-5.2"
        case "plus":        return "M8 2.5v11 M2.5 8h11"
        case "grid":        return "M2.5 2.5h4.5v4.5H2.5z M9 2.5h4.5v4.5H9z M2.5 9h4.5v4.5H2.5z M9 9h4.5v4.5H9z"
        case "more":        return "M2.5 8a1 1 0 1 0 2 0 1 1 0 1 0-2 0 M7 8a1 1 0 1 0 2 0 1 1 0 1 0-2 0 M11.5 8a1 1 0 1 0 2 0 1 1 0 1 0-2 0"
        case "play":        return "M4.5 2.5l9 5.5-9 5.5z"
        case "pause":       return "M6.4 1.6h2v12.8h-2z M9.6 1.6h2v12.8h-2z"
        case "checkCircle": return "M2.5 8a5.5 5.5 0 1 0 11 0 5.5 5.5 0 1 0-11 0 M5.8 8l1.7 1.7 2.7-3.2"
        case "check":       return "M3 8.5l3 3 7-7"
        case "clear":       return "M2 8a6 6 0 1 0 12 0A6 6 0 1 0 2 8 M3.8 12.2l8.4-8.4"
        case "sliders":     return "M2 4h4.5 M9.5 4H14 M2 8h1.5 M6.5 8H14 M2 12h6 M11 12h3 M6.5 2.5v3 M8 6.5v3 M9.5 10.5v3"
        case "image":       return "M2 2.5h12v11H2z M5 10.5l2.2-3 1.8 2 1.5-1.5 1.5 2.5"
        case "layers":      return "M8 2.5l5.5 3L8 8.5l-5.5-3z M2.5 8L8 11l5.5-3 M2.5 10.5L8 13.5l5.5-3"
        case "monitor":     return "M2 2.5h12v6H2z M8 8.5v3.5 M5.5 13.2h5"
        case "timer":       return "M8 9V6.5 M6.5 2h3 M3 9a5 5 0 1 0 10 0 5 5 0 1 0-10 0"
        case "bolt":        return "M9 2L4 9h4l-1 5 5-7H8z"
        case "eye":         return "M1.8 8S4 3.8 8 3.8 14.2 8 14.2 8 12 12.2 8 12.2 1.8 8 1.8 8z M8 6.1a1.9 1.9 0 1 0 0 3.8 1.9 1.9 0 1 0 0-3.8"
        case "folder":      return "M2 5a1 1 0 0 1 1-1h3l1.5 1.5H13a1 1 0 0 1 1 1V12a1 1 0 0 1-1 1H3a1 1 0 0 1-1-1z"
        case "newFolder":   return "M2 5a1 1 0 0 1 1-1h3l1.5 1.5H13a1 1 0 0 1 1 1V12a1 1 0 0 1-1 1H3a1 1 0 0 1-1-1z M11.5 7.5v3 M10 9h3"
        case "expand":      return "M9.5 2.5h4v4 M13.5 2.5L9 7 M6.5 13.5h-4v-4 M2.5 13.5L7 9"
        case "skipBack":    return "M2.5 8h8 M7.5 4.5L11 8l-3.5 3.5 M13.5 3.5v9"
        case "pauseCircle": return "M8 1a7 7 0 1 0 0 14A7 7 0 1 0 8 1"
        case "audio":       return "M3 6.2h2.3L8.8 3.5v9L5.3 9.8H3z M11 5.8a3.1 3.1 0 0 1 0 4.4"
        case "ndi":         return "M8 6.7a1.3 1.3 0 1 0 0 2.6 1.3 1.3 0 1 0 0-2.6 M5.4 5.4a3.7 3.7 0 0 0 0 5.2 M10.6 5.4a3.7 3.7 0 0 1 0 5.2 M3.3 3.3a6.7 6.7 0 0 0 0 9.4 M12.7 3.3a6.7 6.7 0 0 1 0 9.4"
        case "clock":       return "M8 2.2a5.8 5.8 0 1 0 0 11.6 5.8 5.8 0 1 0 0-11.6 M8 4.8V8l2.2 1.4"
        case "remote":      return "M4.8 1.8h6.4v12.4H4.8z M7 12h2"
        case "keyboard":    return "M1.5 4h13v8h-13z M4.2 7h.01 M6.7 7h.01 M9.2 7h.01 M11.7 7h.01 M5 9.6h6"
        case "info":        return "M8 2.2a5.8 5.8 0 1 0 0 11.6 5.8 5.8 0 1 0 0-11.6 M8 7.3v3.4 M8 4.7a.5.5 0 1 0 0 1 .5.5 0 1 0 0-1"
        case "shape":       return "M2 2h12v12H2z"
        case "video":       return "M2.5 3.5h8v9h-8z M10.5 6.5l3-2v7l-3-2"
        case "text":        return "M2 4h12 M8 4v9"
        case "undo":        return "M6 5L3 8l3 3 M3 8h7a3 3 0 0 1 0 6"
        case "redo":        return "M10 5l3 3-3 3 M13 8H6a3 3 0 0 0 0 6"
        case "close":       return "M3 3l10 10 M13 3L3 13"
        case "minimize":    return "M3 8h10"
        case "maximize":    return "M3 3h10v10H3z"
        case "sort":        return "M5 6.5L8 3.5l3 3 M5 9.5l3 3 3-3"
        case "settings":    return "M2.5 4.5h6 M11.5 4.5h2 M2.5 11.5h2 M7.5 11.5h6 M8.5 2.8v3.4 M5.5 9.8v3.4"
        default:            return "M8 2a6 6 0 1 0 0 12A6 6 0 1 0 8 2"
        }
    }

    function filled(name) {
        switch (name) {
        case "play":
        case "recordDot":
        case "pause":
        case "text":
            return true
        default:
            return false
        }
    }
}
