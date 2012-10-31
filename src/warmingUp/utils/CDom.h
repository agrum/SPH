/*
 * CDom.h
 *
 *  Created on: Apr 23, 2012
 *      Author: agrum
 */

#ifndef CDOM_H_
#define CDOM_H_

#include <QtXml>

class CDom {

public:
	CDom() : m_done(false) {};

	void init(const QDomNode& p_node){
		if(!m_done)
			initXml(p_node);
		m_done = true;
	}

protected:
	virtual void initXml(const QDomNode&) = 0;

private:
	bool m_done;
};

#endif /* CDOM_H_ */
