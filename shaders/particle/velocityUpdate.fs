#version 140

in float vIndex;

uniform sampler3D bucketTexMap; 
uniform sampler1D densityTexMap;
uniform sampler1D positionTexMap;
uniform sampler1D velocityTexMap;
uniform int worldSize;

uniform float nbrParticle;

out vec4 velocity;

void main(){
	//Compute velocity
	vec3 P = vec3(0.0f,0.0f,0.0f);
	vec3 V = vec3(0.0f,0.0f,0.0f);
	vec3 G = vec3(0.0f,0.0f,0.0f);
	float eps = 0.00002;
	float ATMP = 0.0;
	float PI = 3.14159265358979323846264;
	float coefP = -1.2575;
	float coefV = 1.2575;

	vec3 m_velocity = (texture(velocityTexMap,vIndex).xyz - vec3(0.5, 0.5, 0.5)) *2.0;
	vec3 m_position = texture(positionTexMap, vIndex).xyz * float(worldSize);
	float m_density = texture(densityTexMap,vIndex).r*100.0;
	float m_pressure = ATMP + (m_density - 1.0)*1.2;
	float m_viscosity = 0.4*100.0;
	float m_mass = 1.0;
	float m_friction = 0.995;
	float m_reactDist = 1.5;
	
	vec3 baseIndex = (vec3(ivec3(m_position)) + vec3(0.5, 0.5, 0.5))/float(worldSize);
	
	//Presure and viscosity
	for(int i=-1;i<2;i++){
		for(int j=-1;j<2;j++){
			for(int k=-1;k<2;k++){
				vec3 offset = vec3(i,j,k)/float(worldSize);
				vec3 index = baseIndex + offset;
				vec4 indice = texture(bucketTexMap, index);
				float indices[4]= float[4](indice.x,indice.y,indice.z,indice.w);
				for(int l = 0; l < 4 && indices[l] != 0; l++){
					indices[l] = (indices[l]*65536 - 0.5)/nbrParticle;
					vec3 p_position = texture(positionTexMap, indices[l]).xyz * float(worldSize);
					vec3 diff = (m_position - p_position) * 100;
					float sqDist = dot(diff, diff);
					if(sqDist > 1.0 && sqDist < 22500.0){
						float dist = sqrt(sqDist)*0.01;
						float tmpCoefV = (1.5 - dist);
						float tmpCoefP = pow(m_reactDist - dist, 3.0)/(dist + 0.1);
						
						vec3 p_velocity = (texture(velocityTexMap, indices[l]).xyz - vec3(0.5, 0.5, 0.5)) *2.0;
						float p_density = texture(densityTexMap, indices[l]).r*100.0;
						float p_pressure = ATMP + (p_density - 1.0)*1.2;
						float p_mass = 1.0;
						
						P += (p_position - m_position)*p_mass*tmpCoefP*(m_pressure + p_pressure)/p_density;
						V += (p_velocity - m_velocity)*p_mass*tmpCoefV/p_density;
					}
				}
			}
		}
	}
	
	P *= coefP*0.5;
	V *= coefV*m_viscosity;
	//G = vec3(normalize(vec3(worldSize*0.5, worldSize*0.5, worldSize*0.5) - m_position))*length(vec3(worldSize*0.5, worldSize*0.5, worldSize*0.5) - m_position)/float(worldSize)*0.2/m_density;
	G.z = -0.32*(m_mass - 0.4)/pow(m_density,3);
	
	if(m_position.x < 2.0){
		P.x += pow(2.0 - m_position.x, 3.0)*0.5;
		V -= m_velocity*(3.0 - m_position.x)*coefV*m_viscosity/3.0;}
	else if(m_position.x > float(worldSize-2)){
		P.x -= pow(m_position.x - (worldSize-2), 3.0)*0.5;	
		V -= m_velocity*(1.0+m_position.x - (worldSize-2))*coefV*m_viscosity/3.0;}
	if(m_position.y < 2.0){
		P.y += pow(2.0 - m_position.y, 3.0)*0.5;
		V -= m_velocity*(3.0 - m_position.y)*coefV*m_viscosity/3.0;}
	else if(m_position.y > float(worldSize-2)){
		P.y -= pow(m_position.y - (worldSize-2), 3.0)*0.5;	
		V -= m_velocity*(1.0+m_position.y - (worldSize-2))*coefV*m_viscosity/3.0;}
	if(m_position.z < 2.0){
		P.z += pow(2.0 - m_position.z, 3.0)*0.5;
		V -= m_velocity*(3.0 - m_position.z)*coefV*m_viscosity/3.0;}
	else if(m_position.z > float(worldSize-2)){
		P.z -= pow(m_position.z - (worldSize-2), 3.0)*0.5;
		V -= m_velocity*(1.0+m_position.z - (worldSize-2))*coefV*m_viscosity/3.0;}

	velocity = vec4(m_velocity*m_friction + (P + V + G)*0.001, 1);
	vec3 tmp = m_position + velocity.xyz*3.4*50.0;
	
	if(tmp.x < 0 || tmp.x >= worldSize){
		velocity.x *= -1.0;
		velocity.xyz *= 0.8; 
	}
	if(tmp.y < 0 || tmp.y >= worldSize){
		velocity.y *= -1.0;
		velocity.xyz *= 0.8;
	}
	if(tmp.z < 0 || tmp.z >= worldSize){	
		velocity.z *= -1.0;
		velocity.xyz *= 0.8;
	}
	
	velocity.xyz /= 2.0;
	velocity.xyz += vec3(0.5, 0.5, 0.5);
}

