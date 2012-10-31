/*
 * CMaterial.cpp
 *
 *  Created on: May 28, 2012
 *      Author: agrum
 */

#include "CMaterial.h"

CMaterial::CMaterial(const QString& p_group):
m_group(p_group),
m_diffuse(0,0,0),
m_ambient(0,0,0),
m_specular(0,0,0),
m_diffuseMap(NULL),
m_ambientMap(NULL),
m_specularMap(NULL)
{

}

CMaterial::CMaterial(const CMaterial& p_mat):
m_group(p_mat.m_group),
m_diffuse(0,0,0),
m_ambient(0,0,0),
m_specular(0,0,0),
m_diffuseMap(NULL),
m_ambientMap(NULL),
m_specularMap(NULL)
{

}

CMaterial::~CMaterial(){
	if(m_diffuseMap != NULL)
		delete m_diffuseMap;
	if(m_ambientMap != NULL)
		delete m_ambientMap;
	if(m_specularMap != NULL)
		delete m_specularMap;
}

void CMaterial::sendToProgram() const {
	CProgram* program = CProgram::current();

	if(m_diffuseMap == NULL){
		program->sendUniform3f("diffuse", m_diffuse.x(), m_diffuse.y(), m_diffuse.z());
		program->sendUniform1i("isDiffuseMap", 0);
	}
	else{
		m_diffuseMap->sendToProgram();
		program->sendUniform1i("isDiffuseMap", 1);
	}
	if(m_ambientMap == NULL){
		program->sendUniform3f("ambient", m_ambient.x(), m_ambient.y(), m_ambient.z());
		program->sendUniform1i("isAmbientMap", 0);
	}
	else{
		m_ambientMap->sendToProgram();
		program->sendUniform1i("isAmbientMap", 1);
	}
	if(m_specularMap == NULL){
		program->sendUniform3f("specular", m_specular.x(), m_specular.y(), m_specular.z());
		program->sendUniform1i("isSpecularMap", 0);
	}
	else{
		m_specularMap->sendToProgram();
		program->sendUniform1i("isSpecularMap", 1);
	}
}

const QString& CMaterial::getGroup(){
	return m_group;
}

void CMaterial::setDiffuse(const QVector3D& p_v){
	m_diffuse = p_v;
}

void CMaterial::setAmbient(const QVector3D& p_v){
	m_ambient = p_v;
}

void CMaterial::setSpecular(const QVector3D& p_v){
	m_specular = p_v;
}

void CMaterial::setDiffuseMap(const QString& p_filename){
	m_diffuseMap = new CTexture2D("diffuse", 1, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
	glBindTexture(GL_TEXTURE_2D, m_diffuseMap->id());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D, 0);
	m_diffuseMap->appendImg(p_filename);
}

void CMaterial::setAmbientMap(const QString& p_filename){
	m_ambientMap = new CTexture2D("ambient", 2, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
	glBindTexture(GL_TEXTURE_2D, m_ambientMap->id());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D, 0);
	m_ambientMap->appendImg(p_filename);
}

void CMaterial::setSpecularMap(const QString& p_filename){
	m_specularMap = new CTexture2D("specular", 3, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
	glBindTexture(GL_TEXTURE_2D, m_specularMap->id());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D, 0);
	m_specularMap->appendImg(p_filename);
}
