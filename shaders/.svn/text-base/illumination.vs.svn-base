#version 420

in vec3 position;
in vec2 texture;
in vec3 normal;

uniform mat4 mvp;
uniform mat4 mv;
uniform mat3 mvi;
uniform mat4 shadowTexMat;

out vec4 vPosition;
out vec2 vTexture;
out vec3 vNormal;
out vec4 shadowCoord;

void main()
{
	vPosition = mv * vec4(position, 1);
	vTexture = texture;
	vNormal = normalize(mvi * normal);
	shadowCoord = shadowTexMat * vec4(position, 1);
	
	gl_Position = mvp * vec4(position, 1.0f);
}