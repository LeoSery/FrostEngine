#version 460 core
in vec2 vColor;
layout(location = 0) out vec4 oFragColor;

uniform sampler2D uTexture;

void main()
{
	vec4 texColor = texture(uTexture, vColor);
	oFragColor = texColor;
	oFragColor = vec4(vColor, 1.0 ,1.0);
}