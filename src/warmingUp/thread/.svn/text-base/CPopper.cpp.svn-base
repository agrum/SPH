/*
 * CPopper.cpp
 *
 *  Created on: Apr 13, 2012
 *      Author: agrum
 */

#include "CPopper.h"

void CPopper::execute(int p_start, int p_inc, int p_elapsed, const QList<void*>&, QList<void*>& p_list){
	int size = m_matrix->size()*m_matrix->size()*m_matrix->size();
	int limit = m_matrix->size();
	int blockSize;
	int indexBef, indexAft;
	CParticle* particle;
	QList<void*>* block;

	//Apply the computed forces over each particles
	for(int a = p_start; a < size; a += p_inc){
		block = m_matrix->getBlock(a);
		blockSize = block->size();
		for(int b = 0; b < blockSize; b++){
			particle = (CParticle*) block->at(b);
			if(particle != NULL){
				indexBef = m_matrix->index(*particle);
				particle->applyForces(p_elapsed, limit);
				if(particle->alive(&p_list)){
					indexAft = m_matrix->index(*particle);
					//If the indexes are different, removing the particle from the block
					if(indexBef != indexAft){
						m_matrix->getBlock(indexBef)->removeOne(particle);
						p_list.push_back(particle); //Add to m_pendingList for CDocker in next phase
						blockSize--;
					}
				}
				else {
					m_matrix->getBlock(indexBef)->removeOne(particle);
					blockSize--;
				}
			}
		}
	}
}
