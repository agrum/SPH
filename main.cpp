#include <QtCore>
#include <QApplication>
#include "src/CIFWidget.h"

#define SIZE 30
#define NBR_ENTITY 15000

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	pLog::init("watch.log", pLog::ERROR | pLog::WARNING);
	CIFWidget bleh;

	return a.exec();
}
