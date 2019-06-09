layout (location = 0) out vec2 U;

uniform sampler2D T;
uniform vec2 p;
uniform float power;
uniform float dir;

void main() {
    vec2 o = texelFetch(T, ivec2(gl_FragCoord.xy), 0).xy;
    vec2 d = gl_FragCoord.xy - p;
    vec2 n = vec2(exp(-dot(d, d) / power));
    n = n * (1.0f - dir) + min(n, 1.0f) * power * dir * normalize(d);
    U = o + n;
}
