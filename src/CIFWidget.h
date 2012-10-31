/*
 * CIFWidget.h
 *
 *  Created on: May 18, 2012
 *      Author: agrum
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

	CProgram m_opaqueProgram;
	CProgram m_illuminationProgram;
	CProgram m_particleDrawProgram;

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
