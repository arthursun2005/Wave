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
    float w0 = w(n0.z);
    float w1 = w(n1.z);
    float w2 = w(n2.z);
    float w3 = w(n3.z);
    float s = w0 + w1 + w2 + w3;
    float m = (n0.x * w0 + n1.x * w1 + n2.x * w2 + n3.x * w3) / s;
    float vel = dt * (1.0f + t.z) * (m - t.x) + t.y;
    U = vec3(t.x + vel * dt, vel, t.z);
}
