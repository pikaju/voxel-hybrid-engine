#version 330

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 inverseProjectionMatrix;

uniform sampler2D renderedNormal;
uniform sampler2D renderedDepth;

uniform sampler2D noiseTexture;

const int NUM_SAMPLES = 8;
uniform vec3 samples[NUM_SAMPLES];

in vec2 fragmentTexcoord;

layout(location = 0) out float pixelSSAO;

void main()
{
	float depth = texture(renderedDepth, fragmentTexcoord).r;
	float ssao = float(NUM_SAMPLES);
		
	vec4 deviceCoord = (inverseProjectionMatrix * vec4(fragmentTexcoord * 2.0 - 1.0, depth * 2.0 - 1.0, 1.0));
	vec3 position = deviceCoord.xyz / deviceCoord.w;
	
	vec3 normal = (viewMatrix * vec4(texture(renderedNormal, fragmentTexcoord).xyz * 2.0 - 1.0, 0.0)).xyz;
	vec3 rotation = texture(noiseTexture, fragmentTexcoord * textureSize(renderedDepth, 0) / textureSize(noiseTexture, 0)).xyz * 2.0 - 1.0;
	vec3 tangent = normalize(rotation - normal * dot(rotation, normal));
	vec3 bitangent = cross(normal, tangent);
	mat3 tbn = mat3(tangent, bitangent, normal);

	for (int i = 0; i < NUM_SAMPLES; i++) {
		vec3 offset = tbn * samples[i];
		vec3 samplePosition = position + offset;
		vec4 clipCoord = projectionMatrix * vec4(samplePosition, 1.0);
		float sampleDepth = texture(renderedDepth, clipCoord.xy / clipCoord.w * 0.5 + 0.5).r * 2.0 - 1.0;
		ssao -= sampleDepth <= clipCoord.z / clipCoord.w ? 1.0 : 0.0;
	}
	pixelSSAO = ssao / NUM_SAMPLES;
}