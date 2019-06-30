#include "ObjectSend.h"
#include <QUdpSocket>
#include "QThread"
#include <QTime>

QObjectSend::QObjectSend(QObject *parent)
	: QObject(parent)
{
	m_bRunning = true;
}

QObjectSend::~QObjectSend()
{
}

void QObjectSend::sendData()
{
	QUdpSocket* pSocket = new QUdpSocket(this);

	char szData[512];
	strcpy(szData, "这是一个组播数据");
	int nSize = 512;

	QTime objTime;
	objTime.start();

	int nLen = 0;
	int nCount = 0;

	while (m_bRunning)
	{
		nLen = pSocket->writeDatagram(szData, nSize, QHostAddress("224.0.1.5"), 9999);
		if (nLen >= 0)
		{
			nCount += nLen;
		}
		
		float fMs = objTime.elapsed();
		if (fMs >= 1000.0)
		{
			// byte
			float fByte = nCount;
			// KB
			fByte /= 1024;
			// MB
			fByte /= 1024;

			float fSpeed = fByte / (fMs / 1000);
			QString qsSpeed = QString::number(fSpeed, 'f', 1);
			if (qsSpeed != m_qsSpeed)
			{
				m_qsSpeed = qsSpeed;
				emit speedChanged(m_qsSpeed);
			}

			nCount = 0;
			objTime.restart();
		}
	}

	pSocket->close();
	pSocket->deleteLater();
}

void QObjectSend::stopSending()
{
	m_bRunning = false;
}
