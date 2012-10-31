/*
 * CLight.cpp
 *
 *  Created on: Apr 30, 2012
 *      Author: agrum
 */

#include "CLight.h"

GLuint CLight::m_fboId = 0xdeadbeaf;
GLuint CLight::m_lightCount = 0;

CLight::CLight():
m_type(POINT_LIGHT),
m_intensity(1),
m_ambient(0.5, 0.5, 0.5),
m_diffuse(0.3, 0.6, 0.6),
m_specular(0.3, 0.7, 0.7),
m_enabled(true),
m_shadow(false),
m_shadowMap("shadow", 0, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT)
{
	glBindTexture(GL_TEXTURE_2D, m_shadowMap.id());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D, 0);

	m_lightCount++;
	if(m_fboId == 0xdeadbeaf)
		glGenFramebuffers(1, &m_fboId);
}

CLight::~CLight(){
	if(--m_lightCount == 0){
		glDeleteFramebuffers(1, &m_fboId);
		m_fboId = 0xdeadbeaf;
	}
}

void CLight::sendToProgram(const CMVP* p_camera, const QMatrix4x4& p_modelMat) const{
	CProgram* program = CProgram::current();
	QMatrix4x4 camModelMatOfLight;
	QMatrix4x4 camModelViewMatOfLight;
	QVector4D nil(0, 0, 0, 1);
	QVector4D position(m_position.x(), m_position.y(), m_position.z(), 1);
	QVector3D direction;

	camModelMatOfLight.setToIdentity();
	camModelMatOfLight.setColumn(3, position);
	camModelViewMatOfLight = p_camera->viewMatrix() * camModelMatOfLight;
	position = camModelViewMatOfLight * m_position;
	camModelViewMatOfLight.setRow(3, nil);
	camModelViewMatOfLight.setColumn(3, nil);
	direction = (camModelViewMatOfLight * m_direction.toVector4D()).toVector3D();

	program->sendUniform1i("light.type", m_type);
	program->sendUniform4f("light.position", position.x(), position.y(), position.z(), position.w());
	program->sendUniform3f("light.direction", direction.x(), direction.y(), direction.z());
	program->sendUniform1f("light.intensity", m_intensity);
	program->sendUniform3f("light.ambient", m_ambient.x(), m_ambient.y(), m_ambient.z());
	program->sendUniform3f("light.diffuse", m_diffuse.x(), m_diffuse.y(), m_diffuse.z());
	program->sendUniform3f("light.specular", m_specular.x(), m_specular.y(), m_specular.z());

	if(m_shadow){
		m_shadowMap.sendToProgram(m_projMatrix * m_viewMatrix * p_modelMat);
		program->sendUniform1i("light.noShadow", 0);
	}
	else
		program->sendUniform1i("light.noShadow", 1);
}

void CLight::setType(const QString& p_type){
	if(p_type == "point")
		m_type = POINT_LIGHT;
	else if(p_type == "directional")
		m_type = DIRECTIONAL_LIGHT;
}

void CLight::setIntensity(float p_i){
	m_intensity = p_i;
}

void CLight::setAmbient(float p_r, float p_g, float p_b){
	m_ambient.setX(p_r);
	m_ambient.setY(p_g);
	m_ambient.setZ(p_b);
}

void CLight::setDiffuse(float p_r, float p_g, float p_b){
	m_diffuse.setX(p_r);
	m_diffuse.setY(p_g);
	m_diffuse.setZ(p_b);
}

void CLight::setSpecular(float p_r, float p_g, float p_b){
	m_specular.setX(p_r);
	m_specular.setY(p_g);
	m_specular.setZ(p_b);
}

void CLight::setShadowMapSize(GLuint p_x, GLuint p_y){
	m_width = p_x;
	m_height = p_y;
	m_shadowMap.setSize(p_x, p_y);
}

void CLight::setEnableShadow(bool p_e){
	m_shadow = p_e;
}

void CLight::setEnabled(bool p_e){
	m_enabled = p_e;
}

void CLight::bindFB(){
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);
}

void CLight::unbindFB(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CLight::attachTexToFB(){
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowMap.id(), 0);
}

