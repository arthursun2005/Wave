layout (location = 0) out vec3 U;

uniform sampler2D T;
uniform vec2 invSize;
uniform float dt;

float w(float x) {
    return min(1.0f + x, 1.0f);
}

void main() {
    vec2 coord = gl_FragCoord.xy * invSize;
    vec3 n0 = texture(T, coord + vec2(invSize.x, 0.0f)).xyz;
    vec3 n1 = texture(T, coord - vec2(invSize.x, 0.0f)).xyz;
    vec3 n2 = texture(T, coord + vec2(0.0f, invSize.y)).xyz;
    vec3 n3 = texture(T, coord - vec2(0.0f, invSize.y)).xyz;
    vec3 t = texelFetch(T, ivec2(gl_FragCoord.xy), 0).xyz;
    float s = w(n0.z) + w(n1.z) + w(n2.z) + w(n3.z);
    float m = (n0.x * w(n0.z) + n1.x * w(n1.z) + n2.x * w(n2.z) + n3.x * w(n3.z)) / s;
    float vel = dt * (1.0f + t.z) * (m - t.x) + t.y;
    U = vec3(t.x + vel * dt, vel, t.z);
}
