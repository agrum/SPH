/*
 * CLinker.cpp
 *
 *  Created on: Mar 30, 2012
 *      Author: agrum
 */

#include "CLinker.h"

void CLinker::execute(int p_start, int p_inc, int, const QList<void*>&, QList<void*>&){
	unsigned int maxSize = m_particleList->maxSize();
	unsigned int aIndex, bIndex;
	unsigned int worldIndex, sizeBlock, sizeSurroundingBlock;
	CParticle* particleA;
	CParticle* particleB;
	QList<QList<void*>* >* surrounding;
	QList<void*>* block;
	QList<CLink*> tmpLink;

	//Fill the local link list
	for(unsigned int a = p_start; a < maxSize; a += p_inc){
		particleA = m_particleList->at(a);
		if(particleA != NULL && particleA->canLink()){
			worldIndex = m_matrix->index(*particleA);
			block = m_matrix->getBlock(worldIndex);
			surrounding = m_matrix->getSurrounding(worldIndex);
			sizeBlock = block->size();
			sizeSurroundingBlock = surrounding->size();

			//First links the particles in the same block
			for(unsigned int b = 0; b < sizeBlock && particleA->canLink(); b++){
				particleB = (CParticle*) block->at(b);
				if(particleA->id() < particleB->id() && !particleB->isNull() && particleA->canLink(particleB, aIndex, bIndex)){
					tmpLink.push_back(new CLink(particleA, particleB, aIndex, bIndex));
				}
			}

			//Then the surrounding ones
			for(unsigned int c = 0; c < sizeSurroundingBlock && particleA->canLink(); c++){
				block = surrounding->at(c);
				sizeBlock = block->size();

				for(unsigned int b = 0; b < sizeBlock && particleA->canLink(); b++){
					particleB = (CParticle*) block->at(b);
					if(particleA->id() < particleB->id() && !particleB->isNull() && particleA->canLink(particleB, aIndex, bIndex)){
						tmpLink.push_back(new CLink(particleA, particleB, aIndex, bIndex));
					}
				}
			}
		}
	}

	//Append the local link list to the shared one
	if(!tmpLink.empty())
		m_linkList->append(tmpLink);
}
