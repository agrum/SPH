/*
 * CDocker.cpp
 *
 *  Created on: Apr 13, 2012
 *      Author: agrum
 */

#include "CDocker.h"

void CDocker::execute(int p_start, int p_inc, int, const QList<void*>& p_currentList, QList<void*>&){
	unsigned int size = p_currentList.size();
	CParticle* particle;

	//Pushes homeless particle in there new blocks
	for(unsigned int a = p_start; a < size; a += p_inc){
		particle = (CParticle*) p_currentList[a];
		if(particle != NULL){
			m_matrix->getBlock(m_matrix->index(*particle))->push_back(particle);
		}
	}
}
