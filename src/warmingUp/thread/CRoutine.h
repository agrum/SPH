/*
 * CRoutine.h
 *
 *  Created on: Apr 23, 2012
 *      Author: agrum
 */

#ifndef CROUTINE_H_
#define CROUTINE_H_

#include <QList>
#include <QString>

#include "../utils/CMatrix.h"
#include "../utils/CList.h"
#include "../utils/CLink.h"
#include "../utils/CParticle.h"

class CRoutine {

public:
	//Constructor null (to avoid default ones)
	CRoutine() {}

	//Init statics
	static void setStatic(CMatrix* p_matrix, CList<CLink>* p_linkList, CList<CParticle>* p_particleList){
		m_matrix = p_matrix;
		m_linkList = p_linkList;
		m_particleList = p_particleList;
	}

	//Routine
	virtual void execute(int start, int inc, int elapsed, const QList<void*>& current, QList<void*>& pending) = 0;

protected:
	static CMatrix* m_matrix;
	static CList<CLink>* m_linkList;
	static CList<CParticle>* m_particleList;
};

#endif /* CROUTINE_H_ */
