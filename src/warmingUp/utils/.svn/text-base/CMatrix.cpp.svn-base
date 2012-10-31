/*
 * CMatrix.cpp
 *
 *  Created on: Mar 29, 2012
 *      Author: agrum
 */

#include "CMatrix.h"

CMatrix::CMatrix() :
m_size(0),
m_sizeCu(0)
{

}

CMatrix::~CMatrix(){
	for(unsigned int a = 0; a < m_sizeCu; a++){
		delete m_block.takeFirst();
	}
}

void CMatrix::initXml(const QDomNode& p_node){
	for (QDomNode n = p_node.firstChild(); !n.isNull(); n = n.nextSibling()){
		if (n.isElement()){
			QDomElement e = n.toElement();
			if (e.tagName() == T_MATRIX_SIZE)
				m_size = e.text().toInt();
		}
	}

	m_sizeCu = m_size*m_size*m_size;
	for(unsigned int a = 0; a < m_sizeCu; a++){
		m_block.push_back(new QList<void*>);
		m_surroundingBlock.push_back(new QList<QList<void*>* >);
	}

	int size = (int) m_size;
	for(int x = 0; x < size; x++){
		for(int y = 0; y < size; y++){
			for(int z = 0; z < size; z++){
				int index = x + size*(y + size*z);
				for(int indX = 0; indX <= 1; indX++){
					for(int indY = 0; indY <= 1; indY++){
						for(int indZ = -1; indZ <= 1; indZ++){
							if((indX != 0 || indY != 0 || indZ != 0)
									&& indX + x < size && indY + y < size && indZ + z < size
									&& indX + x >= 0 && indY + y >= 0 && indZ + z >= 0 ){
								m_surroundingBlock[index]->push_back(m_block[index + indX + size*(indY + size*indZ)]);
							}
						}
					}
				}
			}
		}
	}
}
