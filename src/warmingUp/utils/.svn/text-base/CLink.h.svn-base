/*
 * CLink.h
 *
 *  Created on: Mar 30, 2012
 *      Author: agrum
 *      Desc: Link between two particles
 */

#ifndef CLINK_H_
#define CLINK_H_

#include "CParticle.h"

class CLink {

public:
	//Constructors and dest
	CLink(CParticle*, CParticle*, unsigned int, unsigned int);
	CLink(const CLink&);
	~CLink();
	CLink& operator=(const CLink&);

	//Access to particles id
	inline unsigned int id(bool p) const { return (p) ? m_a->id() : m_b->id(); }

	//Compute forces between the linked particles and return false if not effective anymore
	inline bool interact(){	return m_b->addForce(*m_a); }

	//Needed by CList
	inline bool empty() const { return (m_a == NULL || m_b == NULL);	}
	inline void clear() {
		m_a->unlink(m_aIndex);
		m_b->unlink(m_bIndex);
		m_a = m_b = NULL;
	}

private:
	CParticle* m_a;
	CParticle* m_b;
	unsigned int m_aIndex; //index of the link in m_a array
	unsigned int m_bIndex; //index of the link in m_b array
};

#endif /* CLINK_H_ */
