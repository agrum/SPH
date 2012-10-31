/*
 * CWorld.cpp
 *
 *  Created on: Mar 30, 2012
 *      Author: agrum
 */

#include "CWorld.h"

CWorld::CWorld(CPopulation* p_pop) :
m_matrix(p_pop->matrix()),
m_particleList(p_pop->list()),
m_linkList(m_particleList->maxSize()*MAXLINK)
{

}

CWorld::~CWorld(){
	while(!m_threadList.empty())
		delete m_threadList.takeFirst();
}

void CWorld::initXml(const QDomNode& p_node){
	QList<CParticle*> tmpList;
	QList<int> maxToken;
	int nbr_linker = 1;
	int nbr_computer = 1;
	int nbr_popper = 1;
	int nbr_docker = 1;
	int subphase_linker = 1;
	int subphase_computer = 1;
	int subphase_popper = 1;
	int subphase_docker = 1;
	int loopTime = 50;

	//Read dom
	for (QDomNode n = p_node.firstChild(); !n.isNull(); n = n.nextSibling()){
		if (n.isElement()){
			QDomElement e = n.toElement();
			//Matrix
			if (e.tagName() == T_WORLD_MATRIX)
				m_matrix->init(n);
			//Nbr threads
			if (e.tagName() == T_WORLD_NBR_LINKER && e.text().toInt() > nbr_linker)
				nbr_linker = e.text().toInt();
			else if (e.tagName() == T_WORLD_NBR_COMPUTER && e.text().toInt() > nbr_computer)
				nbr_computer = e.text().toInt();
			else if (e.tagName() == T_WORLD_NBR_POPPER && e.text().toInt() > nbr_popper)
				nbr_popper = e.text().toInt();
			else if (e.tagName() == T_WORLD_NBR_DOCKER && e.text().toInt() > nbr_docker)
				nbr_docker = e.text().toInt();
			//Nbr subphases
			else if (e.tagName() == T_WORLD_SUBPHASE_LINKER && e.text().toInt() > subphase_linker)
				subphase_linker = e.text().toInt();
			else if (e.tagName() == T_WORLD_SUBPHASE_COMPUTER && e.text().toInt() > subphase_computer)
				subphase_computer = e.text().toInt();
			else if (e.tagName() == T_WORLD_SUBPHASE_POPPER && e.text().toInt() > subphase_popper)
				subphase_popper = e.text().toInt();
			else if (e.tagName() == T_WORLD_SUBPHASE_DOCKER && e.text().toInt() > subphase_docker)
				subphase_docker = e.text().toInt();
			//Minimum time between each iteration
			else if (e.tagName() == T_WORLD_LOOP_TIME && e.text().toInt() >= 0)
				loopTime = e.text().toInt();
		}
	}

	//Ajust particles position
	for(unsigned int a = 0; a < m_particleList->maxSize(); a++)
		if(m_particleList->at(a) != NULL)
			*(m_particleList->at(a)) *= m_matrix->size();

	//Tokens
	maxToken.push_back(nbr_linker + nbr_computer);
	maxToken.push_back(nbr_popper);
	maxToken.push_back(nbr_docker);

	//Init classes statics
	CRoutine::setStatic(m_matrix, &m_linkList, m_particleList);
	CParticle::setStatic();
	CThread::setStatic(maxToken, loopTime);

	//Fill matrix
	for(unsigned int a = 0; a < m_particleList->maxSize(); a++)
		if(m_particleList->at(a) != NULL)
			m_matrix->getBlock(m_matrix->index(*(m_particleList->at(a))))->push_back(m_particleList->at(a));

	//Create threads
	for(int a = 0; a < nbr_linker; a++)
		m_threadList.push_back(new CThread(a, nbr_linker, subphase_linker, 0, &m_linker, QString("CLin%1 | ").arg(a)));
	for(int a = 0; a < nbr_computer; a++)
		m_threadList.push_back(new CThread(a, nbr_computer, subphase_computer, 0, &m_computer, QString("CCom%1 | ").arg(a)));
	for(int a = 0; a < nbr_popper; a++)
		m_threadList.push_back(new CThread(a, nbr_popper, subphase_popper, 1, &m_popper, QString("CPop%1 | ").arg(a)));
	for(int a = 0; a < nbr_docker; a++)
		m_threadList.push_back(new CThread(a, nbr_docker, subphase_docker, 2, &m_docker, QString("CDoc%1 | ").arg(a)));
}
