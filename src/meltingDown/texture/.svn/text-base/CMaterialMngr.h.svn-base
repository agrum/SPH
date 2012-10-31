/*
 * CMaterialMngr.h
 *
 *  Created on: May 28, 2012
 *      Author: agrum
 */

#ifndef CMATERIALMNGR_H_
#define CMATERIALMNGR_H_

#include "CMaterial.h"

#include <QFile>

class CMaterialMngr {

public:
	static void add(const QString&);

	static const CMaterial* get(const QString&);

private:
	CMaterialMngr(){}

	static QList<CMaterial> m_materials;
};

#endif /* CMATERIALMNGR_H_ */
