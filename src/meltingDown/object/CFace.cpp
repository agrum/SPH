/*
 * CFace.cpp
 *
 *  Created on: May 20, 2012
 *      Author: agrum
 */

#include "CFace.h"

CFace::CFace(const QByteArray& p_line, const QList<QVector3D>& p_v, const QList<QVector2D>& p_t, const QList<QVector3D>& p_n){
	QList<QByteArray> indices = p_line.split(' ');
	indices.removeFirst();

	m_count = new int(1);
	m_size = indices.size();
	m_start = CVA::add(m_size + 1);
	if(m_start != -1){
		m_vertices = CVA::vertices() + 3*m_start;
		m_textures = CVA::textures() + 2*m_start;
		m_normals = CVA::normals() + 3*m_start;

		m_indices = new GLuint[m_size + 1];
		for(int a = 0; a < m_size; a++){
			QList<QByteArray> subIndices = indices[a].split('/');
			m_vertices[3*a+0] = p_v[subIndices[0].toUInt() - 1].x();
			m_vertices[3*a+1] = p_v[subIndices[0].toUInt() - 1].y();
			m_vertices[3*a+2] = p_v[subIndices[0].toUInt() - 1].z();
			m_textures[2*a+0] = p_t[subIndices[1].toUInt() - 1].x();
			m_textures[2*a+1] = p_t[subIndices[1].toUInt() - 1].y();
			m_normals[3*a+0] = p_n[subIndices[2].toUInt() - 1].x();
			m_normals[3*a+1] = p_n[subIndices[2].toUInt() - 1].y();
			m_normals[3*a+2] = p_n[subIndices[2].toUInt() - 1].z();
			m_indices[a] = a + m_start;
		}
	}
}

CFace::~CFace(){
	*m_count = *m_count - 1;

	if(*m_count == 0){
		CVA::del(m_start, m_size);
		delete m_indices;
	}
}

void CFace::draw(){
	glDrawElements(GL_TRIANGLE_FAN, m_size, GL_UNSIGNED_INT, m_indices);
}
