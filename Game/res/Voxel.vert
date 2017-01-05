#version 330

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

attribute vec3 vertexPosition;
attribute vec4 vertexColor;
attribute vec3 vertexNormal;

out vec4 fragmentColor;
out vec3 fragmentNormal;

void main()
{
	fragmentColor = vertexColor;
	fragmentNormal = (modelMatrix * vec4(vertexNormal, 0.0)).xyz;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition, 1.0);
}