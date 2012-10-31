/*
 * CProgram.cpp
 *
 *  Created on: Apr 28, 2012
 *      Author: agrum
 */

#include "CProgram.h"

CProgram* CProgram::m_used = NULL;

CProgram::CProgram():
m_init(false),
m_id(0)
{

}

CProgram::~CProgram(){
	glDeleteProgram(m_id);
}

char* CProgram::loadShader( const QString& p_filename ){
	FILE* fp;
	char* content = NULL;
	long length;
	QByteArray ba = p_filename.toAscii();

	fp = fopen( ba.data(), "rb" );
	if (fp)	{
		fseek( fp, 0, SEEK_END );
		length = ftell( fp );
		fseek( fp, 0, SEEK_SET );
		content = new char [length+1];
		fread( content, sizeof( char ), length, fp );
		fclose( fp );
		content[length] = '\0';
	}

	return content;
}

int CProgram::createShader(const QString& p_filename, GLenum p_shaderType){
	const GLchar* content = loadShader(p_filename);

	if (content == NULL){
		qDebug() << "Echec du chargement d'un shader\n" << p_filename;
		return -1;
	}

	GLint status, logSize;
	QByteArray log;
	GLuint shader = glCreateShader(p_shaderType);

	glShaderSource(shader, 1, &content, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE){
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
		log.resize(logSize - 1);
		glGetShaderInfoLog(shader, logSize, &logSize, log.data());
		qDebug() << QString("Echec de la compilation du %1 shader %2:\n\n%3").arg((p_shaderType == GL_VERTEX_SHADER) ? "vertex" : "fragment").arg(p_filename).arg(QString(log));
		return -2;
	}
	glAttachShader(m_id, shader);
	delete [] content;

	return 0;
}

void CProgram::initProgram( const QString& p_shaderPrefix ){
	if(m_init)
		return;

	m_id = glCreateProgram();
	createShader(p_shaderPrefix + ".vs", GL_VERTEX_SHADER);
	//createShader(p_shaderPrefix + ".ts", GL_TESS_CONTROL_SHADER);
	//createShader(p_shaderPrefix + ".gs", GL_GEOMETRY_SHADER);
	createShader(p_shaderPrefix + ".fs", GL_FRAGMENT_SHADER);

	GLint status, logSize;
	QByteArray log;
	glLinkProgram(m_id);
	glGetProgramiv(m_id, GL_LINK_STATUS, &status);
	if(status != GL_TRUE){
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &logSize);
		log.resize(logSize - 1);
		glGetProgramInfoLog(m_id, logSize, &logSize, log.data());
		qDebug() << QString("Echec du linkage du programme:\n\n%1").arg(QString(log));
		return;
	}
}

//----------

void CProgram::sendUniform1f(const QString& p_name,  GLfloat  v0){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform1f( glGetUniformLocation( m_id, (const char*) ba.data() ), v0 );
}

void CProgram::sendUniform2f(const QString& p_name,  GLfloat  v0,  GLfloat  v1){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform2f( glGetUniformLocation( m_id, (const char*) ba.data() ), v0, v1 );
}
void CProgram::sendUniform3f(const QString& p_name,  GLfloat  v0,  GLfloat  v1,  GLfloat  v2){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform3f( glGetUniformLocation( m_id, (const char*) ba.data() ), v0, v1, v2 );
}

void CProgram::sendUniform4f(const QString& p_name,  GLfloat  v0,  GLfloat  v1,  GLfloat  v2,  GLfloat  v3){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform4f( glGetUniformLocation( m_id, (const char*) ba.data() ), v0, v1, v2, v3 );
}

void CProgram::sendUniform1i(const QString& p_name,  GLint  v0){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform1i( glGetUniformLocation( m_id, (const char*) ba.data() ), v0 );
}

void CProgram::sendUniform2i(const QString& p_name,  GLint  v0,  GLint  v1){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform2i( glGetUniformLocation( m_id, (const char*) ba.data() ), v0, v1 );
}

void CProgram::sendUniform3i(const QString& p_name,  GLint  v0,  GLint  v1,  GLint  v2){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform3i( glGetUniformLocation( m_id, (const char*) ba.data() ), v0, v1, v2 );
}

void CProgram::sendUniform4i(const QString& p_name,  GLint  v0,  GLint  v1,  GLint  v2,  GLint  v3){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform4i( glGetUniformLocation( m_id, (const char*) ba.data() ), v0, v1, v2, v3 );
}


void CProgram::sendUniform1fv(const QString& p_name,  GLsizei  count,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform1fv( glGetUniformLocation( m_id, (const char*) ba.data() ), count, value );
}

void CProgram::sendUniform2fv(const QString& p_name,  GLsizei  count,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform2fv( glGetUniformLocation( m_id, (const char*) ba.data() ), count, value );
}

void CProgram::sendUniform3fv(const QString& p_name,  GLsizei  count,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform3fv( glGetUniformLocation( m_id, (const char*) ba.data() ), count, value );
}

void CProgram::sendUniform4fv(const QString& p_name,  GLsizei  count,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform4fv( glGetUniformLocation( m_id, (const char*) ba.data() ), count, value );
}

void CProgram::sendUniform1iv(const QString& p_name,  GLsizei  count,  const GLint * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform1iv( glGetUniformLocation( m_id, (const char*) ba.data() ), count, value );
}

void CProgram::sendUniform2iv(const QString& p_name,  GLsizei  count,  const GLint * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform2iv( glGetUniformLocation( m_id, (const char*) ba.data() ), count, value );
}

void CProgram::sendUniform3iv(const QString& p_name,  GLsizei  count,  const GLint * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform3iv( glGetUniformLocation( m_id, (const char*) ba.data() ), count, value );
}

void CProgram::sendUniform4iv(const QString& p_name,  GLsizei  count,  const GLint * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform4iv( glGetUniformLocation( m_id, (const char*) ba.data() ), count, value );
}


void CProgram::sendUniformMatrix2fv(const QString& p_name,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniformMatrix2fv( glGetUniformLocation( m_id, (const char*) ba.data() ), count, transpose, value );
}

void CProgram::sendUniformMatrix3fv(const QString& p_name,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniformMatrix3fv( glGetUniformLocation( m_id, (const char*) ba.data() ), count, transpose, value );
}

void CProgram::sendUniformMatrix4fv(const QString& p_name,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniformMatrix4fv( glGetUniformLocation( m_id, (const char*) ba.data() ), count, transpose, value );
}

void CProgram::sendUniformMatrix2x3fv(const QString& p_name,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniformMatrix2x3fv( glGetUniformLocation( m_id, (const char*) ba.data() ), count, transpose, value );
}

void CProgram::sendUniformMatrix3x2fv(const QString& p_name,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniformMatrix3x2fv( glGetUniformLocation( m_id, (const char*) ba.data() ), count, transpose, value );
}

void CProgram::sendUniformMatrix2x4fv(const QString& p_name,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniformMatrix2x4fv( glGetUniformLocation( m_id, (const char*) ba.data() ), count, transpose, value );
}

void CProgram::sendUniformMatrix4x2fv(const QString& p_name,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniformMatrix4x2fv( glGetUniformLocation( m_id, (const char*) ba.data() ), count, transpose, value );
}

void CProgram::sendUniformMatrix3x4fv(const QString& p_name,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniformMatrix3x4fv( glGetUniformLocation( m_id, (const char*) ba.data() ), count, transpose, value );
}

void CProgram::sendUniformMatrix4x3fv(const QString& p_name,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniformMatrix4x3fv( glGetUniformLocation( m_id, (const char*) ba.data() ), count, transpose, value );
}


