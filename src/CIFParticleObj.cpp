/*
 * CIFParticleObj.cpp
 *
 *  Created on: Jun 1, 2012
 *      Author: agrum
 */

#include "CIFParticleObj.h"

CIFParticleObj::CIFParticleObj(int p_worldSize):
m_nbrParticle(16384),
m_worldSize(p_worldSize),
m_activeParticle(m_nbrParticle),
m_textures(new GLfloat[m_nbrParticle*2]),
m_indices(new GLuint[m_nbrParticle]),
m_indexes(new GLuint[m_nbrParticle]),
m_position("position", 4, GL_RGBA16, GL_RGBA, GL_FLOAT),
m_velocity("velocity", 5, GL_RGBA16, GL_RGBA, GL_FLOAT),
m_density("density", 6, GL_RGB16, GL_RGB, GL_FLOAT),
m_bucket("bucket", 7, GL_RGBA16, GL_RGBA, GL_UNSIGNED_SHORT),
m_physical("physical", 2, GL_RGB16, GL_RGB, GL_FLOAT),
m_textCoords(new QVector2D[m_nbrParticle]),
m_gravity(0)
{
	//Shaders
	m_densityComputation.initProgram("shaders/particle/dttComputation");
	m_velocityUpdate.initProgram("shaders/particle/velocityUpdate");
	m_positionUpdate.initProgram("shaders/particle/positionUpdate");

	//Texture sizes
	m_bucket.setWidth(m_worldSize);
	m_bucket.setHeight(m_worldSize);
	m_bucket.setDepth(m_worldSize);

	m_velocity.setWidth(m_nbrParticle);
	m_position.setWidth(m_nbrParticle);
	m_density.setWidth(m_nbrParticle);

	//fboGen
	glGenFramebuffers(1, &m_fboId);

	//Physical texture
	m_physical.setWidth(3);
	float physicalP[9];
	physicalP[0] = 1.0; //mass liquid
	physicalP[3] = 0.2; //mass fire
	physicalP[6] = 0.4; //mass smoke
	physicalP[1] = 0.4; //viscosity liquid
	physicalP[4] = 0.1; //viscosity fire
	physicalP[7] = 0.4; //viscosity smoke
	physicalP[2] = 0.995; //friction liquid
	physicalP[5] = 0.99; //friction fire
	physicalP[8] = 0.96; //friction smoke
	m_physical.setData(physicalP);

	//Particle initialization
	GLfloat velocities[m_nbrParticle*4];
	GLfloat positions[m_nbrParticle*4];
	GLfloat densities[m_nbrParticle*3];

	for(int a = 0; a < m_nbrParticle; a++){
		m_indexes[a] = a;
		m_indices[a] = a;
		m_textCoords[a] = QVector2D(qrand()%800 + 100, qrand()%800 + 100);
		positions[a*4+0] = 0;
		positions[a*4+1] = 0;
		positions[a*4+2] = 0;
		velocities[a*4+0] = 0.5;
		velocities[a*4+1] = 0.5;
		velocities[a*4+2] = 0.5;
		densities[a*3+0] = 0;
		densities[a*3+1] = 0;
		densities[a*3+2] = 0;
	}
	m_position.setData(positions);
	m_velocity.setData(velocities);
	m_density.setData(densities);

	//Send textures and variables
	QList<CProgram*> programList;
	programList.append(&m_densityComputation);
	programList.append(&m_velocityUpdate);
	programList.append(&m_positionUpdate);

	for(int i = 0; i < programList.size(); i++){
		programList[i]->use();
		m_bucket.send();
		m_density.send();
		m_position.send();
		m_velocity.send();
		m_physical.send();
		CProgram::current()->sendUniform1i("worldSize", m_worldSize);
		CProgram::current()->sendUniform1f("nbrParticle", m_nbrParticle);
	}
}

CIFParticleObj::~CIFParticleObj(){
	glDeleteFramebuffers(1, &m_fboId);
}

void CIFParticleObj::drop(){
	//QVector3D ref(qrand()%700 + 150, qrand()%700 + 150, qrand()%350 + 500);
	QVector3D ref(500, 500, 800);
	QVector3D velocity(0.5,0.5,0.5);
	ref /= 1000.0;

	for(int a = -5; a <= 5; a++){
		for(int b = -5; b <= 5; b++){
			for(int c = -5; c <= 5; c++){
				QVector3D tmp(a, b, c);
				if(tmp.lengthSquared() <= 25){
					QList<QVector3D> pending;
					pending.push_back(ref + tmp/34.0);
					pending.push_back(velocity);
					m_pendingParticles.push_back(pending);
				}
			}
		}
	}
}

void CIFParticleObj::gravity(){
	m_gravity = (m_gravity+1)%2;
}

void CIFParticleObj::iterate(){
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);

	computeDTT();
	updateVelocity();
	updatePosition();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CIFParticleObj::computeDTT(){
	//Clear
	glFramebufferTexture1D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_1D, m_density.id(), 0);
	glViewport(0, 0, m_nbrParticle, 1);

	//Program
	m_densityComputation.use();

	//Get locations
	GLuint indexLoc = glGetAttribLocation(CProgram::currentId(),"index");
	glVertexAttribPointer(indexLoc , 1, GL_UNSIGNED_INT, GL_FALSE, 0, m_indexes);

	//Draw
	glEnableVertexAttribArray(indexLoc);
	glDrawElements( GL_POINTS, m_activeParticle, GL_UNSIGNED_INT, m_indexes );
	glDisableVertexAttribArray(indexLoc);
}

void CIFParticleObj::updateVelocity(){
	//Clear
	glFramebufferTexture1D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_1D, m_velocity.id(), 0);
	glViewport(0, 0, m_nbrParticle, 1);

	//Program
	m_velocityUpdate.use();

	//Get locations
	GLuint indexLoc = glGetAttribLocation(CProgram::currentId(),"index");
	glVertexAttribPointer(indexLoc , 1, GL_UNSIGNED_INT, GL_FALSE, 0, m_indexes);

	//Draw
	glEnableVertexAttribArray(indexLoc);
	glDrawElements( GL_POINTS, m_activeParticle, GL_UNSIGNED_INT, m_indexes );
	glDisableVertexAttribArray(indexLoc);
}
void CIFParticleObj::updatePosition(){
	//Clear
	glFramebufferTexture1D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_1D, m_position.id(), 0);
	glViewport(0, 0, m_nbrParticle, 1);

	//Program
	m_positionUpdate.use();

	//Get locations
	GLuint indexLoc = glGetAttribLocation(CProgram::currentId(),"index");
	glVertexAttribPointer(indexLoc , 1, GL_UNSIGNED_INT, GL_FALSE, 0, m_indexes);

	//Draw
	glEnableVertexAttribArray(indexLoc);
	glDrawElements( GL_POINTS, m_activeParticle, GL_UNSIGNED_INT, m_indexes );
	glDisableVertexAttribArray(indexLoc);
}

void CIFParticleObj::order(const QMatrix4x4& p_mvp){
	QList<int> bucket;
	int cube = m_worldSize*m_worldSize*m_worldSize;
	int x, y, z;
	int indice;

	QMap<double, GLuint> map;
	QMap<double, GLuint>::const_iterator ite;

	//Reinit
	unsigned short* bucketP = (unsigned short*) calloc(cube*4, sizeof(unsigned short));
	for(int a = 0; a < cube; a++)
		bucket.push_back(0);
	m_activeParticle = 0;

	GLfloat positions[m_nbrParticle*4];
	glBindTexture(GL_TEXTURE_1D, m_position.id());
	glGetTexImage(GL_TEXTURE_1D, 0, GL_RGBA, GL_FLOAT, positions);
	GLfloat velocities[m_nbrParticle*4];
	glBindTexture(GL_TEXTURE_1D, m_velocity.id());
	glGetTexImage(GL_TEXTURE_1D, 0, GL_RGBA, GL_FLOAT, velocities);
	GLfloat dtts[m_nbrParticle*3];
	glBindTexture(GL_TEXTURE_1D, m_density.id());
	glGetTexImage(GL_TEXTURE_1D, 0, GL_RGB, GL_FLOAT, dtts);
	for(int a = 0; a < m_nbrParticle; a++){
		QVector3D tmpP(positions[a*4+0], positions[a*4+1], positions[a*4+2]);
		tmpP *= m_worldSize;
		if(tmpP.isNull() && !m_pendingParticles.empty()){
			QList<QVector3D> pending = m_pendingParticles.takeFirst();
			QVector3D pendingPosition = pending[0];
			QVector3D pendingVelocity = pending[1];
			positions[a*4+0] = pendingPosition.x();
			positions[a*4+1] = pendingPosition.y();
			positions[a*4+2] = pendingPosition.z();
			velocities[a*4+0] = pendingVelocity.x();
			velocities[a*4+1] = pendingVelocity.y();
			velocities[a*4+2] = pendingVelocity.z();
			dtts[a*3+0] = 0;
			dtts[a*3+1] = 0;
			dtts[a*3+2] = 0;

			tmpP = pendingPosition*m_worldSize;
		}
		if(!tmpP.isNull()){
			QVector4D tmpQ = tmpP.toVector4D();
			tmpQ.setW(1);
			tmpQ = p_mvp * tmpQ;
			map.insertMulti(-(tmpQ.z()/tmpQ.w()), a);

			QVector2D tmpV = (m_textCoords[a] - QVector2D(500,500))*0.01;
			m_textCoords[a] -= QVector2D(-tmpV.y(),tmpV.x());
			m_textCoords[a] -= tmpV*0.05;
			m_textures[a*2+0] = m_textCoords[a].x()*0.001;
			m_textures[a*2+1] = m_textCoords[a].y()*0.001;
			m_activeParticle++;

			x = tmpP.x();
			y = tmpP.y();
			z = tmpP.z();
			if(x == m_worldSize)
				x--;
			if(y == m_worldSize)
				y--;
			if(z == m_worldSize)
				z--;
			indice = x + y*m_worldSize + z*m_worldSize*m_worldSize;
			if(bucket[indice] < 4){
				bucketP[indice*4 + bucket[indice]] = a+1;
				bucket[indice]++;
			}
		}
	}
	m_pendingParticles.clear();

	int b = 0;
	for(ite = map.constBegin(); ite != map.constEnd(); ite++){
		m_indices[b] = ite.value();
		b++;
	}

	//Affect
	m_position.setData(positions);
	m_bucket.setData(bucketP);
	free(bucketP);
}

void CIFParticleObj::drawSub(){
	//Get locations
	GLuint texLoc = glGetAttribLocation(CProgram::currentId(),"textureCoords");
	GLuint indexLoc = glGetAttribLocation(CProgram::currentId(),"index");
	glVertexAttribPointer(texLoc , 2, GL_FLOAT, GL_FALSE, 0, m_textures );
	glVertexAttribPointer(indexLoc , 1, GL_UNSIGNED_INT, GL_FALSE, 0, m_indexes);

	//Send textures
	m_position.send();
	CProgram::current()->sendUniform1f("nbrParticle", m_nbrParticle);
	CProgram::current()->sendUniform1i("worldSize", m_worldSize);

	//Draw
	glEnableVertexAttribArray(indexLoc);
	glEnableVertexAttribArray(texLoc);
	glDrawElements(GL_POINTS, m_activeParticle, GL_UNSIGNED_INT, m_indices);
	glDisableVertexAttribArray(indexLoc);
	glDisableVertexAttribArray(texLoc);
}
