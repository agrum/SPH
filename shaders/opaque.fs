#version 140

in vec4 vPosition;
in vec2 vTexture;
in vec3 vNormal;

uniform vec3 ambient;
uniform int isAmbientMap;
uniform sampler2D ambientTexMap;

out vec4 fColor;

void main (void)
{
	vec4 fAmbient;

	if(isAmbientMap == 0)
		fAmbient = vec4(ambient,1);
	else
		fAmbient = texture2D(ambientTexMap, vTexture);

	fColor = fAmbient / length(vPosition) * ( 1 - pow(1 - dot(normalize(-vPosition), normalize(vec4(vNormal, 0))),2));
}