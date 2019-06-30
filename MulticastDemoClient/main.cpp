#include "MulticastDemoClient.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QMulticastDemoClient w;
	w.show();
	return a.exec();
}
