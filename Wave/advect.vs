layout (location = 0) in vec2 uv;

uniform sampler2D T;
uniform sampler2D V;
uniform vec2 size;
uniform float dt;

uniform int x;
uniform int y;

flat out vec2 A;

float dist(vec2 d) {
    return (1.0f - abs(d.x)) * (1.0f - abs(d.y));
}

void main() {
    ivec2 k = ivec2(size * uv);
    vec2 v = texelFetch(V, k, 0).xy;
    vec2 p = size * uv + v * dt;
    float xs[2] = float[](floor(p.x - 0.5f) + 0.5f, floor(p.x - 0.5f) + 1.5f);
    float ys[2] = float[](floor(p.y - 0.5f) + 0.5f, floor(p.y - 0.5f) + 1.5f);
    vec2 rp = vec2(xs[x], ys[y]);
    A = texelFetch(T, k, 0).xy * dist(rp - p);
    gl_Position = vec4(rp / size * 2.0f - 1.0f, 0.0f, 1.0f);
}
