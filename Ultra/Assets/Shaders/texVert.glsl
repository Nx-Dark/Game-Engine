#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoords;
layout(location = 3) in float aTexID;
layout(location = 4) in float aTilingFactor;

uniform mat4 u_ProjectionView;

out vec2 v_TexCoords;
out vec4 v_Color;
out float v_TexID;
out float v_TilingFactor;

void main() {

	v_TexCoords = aTexCoords;
	v_Color = aColor;
	v_TexID = aTexID;
	v_TilingFactor = aTilingFactor;

	gl_Position = u_ProjectionView * vec4(aPos, 1.0f);

}