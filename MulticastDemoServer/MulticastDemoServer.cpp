#include "MulticastDemoServer.h"
#include "ObjectSend.h"
#include "QThread"

QMulticastDemoServer::QMulticastDemoServer(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_pThread = NULL;
	m_pObject = NULL;

	connect(ui.pushButtonStart, SIGNAL(clicked()), this, SLOT(startSending()));
	connect(ui.pushButtonStop, SIGNAL(clicked()), this, SLOT(stopSending()));
}

QMulticastDemoServer::~QMulticastDemoServer()
{
	stopSending();
}

void QMulticastDemoServer::startSending()
{
	if (NULL != m_pObject)
	{
		return;
	}

	m_pObject = new QObjectSend;
	m_pThread = new QThread;
	m_pObject->moveToThread(m_pThread);
	connect(m_pObject, SIGNAL(speedChanged(const QString&)), ui.lineEditSpeed, SLOT(setText(const QString&)));
	connect(m_pThread, SIGNAL(finished()), m_pThread, SLOT(deleteLater()));
	connect(m_pThread, SIGNAL(finished()), m_pObject, SLOT(deleteLater()));
	connect(m_pThread, SIGNAL(started()), m_pObject, SLOT(sendData()));
	m_pThread->start();
}

void QMulticastDemoServer::stopSending()
{
	if (NULL != m_pThread)
	{
		m_pObject->stopSending();

		m_pThread->quit();
		m_pThread->wait();
		m_pThread = NULL;
		m_pObject = NULL;

		ui.lineEditSpeed->setText(QString("0.0"));
	}
}
