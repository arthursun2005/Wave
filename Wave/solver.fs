layout (location = 0) out vec2 U;

uniform sampler2D T;
uniform vec2 invSize;
uniform float dt;

void main() {
    vec2 coord = gl_FragCoord.xy * invSize;
    float n0 = texture(T, coord + vec2(invSize.x, 0.0f)).x;
    float n1 = texture(T, coord - vec2(invSize.x, 0.0f)).x;
    float n2 = texture(T, coord + vec2(0.0f, invSize.y)).x;
    float n3 = texture(T, coord - vec2(0.0f, invSize.y)).x;
    vec2 t = texelFetch(T, ivec2(gl_FragCoord.xy), 0).xy;
    float m = (n0 + n1 + n2 + n3) * 0.25f;
    U = vec2(t.x + t.y * dt, (m - t.x) + t.y);
}
