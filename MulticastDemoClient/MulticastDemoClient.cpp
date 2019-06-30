#include "MulticastDemoClient.h"
#include "QUdpSocket"
#include "QTime"

QMulticastDemoClient::QMulticastDemoClient(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_pSocket = new QUdpSocket(this);
	bool bRet = m_pSocket->bind(QHostAddress::AnyIPv4, 9999, QUdpSocket::ShareAddress);
	m_pSocket->setSocketOption(QAbstractSocket::MulticastLoopbackOption, 1);
	bRet = m_pSocket->joinMulticastGroup(QHostAddress("224.0.1.5"));
	QAbstractSocket::SocketError error = m_pSocket->error();
	QString qsError = m_pSocket->errorString();
	
	connect(m_pSocket, SIGNAL(readyRead()), this, SLOT(receivedData()));

	m_nByte = 0;
	m_nTimerId = startTimer(1000);
	m_pTime->start();
}

QMulticastDemoClient::~QMulticastDemoClient()
{
	killTimer(m_nTimerId);
// 
// 	if (NULL != m_pTime)
// 	{
// 		delete m_pTime;
// 		m_pTime = NULL;
// 	}
// 
// 	if (NULL != m_pSocket)
// 	{
// 		m_pSocket->close();
// 		m_pSocket->deleteLater();
// 		m_pSocket = NULL;
// 	}
}

void QMulticastDemoClient::timerEvent(QTimerEvent *event)
{
	// byte
	float fByte = m_nByte;
	// KB
	fByte /= 1024;
	// MB
	fByte /= 1024;

	float fMs = m_pTime->elapsed();
	float fSpeed = fByte / (fMs / 1000);
	QString qsSpeed = QString::number(fSpeed, 'f', 1);
	if (qsSpeed != ui.lineEditSpeed->text())
	{
		ui.lineEditSpeed->setText(qsSpeed);
	}

	m_nByte = 0;
	m_pTime->restart();
}

void QMulticastDemoClient::receivedData()
{
	char* buf = new char[512];
	memset(buf, 0x0, 512);

	QHostAddress ip;
	quint16 port;
	int nLen = m_pSocket->readDatagram(buf, 512, &ip, &port);
	if (nLen >= 0)
	{
		m_nByte += nLen;
	}
}
