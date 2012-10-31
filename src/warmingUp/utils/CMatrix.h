/*
 * CMatrix.h
 *
 *  Created on: Mar 29, 2012
 *      Author: agrum
 *      Desc: World discretizer
 */

#ifndef CMATRIX_H_
#define CMATRIX_H_

#include <stdlib.h>
#include <QList>
#include <QDebug>

#include "CTagNames.h"
#include "CParticle.h"

class CMatrix : public CDom {
public:
	//Constructor and dest
	CMatrix();
	~CMatrix();

	//Access
	inline unsigned int size() const { return m_size; }
	inline QList<void*>* getBlock(const unsigned int p){ return m_block[p]; }
	inline QList<QList<void*>* >* getSurrounding(const unsigned int p){ return m_surroundingBlock[p]; }
	inline int index(const QVector3D& p_v) const { return (int) p_v.x() + m_size*((int) p_v.y() + m_size*((int) p_v.z())); }

protected:
	void initXml(const QDomNode&);

private:
	QList<QList<void*>* > m_block;
	QList<QList<QList<void*>* >* > m_surroundingBlock;

	unsigned int m_size; //resolution
	unsigned int m_sizeCu; //total number of blocks
};

#endif /* CMATRIX_H_ */
