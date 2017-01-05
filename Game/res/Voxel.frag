#version 330

uniform mat4 projectionMatrix;

in vec4 fragmentColor;
in vec3 fragmentNormal;

layout(location = 0) out vec4 pixelColor;
layout(location = 1) out vec3 pixelNormal;
layout(location = 2) out float pixelDepth;

void main()
{
	float light = dot(-fragmentNormal, normalize(vec3(0.5, -1.0, 0.125))) * 0.6 + 1.0;
	pixelColor = vec4(fragmentColor.xyz * light, 1.0);
	pixelNormal = fragmentNormal * 0.5 + 0.5;
	pixelDepth = gl_FragCoord.z;
}