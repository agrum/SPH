/*
 * CIFBox.h
 *
 *  Created on: Jun 19, 2012
 *      Author: agrum
 */

#ifndef CIFBOX_H_
#define CIFBOX_H_

#include "../../meltingDown/CMeltingDown.h"

class CIFBox : public CMesh {

public:
	CIFBox(const CMesh&);

	void cull(const QMatrix4x4&);
	void drawSub();

private:
	//CMaterial m_material;

	QList<bool> m_active;
	GLuint* m_indices;
};

#endif /* CIFBOX_H_ */
