/*
 * CMesh.cpp
 *
 *  Created on: May 23, 2012
 *      Author: agrum
 */

#include "CMesh.h"

CMesh::CMesh(const QString& p_group):
m_group(p_group)
{

}

CMesh::CMesh(const CMesh& p_mesh):
CObject(p_mesh),
m_group(p_mesh.m_group),
m_faces(p_mesh.m_faces)
{

}

void CMesh::addFace(CFace* p_face){
	m_faces.push_back(p_face);
	m_order.push_back(m_order.size());
}

void CMesh::free(){
	for(int a = 0; a < m_faces.size(); a++)
		delete m_faces[a];
}

bool CMesh::operator==(const QString& p_group){
	return (m_group == p_group);
}

void CMesh::drawSub(){
	for(int a = 0; a < m_faces.size(); a++)
		m_faces[a]->draw();
}
