/*
 * CComputer.cpp
 *
 *  Created on: Apr 2, 2012
 *      Author: agrum
 */

#include "CComputer.h"

void CComputer::execute(int p_start, int p_inc, int, const QList<void*>&, QList<void*>&){
	unsigned int size = m_linkList->maxSize();
	QList<unsigned int> toRemove;

	//Fill the local broke link list
	for(unsigned int a = p_start; a < size; a += p_inc){
		if(m_linkList->at(a) != NULL && !m_linkList->at(a)->interact())
			toRemove.push_back(a);
	}

	//Remove the local link list from the shared one
	if(!toRemove.empty())
		m_linkList->remove(toRemove);
}
