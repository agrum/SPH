/*
 * CLink.cpp
 *
 *  Created on: Mar 30, 2012
 *      Author: agrum
 */

#include "CLink.h"

//Constructors and dest
CLink::CLink(CParticle* p_a, CParticle* p_b, unsigned int p_aIndex, unsigned int p_bIndex) :
m_a(p_a),
m_b(p_b),
m_aIndex(p_aIndex),
m_bIndex(p_bIndex)
{
	m_a->link(m_b, p_aIndex);
	m_b->link(m_a, p_bIndex);
}

CLink::CLink(const CLink& p_link) :
m_a(p_link.m_a),
m_b(p_link.m_b),
m_aIndex(p_link.m_aIndex),
m_bIndex(p_link.m_bIndex)
{

}

CLink::~CLink(){
	m_a->unlink(m_aIndex);
	m_b->unlink(m_bIndex);
}

CLink& CLink::operator=(const CLink& p_link){
	m_a = p_link.m_a;
	m_b = p_link.m_b;
	m_aIndex = p_link.m_aIndex;
	m_bIndex = p_link.m_bIndex;

	return *this;
}
