#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMutex>
#include <QMessageBox>
#include <QTimer>

#include "updatecominfo.h"
#include "myserialport.h"

#define LOG 1

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pbSendButton_clicked();

    void on_openCOM_clicked();

    void on_cbCom_currentIndexChanged(const QString &arg1);

    void on_cbBaudRate_currentIndexChanged(const QString &arg1);

    void on_cbCheckBit_currentIndexChanged(const QString &arg1);

    void on_cbDataBit_currentIndexChanged(const QString &arg1);

    void on_cbStopBit_currentIndexChanged(const QString &arg1);

    void on_pbClearData_clicked();

    void on_ccbLoopSend_clicked();

    void updateCbCom();

    void sendData();

    void readData(QString data);

    void closeEvent(QCloseEvent *event);

    void on_pbClearLog_clicked();

private:
    void init();
    void writeLog(const QString &message);
private:
    MySerialPort *serialPort;
    UpdateComInfo *updateComInfo;
    bool comOpenFlag;
    QString baudRate;
    QString parity;
    QString stopBits;
    QString dataBits;
    bool loopSendFlag;
    QString currentCOM;
    QTimer *timer;
private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
