/*
 * CIFParticle.h
 *
 *  Created on: Jun 1, 2012
 *      Author: agrum
 */

#ifndef CIFPARTICLEOBJ_H_
#define CIFPARTICLEOBJ_H_

#include "lemonGL.h"
#include <QTime>
#include <QQueue>

class CIFParticleObj : public CObject {

public:
	CIFParticleObj(int);
	~CIFParticleObj();

	void add(const CMVP*, float, float);
	void drop();
	void gravity();
	QList<QVector4D> getLights();

    void iterate();
	void computeDTT();
	void updateVelocity();
	void updatePosition();
	void order(const QMatrix4x4&);

	void drawSub();

private:
	int m_nbrParticle;
	int m_worldSize;
	int m_activeParticle;

	QVector3D* m_particleList;

	GLfloat* m_textures;
	GLuint* m_indices;
    GLuint* m_indexes;
	GLuint m_fboId;

	CTexture1D m_position;
	CTexture1D m_velocity;
	CTexture1D m_density;

	CTexture3D m_bucket;
	CTexture1D m_physical;

	CProgram m_densityComputation;
	CProgram m_velocityUpdate;
	CProgram m_positionUpdate;
	CProgram m_particleDraw;

	QVector2D* m_textCoords;
	QQueue<QList<QVector3D> > m_pendingParticles;

	int m_gravity;
};

#endif /* CIFPARTICLEOBJ_H_ */
