/*
 * CTexture.cpp
 *
 *  Created on: May 7, 2012
 *      Author: agrum
 */

#include "CTexture.h"

CTexture::CTexture(QString p_prefix, GLuint p_channel, GLenum p_intFormat, GLenum p_format, GLenum p_type):
m_prefix(p_prefix),
m_channel(p_channel),
m_internalFormat(p_intFormat),
m_format(p_format),
m_type(p_type),
m_data(0)
{
	glGenTextures(1, &m_id);
}

CTexture::~CTexture(){
	glDeleteTextures(1, &m_id);
}

void CTexture::setData(void* p_data){
	m_data = p_data;
	setTex();
}

CTexture1D::CTexture1D(QString p_prefix, GLuint p_channel, GLenum p_intFormat, GLenum p_format, GLenum p_type):
CTexture(p_prefix, p_channel, p_intFormat, p_format, p_type),
m_width(512)
{
	glBindTexture(GL_TEXTURE_1D, m_id);
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_1D, 0);
}

CTexture2D::CTexture2D(QString p_prefix, GLuint p_channel, GLenum p_intFormat, GLenum p_format, GLenum p_type):
CTexture(p_prefix, p_channel, p_intFormat, p_format, p_type),
m_width(512),
m_height(512)
{
	glBindTexture(GL_TEXTURE_2D, m_id);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}

CTexture3D::CTexture3D(QString p_prefix, GLuint p_channel, GLenum p_intFormat, GLenum p_format, GLenum p_type):
CTexture(p_prefix, p_channel, p_intFormat, p_format, p_type),
m_width(512),
m_height(512),
m_depth(512)
{
	glBindTexture(GL_TEXTURE_3D, m_id);
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_3D, 0);
}

void CTexture1D::setTex(){
	glBindTexture(GL_TEXTURE_1D, m_id);
	glTexImage1D(GL_TEXTURE_1D, 0, m_internalFormat, m_width, 0, m_format, m_type, m_data);
	glBindTexture(GL_TEXTURE_1D, 0);
}

void CTexture2D::setTex(){
	glBindTexture(GL_TEXTURE_2D, m_id);
	glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_format, m_type, m_data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CTexture3D::setTex(){
	glBindTexture(GL_TEXTURE_3D, m_id);
	glTexImage3D(GL_TEXTURE_3D, 0, m_internalFormat, m_width, m_height, m_depth, 0, m_format, m_type, m_data);
	glBindTexture(GL_TEXTURE_3D, 0);
}

void CTexture1D::setWidth(int p_w){
	m_width = p_w;
	setTex();
}

void CTexture2D::setWidth(int p_w){
	m_width = p_w;
	setTex();
}

void CTexture3D::setWidth(int p_w){
	m_width = p_w;
	setTex();
}

void CTexture2D::setHeight(int p_h){
	m_height = p_h;
	setTex();
}

void CTexture3D::setHeight(int p_h){
	m_height = p_h;
	setTex();
}

void CTexture3D::setDepth(int p_d){
	m_depth = p_d;
	setTex();
}

void CTexture1D::sendToProgram() const {
	CProgram* program = CProgram::current();

	program->sendUniform1i(m_prefix + "TexMap", m_channel);

	glActiveTexture(GL_TEXTURE0 + m_channel);
	glBindTexture(GL_TEXTURE_1D, m_id);
}

void CTexture2D::sendToProgram() const {
	CProgram* program = CProgram::current();

	program->sendUniform1i(m_prefix + "TexMap", m_channel);

	glActiveTexture(GL_TEXTURE0 + m_channel);
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void CTexture3D::sendToProgram() const {
	CProgram* program = CProgram::current();

	program->sendUniform1i(m_prefix + "TexMap", m_channel);

	glActiveTexture(GL_TEXTURE0 + m_channel);
	glBindTexture(GL_TEXTURE_3D, m_id);
}

void CTexture2D::sendToProgram(const QMatrix4x4& p_mvp) const {
	CProgram* program = CProgram::current();
	float tex[16];
	QMatrix4x4 tmp(
			0.5, 0.0, 0.0, 0.5,
			0.0, 0.5, 0.0, 0.5,
			0.0, 0.0, 0.5, 0.5,
			0.0, 0.0, 0.0, 1.0);
	tmp = tmp * p_mvp;
	for(int a = 0; a < 4; a++)
		for(int b = 0; b < 4; b++)
			tex[a*4 + b] = tmp(a, b);

	program->sendUniformMatrix4fv(m_prefix + "TexMat", 1, GL_TRUE, tex);
	program->sendUniform1i(m_prefix + "TexMap", m_channel);

	glActiveTexture(GL_TEXTURE0 + m_channel);
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void CTexture2D::appendImg(const QString& p_filename){
	QImage img;

	if( ! img.load(p_filename) ) qDebug() << "error loading texture " + p_filename ;

	m_image = QGLWidget::convertToGLFormat(img);
	if( m_image.isNull() ) qDebug() << "error GL_formatted_image" ;

	m_width = m_image.width();
	m_height = m_image.height();
	m_internalFormat = GL_RGBA;
	m_format = GL_RGBA;
	m_type = GL_UNSIGNED_BYTE;
	m_data = m_image.bits();
	setTex();
}

void CTexture2D::setSize(GLuint p_width, GLuint p_height){
	if(p_width != m_width || p_height != m_height){
		m_width = p_width;
		m_height = p_height;
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_height, m_width, 0, m_format, m_type, m_data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
