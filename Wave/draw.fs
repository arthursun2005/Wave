layout (location = 0) out vec4 C;

uniform sampler2D T;
uniform vec2 invSize;

void main() {
    vec3 m = texture(T, gl_FragCoord.xy * invSize).xyz;
    C = m.x * vec4(0.05f, 0.001f, -0.05f, 0.0f) + (1.0f/(m.z + 1.0f)) * vec4(0.05f);
}
