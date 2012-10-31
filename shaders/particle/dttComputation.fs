#version 140

in float vIndex;
flat in float clicIgnite;

uniform sampler3D bucketTexMap; 
uniform sampler1D physicalTexMap;
uniform sampler1D positionTexMap;
uniform int worldSize;
uniform float nbrParticle;

out vec4 density;

void main(){
	//Compute velocity
	vec3 P = vec3(0.0f,0.0f,0.0f);
	vec3 V = vec3(0.0f,0.0f,0.0f);
	vec3 G = vec3(0.0f,0.0f,0.0f);
	float m_density = 0;
	float eps = 0.00002;
	float ATMP = 0.9;
	float PI = 3.14159265358979323846264;
	float coefD = 315.0/(64.0*PI);
	float coefT = (2.0*3.0*27.0)/(4.0*4.0*107.0);
	vec3 m_position = texture(positionTexMap, vIndex).xyz * float(worldSize);
	
	
	vec3 baseIndex = (vec3(ivec3(m_position)) + vec3(0.5, 0.5, 0.5))/float(worldSize);
	
	//Density
	for(int i=-1;i<2;i++){ 
		for(int j=-1;j<2;j++){
			for(int k=-1;k<2;k++){
				vec3 offset = vec3(i,j,k)/float(worldSize);
				vec3 index = baseIndex + offset;
				if(clamp(index, vec3(0,0,0), vec3(0.9999,0.9999,0.9999)) == index){
					vec4 indice = texture(bucketTexMap, index);
					float indices[4]= float[4](indice.x,indice.y,indice.z,indice.w);
					for(int l = 0; l < 4 && indices[l] != 0; l++){
						indices[l] = (indices[l]*65536 - 0.5)/nbrParticle;
						if(abs(indices[l] - vIndex) > eps){
							vec3 p_position = texture(positionTexMap, indices[l]).xyz * float(worldSize);
							vec3 diff = (m_position - p_position) * 100;
							float sqDist = dot(diff, diff);
							if(sqDist < 10000.0){
								float dist = sqrt(sqDist)*0.01;
								
								float p_mass = 1.0;
								float tmpCoefD = pow(1.0 - dist*dist, 3);
								m_density += p_mass*coefD*tmpCoefD;
							}
						}
					}
				}
			}
		}	
	}
		
	m_density += 1.0;
	
	density = vec4(m_density*0.01, 0, 0, 1);
}

