/*
 * CObject.h
 *
 *  Created on: May 9, 2012
 *      Author: agrum
 */

#ifndef COBJECT_H_
#define COBJECT_H_

#include "../shader/CProgram.h"
#include "../mvp/CMVP.h"
#include "../mvp/CLight.h"
#include "../texture/CMaterial.h"
#include "../texture/CMaterialMngr.h"

class CObject {

public:
	CObject();
	CObject(const CObject&);

	void draw(const CMVP* camera, QList<CLight*>* lights = NULL, QVector2D biasVP = QVector2D(0,0));
	virtual void drawSub() = 0;
	virtual void order(const QMatrix4x4&) {}

	void setMaterial(const CMaterial*);

	void translucent(bool p_b) { m_translucent = p_b; }
	bool isTranslucent() { return m_translucent; }
	void pushMatrix();
	void popMatrix();
	void loadIdentity();
	void translate(GLfloat x, GLfloat y, GLfloat z);
	void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	void scale(GLfloat x, GLfloat y, GLfloat z);

protected:
	const CMaterial* m_mat;
	QMatrix4x4 m_modelMatrix;
	QLinkedList<QMatrix4x4> m_matrixStack;
	bool m_translucent;
    void convertMatrix(const QMatrix4x4 p_in, float* p_out);
    void convertMatrix(const QMatrix3x3 p_in, float* p_out);
};

void convertMatrix(const QMatrix4x4, float*);
void convertMatrix(const QMatrix3x3, float*);

#endif /* COBJECT_H_ */
