#version 140

in float index;
in vec2 textureCoords;

uniform sampler1D positionTexMap;
uniform float nbrParticle;
uniform int worldSize;
uniform mat4 mv;
uniform mat4 mvp;

out vec2 vTextureCoords;
out float d;
out float vIndex;
out float vX;
out float vY;

void main()
{
	vIndex = (float(index) + 0.5)/nbrParticle;
	vec3 position = texture(positionTexMap, vIndex).xyz * float(worldSize);
	
	vTextureCoords = textureCoords;
	vec4 cc = mv * vec4(position, 1.0f);
	d=length(cc);
	gl_Position = mvp * vec4(position, 1.0f);
	gl_PointSize = 2500*pow(1.0, 3.0)/pow(d, 2.0)/float(worldSize);
	
	vX = texture(positionTexMap, vIndex).x - 0.5;
	vY = texture(positionTexMap, vIndex).y - 0.5;
}
