#include "commons.h"


BaudRate str2BaudRate(QString baudRate)
{
    qint32 br = baudRate.toInt();
    BaudRate res = BaudRate::Baud9600;
    switch (br) {
    case 1200:
        res = BaudRate::Baud1200;
        break;
    case 2400:
        res = BaudRate::Baud2400;
        break;
    case 4800:
        res = BaudRate::Baud4800;
        break;
    case 19200:
        res = BaudRate::Baud19200;
        break;
    case 38400:
        res = BaudRate::Baud38400;
        break;
    case 57600:
        res = BaudRate::Baud57600;
        break;
    case 9600:
        break;
    case 115200:
        res = BaudRate::Baud115200;
        break;
    default:
        res = BaudRate::UnknownBaud;
        break;
    }
    return res;
}

DataBits str2DataBits(QString dataBits)
{
    qint32 db = dataBits.toInt();
    DataBits res = DataBits::Data8;
    switch (db) {
    case 5:
        res = DataBits::Data5;
        break;
    case 6:
        res = DataBits::Data6;
        break;
    case 7:
        res = DataBits::Data7;
    case 8:
        break;
    default:
        res = DataBits::UnknownDataBits;
        break;
    }
    return res;
}

Parity str2Parity(QString parity)
{
    Parity res = Parity::NoParity;
    if (!parity.compare("even", Qt::CaseInsensitive))
        res = Parity::EvenParity;
    else if (!parity.compare("odd", Qt::CaseInsensitive))
        res = Parity::OddParity;
    else if (!parity.compare("space", Qt::CaseInsensitive))
        res = Parity::SpaceParity;
    else if (!parity.compare("mark", Qt::CaseInsensitive))
        res = Parity::MarkParity;
    else if (!parity.compare("no", Qt::CaseInsensitive))
        res = Parity::NoParity;
    else
        res = Parity::UnknownParity;
    return res;
}

StopBits str2StopBits(QString stopBits)
{
    qint32 sb = stopBits.toInt();
    StopBits res = StopBits::OneStop;
    switch (sb) {
    case 1:
        break;
    case 2:
        res = StopBits::TwoStop;
        break;
    case 3:
        res = StopBits::OneAndHalfStop;
    default:
        res = StopBits::UnknownStopBits;
        break;
    }
    return res;
}
