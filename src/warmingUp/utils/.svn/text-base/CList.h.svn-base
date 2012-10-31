/*
 * CList.h
 *
 *  Created on: Apr 12, 2012
 *      Author: agrum
 *      Desc: Thread safe array with O(1) for access, remove and push
 */

#ifndef CLIST_H_
#define CLIST_H_

#include <QList>
#include <QMutex>

#include "CTagNames.h"

template <typename T>
class CList {

public:
	//Constructors and dest
	CList(unsigned int);
	~CList();

	//Access
	inline unsigned int size() const;
	inline unsigned int maxSize() const;
	inline T* at(unsigned int& a) const;

	//Mutator
	inline void append(QList<T*>& p_list);
	inline void remove(QList<unsigned int>& p_list);

private:
	QList<unsigned int> m_free;
	T** m_list;
	QMutex m_mutex;
	unsigned int m_limit;
};

//------Definition

//Constructor and dest
template<typename T>
CList<T>::CList(unsigned int p_limit):
m_limit(p_limit)
{
	m_list = new T*[m_limit];
	for(unsigned int a = 0; a < m_limit; a++){
		m_list[a] = NULL;
		m_free.push_back(a);
	}
}

template<typename T>
CList<T>::~CList(){
	for(unsigned int a = 0; a < m_limit; a++)
		if(m_list[a] != NULL)
			delete m_list[a];
	delete[] m_list;
}

//number of effective elements
template<typename T>
inline unsigned int CList<T>::size() const{
	return m_limit - m_free.size();
}

//maximum number of effective elements
template<typename T>
inline unsigned int CList<T>::maxSize() const{
	return m_limit;
}

//Access
template<typename T>
inline T* CList<T>::at(unsigned int& a) const{
	return m_list[a];
}

//Append a list of pointers to elements, these are deleted, usefull for expansive copy constructor
template<typename T>
inline void CList<T>::append(QList<T*>& p_list){
	T* tmp;

	m_mutex.lock();
	while(!m_free.empty() && !p_list.empty()){
		tmp = p_list.takeFirst();
		m_list[m_free.takeFirst()] = tmp;
	}
	m_mutex.unlock();
}

//Re Init some elements from a list of indexes
template<typename T>
inline void CList<T>::remove(QList<unsigned int>& p_list){
	unsigned int tmp;

	m_mutex.lock();
	while(!p_list.empty()){
		tmp = p_list.takeFirst();
		if(tmp < m_limit && m_list[tmp] != NULL){
			delete m_list[tmp];
			m_list[tmp] = NULL;
			m_free.push_back(tmp);
		}
	}
	m_mutex.unlock();
}

#endif /* CLIST_H_ */
