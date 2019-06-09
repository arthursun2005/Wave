layout (location = 0) out float U;

uniform sampler2D T;
uniform sampler2D P;
uniform vec2 invSize;

void main() {
    vec2 coord = gl_FragCoord.xy * invSize;
    
    float n0 = texture(P, coord + vec2(invSize.x, 0.0f)).x;
    float n1 = texture(P, coord - vec2(invSize.x, 0.0f)).x;
    float n2 = texture(P, coord + vec2(0.0f, invSize.y)).x;
    float n3 = texture(P, coord - vec2(0.0f, invSize.y)).x;
    
    float d = texelFetch(T, ivec2(gl_FragCoord.xy), 0).x;
    
    U = (n0 + n1 + n2 + n3 - d) * 0.25f;
}
