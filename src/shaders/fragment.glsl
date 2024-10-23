#version 460 core

out vec4 frag_color;

in vec3 vertex_color;
in vec2 texcoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mix_percent;

void main() {
	//frag_color = vec4(vertex_color, 1.0);
	frag_color = mix(texture(texture1, texcoord), texture(texture2, texcoord), mix_percent);
};
