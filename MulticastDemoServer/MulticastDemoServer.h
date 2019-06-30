#ifndef MULTICASTDEMOSERVER_H
#define MULTICASTDEMOSERVER_H

#include <QtWidgets/QDialog>
#include "ui_MulticastDemoServer.h"

class QObjectSend;

class QMulticastDemoServer : public QDialog
{
	Q_OBJECT

public:
	QMulticastDemoServer(QWidget *parent = 0);
	~QMulticastDemoServer();

private slots:
	void startSending();
	void stopSending();

private:
	Ui::QMulticastDemoServerClass ui;

	QThread* m_pThread;
	QObjectSend* m_pObject;
};

#endif // MULTICASTDEMOSERVER_H
