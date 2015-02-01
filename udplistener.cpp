#include "udplistener.h"

UdpListener::UdpListener(qint16 port, QObject *parent)
		:QObject(parent)
		,port_(port)
{
	sock_.bind(QHostAddress::Any, port);
	connect(&sock_, &QIODevice::readyRead, [this](){
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
			emit received(
				QString("%1:%2 -> <%3> %4").arg(sender.toString())
									  .arg(sender_port).arg(port_)
									  .arg(QString::fromUtf8(datagram))
			);
		}
	});
}
