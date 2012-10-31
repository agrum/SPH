#version 140

//in vec3 vPosition;
in float vIndex;

uniform sampler1D positionTexMap;
uniform sampler1D velocityTexMap;
uniform int worldSize;
uniform float nbrParticle;

out vec4 fPosition;

void main(){
	vec3 vPosition = texture(positionTexMap, vIndex).xyz * float(worldSize);
	vec3 velocity = 2.0*(texture(velocityTexMap,vIndex).xyz - vec3(0.5,0.5,0.5));
	if(dot(velocity, velocity) < 0.000000001)
		velocity = vec3(0,0,0);
	velocity *= 3.4*50.0;

	fPosition = vec4((vPosition + velocity)/float(worldSize),1);
	fPosition.xyz = clamp(fPosition.xyz, vec3(0,0,0), vec3(1,1,1));
}