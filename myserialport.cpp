#include "myserialport.h"

MySerialPort::MySerialPort() : QObject(nullptr)
{
    com = new QSerialPort();
    setComParams("COM1", "9600", "8", "no", "1");
}

MySerialPort::MySerialPort(QString portName,
                           QString baudRate,
                           QString databits,
                           QString parity,
                           QString stopBits) : QObject(nullptr)
{
    com = new QSerialPort();
    setComParams(portName, baudRate, databits, parity, stopBits);
}

MySerialPort::~MySerialPort()
{
    if (com)
        delete com;
    com = nullptr;
}

bool MySerialPort::open()
{
    connect(com, &QSerialPort::readyRead, this, &MySerialPort::read);
    qDebug() << portName
             << baudRate
             << databits
             << parity
             << stopBits;
    bool res = com->open(QIODevice::ReadWrite);
    qDebug() << "err == " << errno;
    qDebug() << com->errorString();
    return res;
}

void MySerialPort::close()
{
    com->close();
    disconnect(com, &QSerialPort::readyRead, this, &MySerialPort::read);
}

qint64 MySerialPort::read()
{
    //FIXME: Need to insert data to a queue
    QByteArray buf;
    buf = com->readAll();
    if(!buf.isEmpty()) {
        readData.clear();
        readData = tr(buf);
    }
    readyRead(readData);
    buf.clear();
}

qint32 MySerialPort::write(QString data)
{
    return com->write(data.toUtf8());
}


