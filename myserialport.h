#ifndef MYSERIALPORT_H
#define MYSERIALPORT_H

#include <QSerialPort>
#include <QDebug>

#include "commons.h"


class MySerialPort : public QObject
{
    Q_OBJECT
public:
    MySerialPort();
    MySerialPort(QString portName,
                 QString baudRate,
                 QString databits,
                 QString parity,
                 QString stopBits);
    ~MySerialPort();
    void setPortName(QString name) {
        this->portName = name;
        this->com->setPortName(this->portName);
    }
    bool setBaudRate(QString baudRate) {
        this->baudRate = baudRate;
        return this->com->setBaudRate(str2BaudRate(this->baudRate));
    }
    bool setDataBits(QString dataBits) {
        this->databits = dataBits;
        return this->com->setDataBits(str2DataBits(this->databits));
    }
    bool setParity(QString parity) {
        this->parity = parity;
        return this->com->setParity(str2Parity(this->parity));
    }
    bool setStopBits(QString stopBits) {
        this->stopBits = stopBits;
        return this->com->setStopBits(str2StopBits(this->stopBits));
    }
    bool setComParams(QString portName,
                      QString baudRate,
                      QString databits,
                      QString parity,
                      QString stopBits) {
        setPortName(portName);
        bool res = setBaudRate(baudRate);
        qDebug() << "res == " << res;
        res &= setDataBits(databits);
        qDebug() << "res == " << res;
        res &= setParity(parity);
        qDebug() << "res == " << res;
        res &= setStopBits(stopBits);
        qDebug() << "res == " << res;
        res &= this->com->setFlowControl(QSerialPort::NoFlowControl);
        qDebug() << "res == " << res;
        return res;
    }
    bool open();
    void close();
public slots:
    qint64 read();
    qint32 write(QString data);
signals:
    void readyRead(QString data);
private:
    QSerialPort *com;
    QString portName;
    QString baudRate;
    QString databits;
    QString parity;
    QString stopBits;
    QString readData;
};


#endif // MYSERIALPORT_H
