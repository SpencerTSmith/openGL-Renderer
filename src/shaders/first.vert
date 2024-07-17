#version 460 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_color;
layout (location = 2) in vec2 a_texcoord;

uniform float hor_offset;
uniform mat4 transform;

out vec3 vertex_color;
out vec2 texcoord;

void main() {
	gl_Position = transform * vec4(a_pos.x + hor_offset, a_pos.yz, 1.0);
	vertex_color = vec3(a_color);
	texcoord = a_texcoord;
};