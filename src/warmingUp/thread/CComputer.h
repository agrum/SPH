/*
 * CComputer.h
 *
 *  Created on: Apr 2, 2012
 *      Author: agrum
 *      Desc: Compute forces over the linked particles and break the obsolete links
 */

#ifndef CComputer_H_
#define CComputer_H_

#include "CRoutine.h"

class CComputer : public CRoutine {

public:
	CComputer() {}

	void execute(int, int, int, const QList<void*>&, QList<void*>&);
};

#endif /* CComputer_H_ */
