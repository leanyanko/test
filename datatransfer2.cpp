#include "datatransfer.hpp"
#include <QDateTime>

DataTransfer::DataTransfer(trikControl::BrickInterface *Brick , QWidget *parent)
    : QPushButton(tr("Quit"), parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(close()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(sendDatagram()));

    timer.start(1 * 1000);

    brick = Brick;
}


void DataTransfer::sendDatagram()
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_3);
    //out << QDateTime::currentDateTime() << temperature() << humidity()
      //  << altitude();
    for(int i = 0; i < 3; i++)
    {
        out << brick->gyroscope()->read()[i];

    }

    for(int i = 0; i < 3; i++)
    {
        brick->accelerometer()->read()[i];
    }

    udpSocket.writeDatagram(datagram, QHostAddress("192.168.77.255"), 5824);
}