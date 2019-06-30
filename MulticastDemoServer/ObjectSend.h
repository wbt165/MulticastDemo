#pragma once

#include <QObject>

class QObjectSend : public QObject
{
	Q_OBJECT

public:
	QObjectSend(QObject *parent = NULL);
	~QObjectSend();

	void stopSending();

public slots:
	void sendData();

private:
	bool m_bRunning;
	QString m_qsSpeed;

signals:
	void speedChanged(const QString& qsSpeed);
};
