/*
	Copyright 2012 Thomas Le Guerroué-Drévillon
	This file is part of lemonGL.

	lemonGL is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	lemonGL is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with lemonGL.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CIFWIDGET_H_
#define CIFWIDGET_H_

#include "CIFParticleObj.h"
#include "CIFBox.h"

#include "lemonGL.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <QTime>

class CIFWidget : public QGLWidget {

public:
	CIFWidget();
	~CIFWidget();

	virtual void initializeGL();
	virtual void paintGL();

	void resizeGL(int w, int h);

	void mouseMoveEvent(QMouseEvent*);
	void mousePressEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);
	void keyPressEvent(QKeyEvent*);
	void keyReleaseEvent(QKeyEvent*);
	void wheelEvent(QWheelEvent*);

private:
	void timerEvent(QTimerEvent *);

protected:
	CMVP m_cameraCenter;
	CMVP m_cameraFree;
	CMVP* m_camera;
	QList<CLight*> m_light;
	QList<CObject* > m_object;

	GLuint m_opaqueProgram;
	GLuint m_illuminationProgram;
	GLuint m_particleDrawProgram;

	CIFBox* m_box;
	CIFParticleObj* m_particles;

	bool m_left;
	bool m_add;
	bool m_ctrl;
    float m_x, m_y;
    int m_posiX, m_posiY;
    int m_posiStampX, m_posiStampY;
    float m_zoom;
    float m_eye[3];

    QTime m_time;
};

#endif /* CIFWIDGET_H_ */
