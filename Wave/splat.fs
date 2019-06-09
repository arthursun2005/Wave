layout (location = 0) out vec2 U;

uniform sampler2D T;
uniform vec2 p;
uniform float power;

void main() {
    vec2 o = texelFetch(T, ivec2(gl_FragCoord.xy), 0).xy;
    vec2 d = gl_FragCoord.xy - p;
    float n = exp(-dot(d, d) / power);
    U = o + vec2(n, 0.0f);
}
