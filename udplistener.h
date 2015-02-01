#ifndef UDPLISTENER_H
#define UDPLISTENER_H

#include <QObject>
#include <QUdpSocket>
#include <QString>

class UdpListener : public QObject
{
	Q_OBJECT
public:
	UdpListener(qint16 port, QObject *parent = 0);

signals:
	void received(QString const&);

private:
	qint16 port_;
	QUdpSocket sock_;
};

#endif // UDPLISTENER_H
