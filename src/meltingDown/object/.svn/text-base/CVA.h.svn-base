/*
 * CVA.h
 *
 *  Created on: May 1, 2012
 *      Author: agrum
 */

#ifndef CVA_H_
#define CVA_H_

#include "../CGL.h"
#include "CFace.h"

#include <stdio.h>
#include <cmath>
#include <QDebug>
#include <QList>
#include <QPair>

class CVA {

public:
	static void create(int);
	static void remove();

	static GLfloat* vertices() { return m_vertices; }
	static GLfloat* textures() { return m_textures; }
	static GLfloat* normals() { return m_normals; }

	static int add(int);
	static void del(int, int);

	static void enable();
	static void disable();

protected:
	CVA() {}

	static QList<QPair<int, int> > m_free;
	static GLfloat* m_vertices;
	static GLfloat* m_textures;
	static GLfloat* m_normals;
};

#endif /* CVA_H_ */
