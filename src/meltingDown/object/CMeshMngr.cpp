/*
 * CMeshMngr.cpp
 *
 *  Created on: May 20, 2012
 *      Author: agrum
 */

#include "CMeshMngr.h"

QList<CMesh> CMeshMngr::m_meshes;

void CMeshMngr::add(const QString& p_filename){
	QFile file(p_filename);
	QByteArray line;
	QList<QByteArray> currentGroups;
	QList<QVector3D> vertices;
	QList<QVector2D> textureCoords;
	QList<QVector3D> normals;

	if(!file.open(QIODevice::ReadOnly)){
		qDebug() << "can't open " + p_filename;
		return;
	}

	while(!file.atEnd()){
		line = file.readLine();
		line.chop(1);
		if(line.left(7) == "mtllib "){ //material libraries
			QStringList libPath = p_filename.split('/');
			libPath.removeLast();
			libPath.push_back(line.split(' ')[1]);
			CMaterialMngr::add(libPath.join("/"));
		}
		else if(line.left(2) == "g "){ //new currentGroup
			currentGroups.clear();
			currentGroups = line.split(' ');
			currentGroups.removeFirst();

			for(int a = 0; a < currentGroups.size(); a++){
				bool exist = false;
				for(int b = 0; b < m_meshes.size(); b++){
					if(m_meshes[b] == currentGroups[a]){
						exist = true;
						break;
					}
				}
				if(!exist){
					CMesh newMesh(currentGroups[a]);
					m_meshes.push_back(newMesh);
				}
			}
		}
		else if(line.left(2) == "v "){ //Vertices
			QList<QByteArray> values = line.split(' ');
			QVector3D tmp(values[1].toDouble(), values[2].toDouble(), values[3].toDouble());
			vertices.push_back(tmp);
		}
		else if(line.left(3) == "vt "){ //Texture coordinates
			QList<QByteArray> values = line.split(' ');
			QVector2D tmp(values[1].toDouble(), values[2].toDouble());
			textureCoords.push_back(tmp);
		}
		else if(line.left(3) == "vn "){ //Normals
			QList<QByteArray> values = line.split(' ');
			QVector3D tmp(values[1].toDouble(), values[2].toDouble(), values[3].toDouble());
			normals.push_back(tmp);
		}
		else if(line.left(7) == "usemtl "){ //use material
			for(int a = 0; a < currentGroups.size(); a++){
				for(int b = 0; b < m_meshes.size(); b++){
					if(m_meshes[b] == currentGroups[a]){
						m_meshes[b].setMaterial(CMaterialMngr::get(line.split(' ')[1]));
					}
				}
			}
		}
		else if(line.left(2) == "f "){ //Face
			CFace* face = new CFace(line, vertices, textureCoords, normals);
			for(int a = 0; a < currentGroups.size(); a++){
				for(int b = 0; b < m_meshes.size(); b++){
					if(m_meshes[b] == currentGroups[a]){
						m_meshes[b].addFace(face);
					}
				}
			}
		}
	}
}

void CMeshMngr::free(){
	for(int a = 0; a < m_meshes.size(); a++)
		m_meshes[a].free();
}

CMesh* CMeshMngr::get(const QString& p_group){
	for(int b = 0; b < m_meshes.size(); b++)
		if(m_meshes[b] == p_group)
			return &(m_meshes[b]);
	return NULL;
}
