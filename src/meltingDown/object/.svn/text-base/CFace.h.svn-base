/*
 * CFace.h
 *
 *  Created on: May 20, 2012
 *      Author: agrum
 */

#ifndef CFACE_H_
#define CFACE_H_

#include "CVA.h"

#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QVector3D>
#include <QVector2D>

class CFace {

public:
	CFace(const QByteArray&, const QList<QVector3D>&, const QList<QVector2D>&, const QList<QVector3D>&);
	~CFace();

	GLfloat* blehPosition(){ return m_vertices; }
	GLfloat* blehNormal(){ return m_normals; }

	void draw();

private:
	GLfloat* m_vertices;
	GLfloat* m_textures;
	GLfloat* m_normals;

	GLuint* m_indices;
	int* m_count;
	int m_size;
	int m_start;
};

#endif /* CFACE_H_ */
