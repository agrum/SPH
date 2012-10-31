/*
 * CThread.cpp
 *
 *  Created on: Apr 11, 2012
 *      Author: agrum
 */

#include "CThread.h"

QList<void*> CThread::m_pendingList;
QList<void*> CThread::m_currentList;
QMutex CThread::m_mutex;
int CThread::m_currentPhase = 0;
int CThread::m_currentToken = 0;
int CThread::m_currentStamp = 0;
QList<int> CThread::m_maxToken;
QTime CThread::m_time;
int CThread::m_elapsed;
int CThread::m_loopTime;

//Constructors and dest
CThread::CThread(int p_start, int p_inc, int p_split, int p_phase, CRoutine* p_routine, QString p_id) :
	m_start(p_start),
	m_inc(p_inc),
	m_split(p_split),
	m_phase(p_phase),
	m_id(p_id),
	m_routine(p_routine),
	m_stamp(0),
	m_subPhase(0)
{
	start();
}

CThread::~CThread() {
	exit();
}

//Static init
void CThread::setStatic(QList<int> p_maxToken, int p_loopTime){
	m_maxToken = p_maxToken;
	m_loopTime = p_loopTime;
	m_time.start();
}

//Main loop
void CThread::run(){
	QList<void*> toNext;

	while(true){
		while(m_currentPhase != m_phase) //Waiting for the good phase
			usleep(1000);

		m_stamp = m_currentStamp; //Affect the stamp to avoid double execution in a same phase
		m_wait.start(); //Local time check
		toNext.clear();
		int start = m_start + m_inc*m_subPhase;
		int inc = m_inc*m_split;
		m_subPhase = (m_subPhase+1)%m_split;

		//-----

		m_routine->execute(start, inc, m_elapsed, m_currentList, toNext); //SubLoop

		//------

		m_mutex.lock(); //Token, phase and list change
		m_pendingList.append(toNext); //Update the on progress list
		//if(m_currentToken == 0) //New phase log
		//	qDebug() << "\tPhaseBegin" << m_currentPhase;
		//qDebug() << "\t\t" << m_id << QString("%1").arg(m_wait.elapsed()); //Local elapsed time log

		if(++m_currentToken == m_maxToken[m_currentPhase]){ //Take token & check for next phase
			m_currentList = m_pendingList; //New list become current
			m_pendingList.clear();
			m_currentPhase++; //New phase
			if(m_currentPhase == m_maxToken.size()){ //Check all phase done
				m_elapsed = m_time.elapsed(); //get elapsed time for main loop
				//qDebug() << "LoopEnd " << m_elapsed;
				if(m_loopTime - m_elapsed > 0)
					usleep(1000*(m_loopTime - m_elapsed));
				m_time.start();
				m_currentPhase = 0; //reinit phase
			}
			m_currentToken = 0; //reinit token
			m_currentStamp++; //new stamp
		}
		m_mutex.unlock();

		//-----

		//Waiting for a stamp change (2nd step to avoid multiple execution in the same phase&&stamp phase)
		while(m_currentStamp - m_maxToken.size() < m_stamp)
			usleep(1000);
	}
}
