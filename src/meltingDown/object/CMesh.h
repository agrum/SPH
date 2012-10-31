/*
 * CMesh.h
 *
 *  Created on: May 23, 2012
 *      Author: agrum
 */

#ifndef CMESH_H_
#define CMESH_H_

#include "CObject.h"
#include "CFace.h"

class CMesh : public CObject {

public:
	CMesh(const QString&);
	CMesh(const CMesh&);

	void addFace(CFace*);
	void free();
	bool operator==(const QString&);

	virtual void drawSub();

protected:
	QString m_group;
	QList<CFace*> m_faces;
	QList<int> m_order;
};

#endif /* CMESH_H_ */
