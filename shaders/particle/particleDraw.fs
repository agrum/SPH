#version 140

in vec2 vTextureCoords;
in float d;
in float vIndex;
in float vX;
in float vY;

out vec4 fragColor;

void main()
{
	float len = length((gl_PointCoord - vec2(0.5, 0.5))*2.0);
	float PI = 3.14159265358979323846264;
	
	if(len < 1)
		fragColor = vec4(1.0-1.0/(0.6*d), 1.0-1.0/(d), 1.0, 1);
	else
		fragColor = vec4(0, 0, 0, 0);
}
