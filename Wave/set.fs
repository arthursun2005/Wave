layout (location = 0) out vec3 A;

uniform sampler2D T;
uniform vec3 origin;
uniform vec3 value;

void main() {
    vec3 v = texelFetch(T, ivec2(gl_FragCoord.xy), 0).xyz;
    A = v * origin + value;
}
