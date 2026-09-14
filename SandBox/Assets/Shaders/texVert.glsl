#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoords;

uniform mat4 u_ProjectionView;

out vec2 v_TexCoords;
out vec4 v_Color;

void main() {

	v_TexCoords = aTexCoords;
	v_Color = aColor;

	gl_Position = u_ProjectionView * vec4(aPos, 1.0f);

}