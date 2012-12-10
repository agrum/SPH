/*
 * CIFWidget.cpp
 *
 *  Created on: May 18, 2012
 *      Author: agrum
 */

#include "CIFWidget.h"

CIFWidget::CIFWidget():
m_camera(&m_cameraCenter),
m_left(false),
m_add(false),
m_ctrl(false),
m_zoom(6)
{
	//Camera
	m_eye[0] = 10.0*cos(-m_x/300.0)*cos(m_y/300.0)/m_zoom;
	m_eye[1] = 10.0*sin(-m_x/300.0)*cos(m_y/300.0)/m_zoom;
	m_eye[2] = 10.0*sin(m_y/300.0)/m_zoom;
	m_camera->lookAt(
			m_eye[0], m_eye[1], m_eye[2],
			0, 0, 0);

	setMouseTracking(true);
	setWindowTitle(trUtf8("InFire"));
	startTimer(50);
	resize(1024, 512);
	showFullScreen();

	show();
}

CIFWidget::~CIFWidget(){
	for(int a = 0; a < m_object.size(); a++)
		delete m_object[a];
	CVA::disable();
	CVA::remove();
}

void CIFWidget::initializeGL(){
	lemonGL::init();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_POINT_SPRITE_ARB);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

	//Objects
	float worldSize = 34.0;
	CVA::create(100000);
	CMeshMngr::add("meshes/sphere.obj");
	CMeshMngr::add("meshes/cube.obj");
	m_box = new CIFBox(CMeshMngr::get("pCube"));
	m_box->translate(-0.5, -0.5, -0.5);
	m_object.push_back(m_box);
	m_particles = new CIFParticleObj(worldSize);
	m_particles->translate( -0.5, -0.5, -0.5 );
	m_particles->scale( 1.0/worldSize, 1.0/worldSize, 1.0/worldSize );

	//Shaders
	m_opaqueProgram = CShaderInterface::add("shaders/opaque");
	m_illuminationProgram = CShaderInterface::add("shaders/illumination");
	m_particleDrawProgram = CShaderInterface::add("shaders/particle/particleDraw");

	//Light
	CLight* light = new CLight();
	light->lookAt(
			1, 1, 1,
			0, 0, 0);
	light->setPerspective(45, 1.0, 0.1f, 30.0f);
	light->setIntensity(0.3);
	light->setEnableShadow(true);
	light->setShadowMapSize(2048, 2048);
	m_light.push_back(light);

	CVA::enable();
}

void CIFWidget::paintGL()
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Shadow maps generation
	m_box->cull(m_light[0]->viewMatrix());
	CShaderInterface::use(m_opaqueProgram);
	CLight::bindFB();
	glEnable(GL_DEPTH_TEST);
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for(int a = 0; a < m_object.size(); a++){
		m_light[0]->attachTexToFB();
		m_object[a]->draw(m_light[0]);
	}
	CLight::unbindFB();

	//opaque render
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	m_box->cull(m_camera->viewMatrix());
	CShaderInterface::use(m_opaqueProgram);
	for(int a = 0; a < m_object.size(); a++)
		m_object[a]->draw(m_camera);

	//lights
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	CShaderInterface::use(lemonGL::m_illuminationProgram);
	for(int a = 0; a < m_object.size(); a++){
		m_object[a]->draw(m_camera, &m_light);
	}
	glDepthMask(GL_TRUE);

	//Particles
	CShaderInterface::use(m_particleDrawProgram);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	m_particles->draw(m_camera);
	glDisable(GL_BLEND);

	//To next step
	m_particles->iterate();

	//Time
        //qDebug() << "end" << m_time.elapsed() << "ms";
	m_time.start();
}

void CIFWidget::timerEvent(QTimerEvent *){
	update();
}

void CIFWidget::resizeGL(int p_width, int p_height){
	m_cameraFree.setViewPortSize(p_width, p_height);
	m_cameraCenter.setViewPortSize(p_width, p_height);
	m_cameraFree.setPerspective(45.0f, (float) p_width / (float) p_height, 0.1f, 30.0f);
	m_cameraCenter.setPerspective(45.0f, (float) p_width / (float) p_height, 0.1f, 30.0f);
}

void CIFWidget::mousePressEvent(QMouseEvent* p_event){
	m_posiStampX = p_event->x();
	m_posiStampY = p_event->y();
	if(p_event->button() == Qt::LeftButton)
		m_left = true;
}

void CIFWidget::mouseReleaseEvent(QMouseEvent* p_event){
	if(m_posiStampX == p_event->x() && m_posiStampY == p_event->y()){
		if(p_event->button() == Qt::RightButton)
			m_camera = (m_camera == &m_cameraCenter) ? &m_cameraFree : &m_cameraCenter;
	}
	if(p_event->button() == Qt::LeftButton)
		m_left = false;
}

void CIFWidget::keyPressEvent(QKeyEvent* p_event){
	if(p_event->key() == Qt::Key_Up && m_camera == &m_cameraFree)
		m_camera->translate(0.02,0,0);
	if(p_event->key() == Qt::Key_Down && m_camera == &m_cameraFree)
		m_camera->translate(-0.02,0,0);
	if(p_event->key() == Qt::Key_Left && m_camera == &m_cameraFree)
		m_camera->translate(0,0.02,0);
	if(p_event->key() == Qt::Key_Right && m_camera == &m_cameraFree)
		m_camera->translate(0,-0.02,0);
	if(p_event->key() == Qt::Key_Control)
		m_ctrl = true;
	if(p_event->key() == Qt::Key_D)
		m_particles->drop();
	if(p_event->key() == Qt::Key_G)
		m_particles->gravity();
	if(p_event->key() == Qt::Key_Escape)
		exit(0);

}

void CIFWidget::keyReleaseEvent(QKeyEvent* p_event){
	if(p_event->key() == Qt::Key_Control)
		m_ctrl = false;
}

void CIFWidget::mouseMoveEvent(QMouseEvent* p_event){
	if(m_left){
		if(m_camera == &m_cameraCenter){
			m_x += p_event->x() - m_posiX;
			m_y += p_event->y() - m_posiY;
			if(m_y > 300) m_y = 300;
			else if(m_y < -300) m_y = -300;

			m_eye[0] = 10.0*cos(-m_x/300.0)*cos(m_y/300.0)/m_zoom;
			m_eye[1] = 10.0*sin(-m_x/300.0)*cos(m_y/300.0)/m_zoom;
			m_eye[2] = 10.0*sin(m_y/300.0)/m_zoom;

			m_camera->lookAt(
					m_eye[0], m_eye[1], m_eye[2],
					0, 0, 0);
		}
		else {
			if(p_event->y() - m_posiY != 0 || p_event->x() - m_posiX != 0){
				if(!m_ctrl){
					m_camera->lookUp((float) -(p_event->y() - m_posiY)/1000.0);
					m_camera->lookLeft((float) (p_event->x() - m_posiX)/1000.0);
				}
				else {
					m_camera->lookForward((float) -(p_event->x() - m_posiX)/1000.0);
				}
			}
		}
	}

	m_posiX = p_event->x();
	m_posiY = p_event->y();
}

void CIFWidget::wheelEvent(QWheelEvent* p_event){
	if(m_camera == &m_cameraCenter){
		m_zoom *= 1 + (float)p_event->delta()/5000.0;

		m_eye[0] = 10.0*cos(-m_x/300.0)*cos(m_y/300.0)/m_zoom;
		m_eye[1] = 10.0*sin(-m_x/300.0)*cos(m_y/300.0)/m_zoom;
		m_eye[2] = 10.0*sin(m_y/300.0)/m_zoom;

		m_camera->lookAt(
				m_eye[0], m_eye[1], m_eye[2],
				0, 0, 0);
	}
	else {
		m_camera->translate(0.0001*(float)p_event->delta(),0,0);
	}
}
