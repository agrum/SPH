/*
 * CMeshMngr.h
 *
 *  Created on: May 20, 2012
 *      Author: agrum
 */

#ifndef CMESHMNGR_H_
#define CMESHMNGR_H_

#include "../texture/CMaterialMngr.h"
#include "CMesh.h"

#include <QMap>
#include <QString>
#include <QStringList>
#include <QVector3D>
#include <QVector2D>
#include <QFile>

class CMeshMngr {

public:
	static void add(const QString&);
	static void free();

	static CMesh* get(const QString&);

private:
	CMeshMngr(){}

	static QList<CMesh> m_meshes;
};

#endif /* CMeshMngr_H_ */
