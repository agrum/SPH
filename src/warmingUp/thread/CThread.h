/*
 * CThread.h
 *
 *  Created on: Apr 11, 2012
 *      Author: agrum
 *      Desc: global thread's behavior
 */

#ifndef CTHREAD_H_
#define CTHREAD_H_

#include <QThread>
#include <QMutex>
#include <QList>
#include <QTime>
#include <QString>

#include "CRoutine.h"

class CThread : public QThread {

public:
	//Constructors and dest
	CThread(int p_start, int p_inc, int p_split, int p_phase, CRoutine* p_routine, QString p_id = "");
	virtual ~CThread();

	//Init static attributes
	static void setStatic(QList<int>, int);

	//Global loop
	void run();

private:
	//Non available to children static attributes
	static QMutex m_mutex;
	static int m_currentPhase; //Instant phase identifier
	static int m_currentToken; //Number of token taken
	static int m_currentStamp; //Phase iterator without modulo
	static QList<int> m_maxToken; //Tokens available for each phase
	static QTime m_time;
	static QList<void*> m_pendingList; //Void list available for the next phase
	static QList<void*> m_currentList; //Void list available during specific phase
	static int m_elapsed; //Elapsed time last iteration
	static int m_loopTime;

	//Local informations
	int m_start, m_inc; //Where to start and how much to increment
	int m_split; //Number of subPhase
	int m_phase; //Phase when the thread is allowed to run
	QString m_id; //Id for debug
	CRoutine* m_routine;
	int m_stamp; //Stamp when the thread is allowed to end his loop
	QTime m_wait; //Local timer for debug private:
	int m_subPhase; //Instant subPhase
};

#endif /* CTHREAD_H_ */
