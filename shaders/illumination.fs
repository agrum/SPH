#version 420

in vec4 vPosition;
in vec2 vTexture;
in vec3 vNormal;
in vec4 shadowCoord;

uniform vec3 diffuse;
uniform int isDiffuseMap;
uniform sampler2D diffuseTexMap;

uniform vec3 specular;
uniform int isSpecularMap;
uniform sampler2D specularTexMap;

uniform struct lightStruct {
	int type;
	vec4 position;
	vec3 direction;
	float intensity;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	int noShadow;
} light;
uniform sampler2D shadowTexMap;

out vec4 fragColor;

void main (void)
{
	vec4 iDiff = vec4(0,0,0,0);
	vec4 iSpec = vec4(0,0,0,0);
	vec4 fDiffuse;
	vec4 fSpecular;
	
	if(isDiffuseMap == 0)
		fDiffuse = vec4(diffuse,1);
	else
		fDiffuse = texture2D(diffuseTexMap, vTexture);
		
	if(isSpecularMap == 0)
		fSpecular = vec4(specular,1);
	else
		fSpecular = texture2D(specularTexMap, vTexture);
	
	//Compute shadows
	vec4 shadowCoordWdivide = shadowCoord / shadowCoord.w ;

	float distanceFromLight = texture2D(shadowTexMap, shadowCoordWdivide.st).z;
		
	float shadow = 1.0;
	if (light.noShadow != 1 && shadowCoordWdivide.z - distanceFromLight > 0.0005)
 		shadow = 0.0;
	
	//Compute rays
	vec3 L;
	if(light.type == 0) //Point light
		L = vec3(normalize(vPosition - light.position));
	else if(light.type == 1) //Directionnal light
		L = normalize(light.direction);
	vec3 E = -normalize(vec3(vPosition));
	vec3 R = normalize(reflect(L,vNormal)); 
	
	//Add light
	iDiff = iDiff + fDiffuse * vec4(light.diffuse * shadow * light.intensity * dot(-L, vNormal),1);
	iSpec = iSpec + fSpecular * vec4(light.specular * shadow * light.intensity * pow(max(dot(R,E),0.0),7.0),1);
	
	fragColor = vec4(iDiff + iSpec);
}