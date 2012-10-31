/*
 * CWorld.cpp
 *
 *  Created on: Mar 30, 2012
 *      Author: agrum
 *      Desc: Global class owning everything
 */

#ifndef CWORLD_H_
#define CWORLD_H_

#include <QList>
#include <QMutex>

#include <stdlib.h>
#include "math.h"

#include "../utils/CTagNames.h"
#include "../utils/CMatrix.h"
#include "../utils/CParticle.h"
#include "../utils/CList.h"
#include "../thread/CLinker.h"
#include "../thread/CComputer.h"
#include "../thread/CPopper.h"
#include "../thread/CDocker.h"
#include "../thread/CThread.h"

#include "CPopulation.h"

class CWorld : public CDom {

public:
	//Constructor and dest
	CWorld(CPopulation*);
	~CWorld();

	void initXml(const QDomNode&);

private:
	//World
	CMatrix* m_matrix;
	CList<CParticle>* m_particleList;
	CList<CLink> m_linkList;

	//Threads and routines
	CLinker m_linker;
	CComputer m_computer;
	CPopper m_popper;
	CDocker m_docker;
	QList<CThread*> m_threadList;
};

#endif /* CWORLD_H_ */
