#version 330 core

layout(location = 0) out vec4 fragColor;

in vec2 v_TexCoords;
in vec4 v_Color;

uniform sampler2D u_Texture;
uniform vec4 u_Color;
uniform float u_TilingFactor;

void main() {

	//fragColor = v_Color * texture(u_Texture, v_TexCoords * u_TilingFactor);
	fragColor = v_Color;

}