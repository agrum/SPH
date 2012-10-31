/*
 * CParticle.cpp
 *
 *  Created on: Mar 30, 2012
 *      Author: agrum
 */

#include "CParticle.h"

unsigned int CParticle::m_ite = 0;
qreal CParticle::m_coefV[10000];
qreal CParticle::m_coefD[10000];
qreal CParticle::m_coefP[10000];

//Constructors and dest
CParticle::CParticle(float p_x, float p_y, float p_z, CReference* p_ref) :
QVector3D(p_x, p_y, p_z),
m_d(0),
m_invD(0),
m_invDdotM(0),
m_nextD(0),
m_p(0),
m_integrity(1),
m_pressF(),
m_viscoF(),
m_s(),
m_ref(p_ref),
m_count(0),
m_id(m_ite++)
{

	m_linked = (CParticle**) malloc(sizeof(CParticle*)*MAXLINK);
	for(unsigned int a = 0; a < MAXLINK; a++)
		m_linked[a] = NULL;
}

//Init static values
void CParticle::setStatic() {
	//Muller's weight functions
	for(int a = 0; a < 10000; a++){
		float length = sqrt(a)*0.01;

		m_coefV[a] = 45.0/(M_PI)*(1.0 - length);
		m_coefD[a] = 315.0/(64.0*M_PI)*pow((1.0 - pow(length, 2)), 3);
		m_coefP[a] = -45.0/(M_PI*length+0.4)*pow(1.0 - length, 3);
	}
}

//Check links possibilities
bool CParticle::canLink(CParticle* p_p, unsigned int& p_aIndex, unsigned int& p_bIndex){
	int openA = -1;
	int openB = -1;

	//Links available ?
	if(m_count == MAXLINK || p_p->m_count == MAXLINK || this == p_p)
		return false;

	//Find free links id in both particles
	for(unsigned int a = 0; a < MAXLINK && (openA == -1 || openB == -1); a++){
		if(m_linked[a] == p_p || p_p->m_linked[a] == this)
			return false;
		else if(openA == -1 && m_linked[a] == NULL)
			openA = a;
		if(openB == -1 && p_p->m_linked[a] == NULL)
			openB = a;
	}

	//Return links id if the particles are not to far apart
	if(openB != -1 && openA != -1){
		QVector3D link(*this - *p_p);

		if(link.lengthSquared() > 1.0)
			return false;

		p_aIndex = (unsigned int) openA;
		p_bIndex = (unsigned int) openB;
		return true;
	}
	return false;
}

//Apply all the forces and move the particle
void CParticle::applyForces(unsigned int p_time, int p_limit){
	//density
	m_d = m_nextD + 1.0;
	m_nextD = 0;
	m_invD = 1.0/m_d;
	m_invDdotM = m_ref->m()*m_invD;
	//pressure
	m_p = ATMP + m_d*0.5;
	//gravity
	QVector3D graviF(0.0, 0.0, -0.22*(m_ref->m() - 0.2));
	//speed
	m_s = m_s/**m_ref->frict()*/ + (m_pressF/* + m_viscoF + graviF*/)*0.001;
	//bounding box
	boundingBox(p_time, p_limit);
	//position
	*this += m_s*1.4*25.0;
}

//Interaction with the bounding box
void CParticle::boundingBox(unsigned int p_time, int p_limit){
	//reinit
	m_pressF *= 0;
	m_viscoF *= 0;

	//update pressure and density forces relative to bounding box
	float bleh = 1.0;
	float blah = 0.01;
	if(x() < 1.0){
		m_pressF.setX(m_pressF.x() + (1.0 - x())*bleh);
		m_nextD += (1.0 - x())*blah;
	}
	else if(x() > p_limit - 1.0){
		m_pressF.setX(m_pressF.x() - (1.0 - p_limit + x())*bleh);
		m_nextD += (1.0 - p_limit + x())*blah;
	}
	if(y() < 1.0){
		m_pressF.setY(m_pressF.y() + (1.0 - y())*bleh);
		m_nextD += (1.0 - y())*blah;
	}
	else if(y() > p_limit - 1.0){
		m_pressF.setY(m_pressF.y() - (1.0 - p_limit + y())*bleh);
		m_nextD += (1.0 - p_limit + y())*blah;
	}
	if(z() < 1.0){
		m_pressF.setZ(m_pressF.z() + (1.0 - z())*bleh);
		m_nextD += (1.0 - y())*blah;
	}
	else if(z() > p_limit - 1.0){
		m_pressF.setZ(m_pressF.z() - (1.0 - p_limit + z())*bleh);
		m_nextD += (1.0 - p_limit + z())*blah;
	}
	//update speed relative to bounding box
	QVector3D tmp(*this + m_s*1.4*25.0);
	if(tmp.x() < 0 || tmp.x() >= p_limit){	m_s.setX(m_s.x()*-1.0); m_s *= 0.8; }
	if(tmp.y() < 0 || tmp.y() >= p_limit){	m_s.setY(m_s.y()*-1.0); m_s *= 0.8; }
	if(tmp.z() < 0 || tmp.z() >= p_limit){	m_s.setZ(m_s.z()*-1.0); m_s *= 0.8; }
}
