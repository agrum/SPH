/*
 * CReference.h
 *
 *  Created on: Apr 25, 2012
 *      Author: agrum
 */

#ifndef CREFERENCE_H_
#define CREFERENCE_H_

#include "CTagNames.h"

class CReference : public CDom {

public:
	CReference(void (*)(void*, void*, void*), void*);

	inline const QString& id() { return m_id; }
	inline float m() { return m_mass; }
	inline float visc() { return m_viscosity; }
	inline float frict() { return m_friction; }
	inline void chronos(void* p_particle, void* p_list) { m_function(m_parent, p_particle, p_list); }

protected:
	void initXml(const QDomNode&);

private:
	QString m_id;
	float m_mass;
	float m_viscosity;
	float m_friction;

	void (*m_function)(void*, void*, void*);
	void* m_parent;
};

#endif /* CREFERENCE_H_ */
