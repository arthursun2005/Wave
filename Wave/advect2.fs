layout (location = 0) out vec2 U;

uniform sampler2D T;
uniform sampler2D V;
uniform vec2 invSize;
uniform float dt;

void main() {
    vec2 v = texelFetch(V, ivec2(gl_FragCoord.xy), 0).xy;
    U = texture(T, invSize * (gl_FragCoord.xy - v * dt)).xy;
}

