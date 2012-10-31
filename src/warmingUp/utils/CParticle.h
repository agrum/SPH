/*
 * CParticle.h
 *
 *  Created on: Mar 30, 2012
 *      Author: agrum
 *      Desc: CVertex extend to implement physical behavior
 */

#ifndef CPARTICLE_H_
#define CPARTICLE_H_

#define ATMP 0.9 //Atmospheric pressure
#define MAXLINK 25 //Maximum link number between particles

#include <QVector3D>
#include <QString>
#include <QDebug>
#include <iostream>
#include <math.h>
#include "stdlib.h"

#include "CReference.h"

class CParticle : public QVector3D {

public:
	//Constructors and dest
	CParticle(float, float, float, CReference*);

	//Init coefs
	static void setStatic();

	//Link methods
	bool canLink(CParticle*, unsigned int&, unsigned int&);
	inline bool canLink(){ return (m_count < MAXLINK); }
	inline bool link(CParticle* p_p, unsigned int p_index) { m_linked[p_index] = p_p; return (++m_count == MAXLINK); }
	inline bool unlink(unsigned int p_index) { m_linked[p_index] = NULL; return (m_count-- == MAXLINK); }

	//Physics related methods
	inline bool alive(QList<void*>*);
	inline bool addForce(CParticle&);
	void applyForces(unsigned int, int);
	void boundingBox(unsigned int, int);

	//Access
	inline unsigned int id() const { return m_id; }
	inline CReference* ref() { return m_ref; }

protected:
	//Physics related attributes
	float m_d, m_invD, m_invDdotM, m_nextD; //density, inverse, inverseDotMass and temporary
	float m_p; //pressure
	float m_integrity;
	QVector3D m_pressF, m_viscoF; //pressure and viscosity forces
	QVector3D m_s; //speed
	CReference* m_ref;

	//Link related attribute
	CParticle** m_linked; //List of links
	unsigned int m_count; //Number of effective links

	//Id relative attributes
	unsigned int m_id; //particle's id
	static unsigned int m_ite; //static id iterator	//Bleh stuff

	//Mullers's coeficients
	static qreal m_coefV[10000]; //viscosity coefs
	static qreal m_coefD[10000]; //density coefs
	static qreal m_coefP[10000]; //pressure coefs
};

//----Definition

//Compute instant forces between two particles
bool CParticle::addForce(CParticle& p_p) {
	QVector3D link(p_p - *this);
	QVector3D p, v;
	int freezed;
	float d;

	freezed = (link*100.0).lengthSquared();

	if(freezed < 10000){
		//density update
		d = m_coefD[freezed];
		m_nextD += d*p_p.m_ref->m();
		p_p.m_nextD += d*m_ref->m();
		//pressure update
		p = link*((m_p + p_p.m_p)*m_coefP[freezed]*0.5);
		m_pressF += p*p_p.m_invD;
		p_p.m_pressF -= p*m_invD;
		//viscosity update
		v = (p_p.m_s - m_s)*(m_coefV[freezed]*m_ref->visc());
		m_viscoF += v*p_p.m_invDdotM;
		p_p.m_viscoF -= v*m_invDdotM;

		return true;
	}

	return false;
}

bool CParticle::alive(QList<void*>* p_list){
	m_ref->chronos(this, p_list);
	return (m_integrity > 0);
}

#endif /* CPARTICLE_H_ */
