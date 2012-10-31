/*
 * CMaterialMngr.cpp
 *
 *  Created on: May 28, 2012
 *      Author: agrum
 */

#include "CMaterialMngr.h"

QList<CMaterial> CMaterialMngr::m_materials;

void CMaterialMngr::add(const QString& p_filename){
	QFile file(p_filename);
	QByteArray line;

	if(!file.open(QIODevice::ReadOnly))
		return;

	while(!file.atEnd()){
		line = file.readLine();
		line.chop(1);
		if(line.left(7) == "newmtl "){ //new currentGroup
			CMaterial newMaterial(line.split(' ')[1]);
			m_materials.push_back(newMaterial);
		}
		else if(line.left(3) == "Kd "){
			QList<QByteArray> values = line.split(' ');
			m_materials.last().setDiffuse(QVector3D(values[1].toDouble(), values[2].toDouble(), values[3].toDouble()));
		}
		else if(line.left(3) == "Ka "){
			QList<QByteArray> values = line.split(' ');
			m_materials.last().setAmbient(QVector3D(values[1].toDouble(), values[2].toDouble(), values[3].toDouble()));
		}
		else if(line.left(3) == "Ks "){
			QList<QByteArray> values = line.split(' ');
			m_materials.last().setSpecular(QVector3D(values[1].toDouble(), values[2].toDouble(), values[3].toDouble()));
		}
		else if(line.left(7) == "map_Kd "){
			QStringList imgPath = p_filename.split('/');
			imgPath.removeLast();
			imgPath.push_back("img");
			imgPath.push_back(line.split(' ')[1]);
			m_materials.last().setDiffuseMap(imgPath.join("/"));
		}
		else if(line.left(7) == "map_Ka "){
			QStringList imgPath = p_filename.split('/');
			imgPath.removeLast();
			imgPath.push_back("img");
			imgPath.push_back(line.split(' ')[1]);
			m_materials.last().setAmbientMap(imgPath.join("/"));
		}
		else if(line.left(7) == "map_Ks "){
			QStringList imgPath = p_filename.split('/');
			imgPath.removeLast();
			imgPath.push_back("img");
			imgPath.push_back(line.split(' ')[1]);
			m_materials.last().setSpecularMap(imgPath.join("/"));
		}
	}
}

const CMaterial* CMaterialMngr::get(const QString& p_group){
	for(int a = 0; a < m_materials.size(); a++)
		if(m_materials[a].getGroup() == p_group)
			return &(m_materials[a]);
	return NULL;
}
