/*
 * CPopulation.h
 *
 *  Created on: Apr 23, 2012
 *      Author: agrum
 */

#ifndef CPOPULATION_H_
#define CPOPULATION_H_

#include "../utils/CTagNames.h"
#include "../utils/CList.h"
#include "../utils/CParticle.h"

class CPopulation : public CDom {

public:
	CPopulation() : m_particleList(NULL) {}

	CList<CParticle>* list() { return m_particleList; }
	CMatrix* matrix() { return &m_matrix; }

protected:
	CList<CParticle>* m_particleList;
	CMatrix m_matrix;
};

#endif /* CPOPULATION_H_ */
