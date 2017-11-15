#ifndef UPDATECOMINFO_H
#define UPDATECOMINFO_H

#include <QThread>
#include <QSerialPortInfo>
#include <QList>
#include <QMutex>
#include <QDebug>


class UpdateComInfo : public QThread
{
    Q_OBJECT
public:
    UpdateComInfo();
    ~UpdateComInfo();

public:
    void stop() { startFlag = false; }
protected:
    void run();
private:
    bool startFlag;

signals:
    void updateComInfo();
};
extern QList<QString> coms;
extern QMutex comsMutex;

#endif // UPDATECOMINFO_H
