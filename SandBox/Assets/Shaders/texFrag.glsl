#version 330 core

layout(location = 0) out vec4 fragColor;

in vec2 v_TexCoords;
in vec4 v_Color;
in float v_TexID;
in float v_TilingFactor;

uniform sampler2D u_Textures[32];

void main() {

	fragColor = v_Color * texture(u_Textures[int(v_TexID)], v_TexCoords * v_TilingFactor);

}