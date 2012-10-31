#include <QtCore>
#include <QApplication>
#include "src/inFire/CInFire.h"

#define SIZE 30
#define NBR_ENTITY 15000

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//CProject bleh("configuration/inFire.conf");
	CIFWidget bleh;

	return a.exec();
}
