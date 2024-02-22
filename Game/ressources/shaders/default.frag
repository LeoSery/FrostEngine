#version 460 core
in vec3 vColor;
layout(location = 0) out vec4 oFragColor;
void main()
{
	oFragColor = vec4(vColor, 1.0);
}