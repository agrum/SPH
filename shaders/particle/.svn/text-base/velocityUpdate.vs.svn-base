#version 140

in float index;

uniform float nbrParticle;

out float vIndex;

void main(){

	vIndex = (float(index) + 0.5)/nbrParticle;
	gl_Position = vec4((float(index) + 1.0)*2.0/nbrParticle - 1.0,0,0,1);
}