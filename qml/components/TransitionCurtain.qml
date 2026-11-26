import QtQuick

// Shader-driven transition curtain. Replaces a plain coloured Rectangle with
// a small GLSL effect: dissolve noise for burn, otherwise a smooth wash.
ShaderEffect {
    id: curtain
    property color curtainColor: "black"
    property real strength: 0
    property bool burn: false

    fragmentShader: "
        varying vec2 qt_TexCoord0;
        uniform vec4 curtainColor;
        uniform float strength;
        uniform bool burn;
        float noise(vec2 p) {
            return fract(sin(dot(p, vec2(12.9898, 78.233))) * 43758.5453);
        }
        void main() {
            float a = curtainColor.a * strength;
            if (burn) {
                float n = noise(floor(qt_TexCoord0 * 80.0));
                a *= smoothstep(0.15, 0.85, n + strength - 0.5);
            }
            gl_FragColor = vec4(curtainColor.rgb, a);
        }
    "
}
