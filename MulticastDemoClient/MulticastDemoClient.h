#ifndef MULTICASTDEMOCLIENT_H
#define MULTICASTDEMOCLIENT_H

#include <QtWidgets/QDialog>
#include "ui_MulticastDemoClient.h"

class QUdpSocket;

class QMulticastDemoClient : public QDialog
{
	Q_OBJECT

public:
	QMulticastDemoClient(QWidget *parent = 0);
	~QMulticastDemoClient();

protected:
	virtual void timerEvent(QTimerEvent *event);

private slots:
	void receivedData();

private:
	Ui::QMulticastDemoClientClass ui;

	int m_nTimerId;

	QUdpSocket* m_pSocket;

	QTime* m_pTime;
	int m_nByte;
};

#endif // MULTICASTDEMOCLIENT_H
