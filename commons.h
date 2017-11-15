#ifndef COMMONS_H
#define COMMONS_H

#include <QSerialPort>

typedef QSerialPort::BaudRate BaudRate;
typedef QSerialPort::DataBits DataBits;
typedef QSerialPort::Direction Direction;
typedef QSerialPort::FlowControl FlowControl;
typedef QSerialPort::Parity Parity;
typedef QSerialPort::StopBits StopBits;

BaudRate str2BaudRate(QString baudRate);
DataBits str2DataBits(QString dataBits);
Parity str2Parity(QString parity);
StopBits str2StopBits(QString stopBits);

#endif // COMMONS_H
