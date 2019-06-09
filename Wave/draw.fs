layout (location = 0) out vec4 C;

uniform sampler2D T;
uniform vec2 invSize;

void main() {
    float m = texture(T, gl_FragCoord.xy * invSize).x;
    C = vec4(m * 0.1f, m * 0.005f, m, 1.0f);
}
