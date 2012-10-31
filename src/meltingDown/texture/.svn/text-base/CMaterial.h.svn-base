/*
 * CMaterial.h
 *
 *  Created on: May 28, 2012
 *      Author: agrum
 */

#ifndef CMATERIAL_H_
#define CMATERIAL_H_

#include "CTexture.h"

#include <QVector3D>

class CMaterial {

public:
	CMaterial(const QString&);
	CMaterial(const CMaterial&);
	~CMaterial();

	void sendToProgram() const;

	const QString& getGroup();

	void setDiffuse(const QVector3D&);
	void setAmbient(const QVector3D&);
	void setSpecular(const QVector3D&);
	void setDiffuseMap(const QString&);
	void setAmbientMap(const QString&);
	void setSpecularMap(const QString&);

private:
	QString m_group;
	QVector3D m_diffuse;
	QVector3D m_ambient;
	QVector3D m_specular;
	CTexture2D* m_diffuseMap;
	CTexture2D* m_ambientMap;
	CTexture2D* m_specularMap;
};

#endif /* CMATERIAL_H_ */
