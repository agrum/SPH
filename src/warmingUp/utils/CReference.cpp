/*
 * CReference.cpp
 *
 *  Created on: Apr 25, 2012
 *      Author: agrum
 */

#include "CReference.h"

CReference::CReference(void (*p_func)(void*, void*, void*), void* p_parent):
m_mass(0),
m_viscosity(0),
m_friction(0),
m_function(p_func),
m_parent(p_parent)
{

}

void CReference::initXml(const QDomNode& p_node){
	for (QDomNode n = p_node.firstChild(); !n.isNull(); n = n.nextSibling()){
		if (n.isElement()){
			QDomElement e = n.toElement();
			if (e.tagName() == T_REFERENCE_ID)
				m_id = e.text();
			else if (e.tagName() == T_REFERENCE_MASS)
				m_mass = e.text().toFloat();
			else if (e.tagName() == T_REFERENCE_VISCO)
				m_viscosity = e.text().toFloat();
			else if (e.tagName() == T_REFERENCE_FRICT)
				m_friction = e.text().toFloat();
		}
	}
}
