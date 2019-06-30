#include "MulticastDemoServer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QMulticastDemoServer w;
	w.show();
	return a.exec();
}
