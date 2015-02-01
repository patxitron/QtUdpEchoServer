#include "udplistener.h"

UdpListener::UdpListener(qint16 port, QObject *parent)
		:QObject(parent)
{
	sock_.bind(QHostAddress::Any, port);
	connect(&sock_, &QUdpSocket::readPendingDatagrams, [this](){
		while(sock_.hasPendingDatagrams()) {
			QByteArray datagram;
			datagram.resize(sock_.pendingDatagramSize());
			QHostAddress sender;
			quint16 sender_port;
			sock_.readDatagram(
				 datagram.data()
				,datagram.size()
				,&sender
				,&sender_port
			);
			sock_.writeDatagram(datagram, sender, sender_port);
			sendResponse(sender, sender_port, datagram);
			emit received(QString::fromUtf8(datagram));
		}
	});
}
