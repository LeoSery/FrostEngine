#version 460 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aColor;
out vec2 vColor;

uniform vec2  uPosition;
uniform float uRotation;
uniform vec2  uScale;
uniform float uAspectRatio;

void main()
{
	mat2 rotMatrix = mat2(cos(uRotation), -sin(uRotation), sin(uRotation), cos(uRotation));
	vec2 finalPos = ((rotMatrix * aPos) * uScale + uPosition) / vec2(uAspectRatio, 1.0) * 0.1;

	gl_Position = vec4(finalPos, 0.0, 1.0);
	vColor = aColor;
}