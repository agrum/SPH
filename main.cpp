#include <QtCore>
#include <QApplication>
#include "src/CIFWidget.h"

#define SIZE 30
#define NBR_ENTITY 15000

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	CLog::init("watch.log", CLog::ERROR | CLog::WARNING);
	CIFWidget bleh;

	return a.exec();
}
