/*
 * CIFBox.cpp
 *
 *  Created on: Jun 19, 2012
 *      Author: agrum
 */

#include "CIFBox.h"

CIFBox::CIFBox(const CMesh& p_mesh):
CMesh(p_mesh)
{
	for(int a = 0; a < 6; a++)
		m_active.push_back(false);
}

void CIFBox::cull(const QMatrix4x4& p_view){
	QMatrix4x4 modelView = p_view * m_modelMatrix;
	QMatrix3x3 modelViewInverse = modelView.normalMatrix().transposed();
	modelView = modelView.transposed();

	for(int a = 0; a < m_faces.size(); a++){
		QVector4D position(m_faces[a]->blehPosition()[0], m_faces[a]->blehPosition()[1], m_faces[a]->blehPosition()[2], 1);
		QVector3D normal(m_faces[a]->blehNormal()[0], m_faces[a]->blehNormal()[1], m_faces[a]->blehNormal()[2]);
		QVector3D n = (normal.toVector4D() * QMatrix4x4(modelViewInverse)).toVector3D();
		QVector3D r = (position * modelView).toVector3D();
		if(QVector3D::dotProduct(n, r) < 0)
			m_active[a] = true;
		else
			m_active[a] = false;
	}
}

void CIFBox::drawSub(){
	for(int a = 0; a < m_faces.size(); a++)
		if(m_active[a])
			m_faces[a]->draw();
}
