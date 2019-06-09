layout (location = 0) out vec3 U;

uniform sampler2D T;
uniform vec2 p;
uniform float radius;
uniform float power;

void main() {
    vec3 o = texelFetch(T, ivec2(gl_FragCoord.xy), 0).xyz;
    vec2 d = gl_FragCoord.xy - p;
    float n = power * exp(-dot(d, d) / radius);
    U = o + vec3(n, 0.0f, 0.0f);
}
