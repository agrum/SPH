/*
 * CTexture.h
 *
 *  Created on: May 7, 2012
 *      Author: agrum
 */

#ifndef CTEXTURE_H_
#define CTEXTURE_H_

#include "../CGL.h"
#include "../shader/CProgram.h"

#include <limits>
#include <cmath>
#include <QString>
#include <QMatrix4x4>

class CTexture {

public:
	CTexture(QString, GLuint, GLenum, GLenum, GLenum);
	~CTexture();

	void setData(void*);
	GLuint id() { return m_id; }
	virtual void sendToProgram() const = 0;
protected:
	virtual void setTex() = 0;

protected:
	QString m_prefix;
	GLuint m_channel;
	GLuint m_id;
	GLenum m_internalFormat;
	GLenum m_format;
	GLenum m_type;
    void* m_data;
};

class CTexture1D : public CTexture {

public:
	CTexture1D(QString, GLuint, GLenum, GLenum, GLenum);

	void setWidth(int);
	void sendToProgram() const ;

private:
	void setTex();

private:
	GLuint m_width;
};

class CTexture2D : public CTexture {

public:
	CTexture2D(QString, GLuint, GLenum, GLenum, GLenum);

	void setWidth(int);
	void setHeight(int);
	void sendToProgram() const ;
	void sendToProgram(const QMatrix4x4&) const ;

	void appendImg(const QString&);
	void setSize(GLuint, GLuint);

private:
	void setTex();

private:
	GLuint m_width, m_height;
	QImage m_image;

};

class CTexture3D : public CTexture {

public:
	CTexture3D(QString, GLuint, GLenum, GLenum, GLenum);

	void setWidth(int);
	void setHeight(int);
	void setDepth(int);
	void sendToProgram() const ;

private:
	void setTex();

private:
	GLuint m_width, m_height, m_depth;

};

#endif /* CTEXTURE_H_ */
