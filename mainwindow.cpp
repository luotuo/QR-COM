#include "mainwindow.h"
#include "ui_mainwindow.h"

QList<QString> coms;
QMutex comsMutex;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    comOpenFlag(false)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    updateComInfo->stop();
    delete ui;
    if (serialPort)
        delete serialPort;
    if (updateComInfo)
        delete updateComInfo;
    serialPort = nullptr;
    updateComInfo = nullptr;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    updateComInfo->stop();
    updateComInfo->wait();
    serialPort->close();
}

void MainWindow::init()
{
    serialPort = new MySerialPort();
    updateComInfo = new UpdateComInfo();
    connect(updateComInfo, &UpdateComInfo::updateComInfo, this, &MainWindow::updateCbCom);
    connect(serialPort, &MySerialPort::readyRead, this, &MainWindow::readData);
    updateComInfo->start();
    ui->cbBaudRate->setCurrentText("9600");
    ui->cbDataBit->setCurrentText("8");
    ui->cbCheckBit->setCurrentText("no");
    ui->cbStopBit->setCurrentText("1");
    baudRate = "9600";
    stopBits = "1";
    parity = "no";
    dataBits = "8";
    loopSendFlag = false;
    currentCOM = "COM1";
    timer = nullptr;
}

void MainWindow::on_pbSendButton_clicked()
{
    if (loopSendFlag) {
        if (timer == nullptr) {
            int timeout = ui->leSendInterval->text().toInt();
            timer = new QTimer();
            connect(timer, &QTimer::timeout, this, &MainWindow::sendData);
            timer->start(timeout);
        }
    } else {
        sendData();
    }
}

void MainWindow::on_openCOM_clicked()
{
    bool res = false;
    if (comOpenFlag) {
        // Close com
        serialPort->close();
        ui->openCOM->setText("打开");
        comOpenFlag = false;
    } else {
        // Open com
        currentCOM = ui->cbCom->currentText();
        baudRate = ui->cbBaudRate->currentText();
        stopBits = ui->cbStopBit->currentText();
        parity = ui->cbCheckBit->currentText();
        dataBits = ui->cbDataBit->currentText();
        serialPort->setPortName(currentCOM);
        res = serialPort->setComParams(currentCOM, baudRate, dataBits, parity, stopBits);
        qDebug() << "setComParams == " << res;
        res = serialPort->open();
        qDebug() << "open == " << res;
        if (!res) {
            QMessageBox::warning(NULL, "警告", "打开串口失败",
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return;
        }
        ui->openCOM->setText("关闭");
        comOpenFlag = true;
    }
}

void MainWindow::on_cbCom_currentIndexChanged(const QString &arg1)
{
    currentCOM = arg1;
}

void MainWindow::on_cbBaudRate_currentIndexChanged(const QString &arg1)
{
    baudRate = arg1;
}

void MainWindow::on_cbCheckBit_currentIndexChanged(const QString &arg1)
{
    parity = arg1;
}

void MainWindow::on_cbDataBit_currentIndexChanged(const QString &arg1)
{
    dataBits = arg1;
}

void MainWindow::on_cbStopBit_currentIndexChanged(const QString &arg1)
{
    stopBits = arg1;
}

void MainWindow::on_pbClearData_clicked()
{
    ui->teDataReceived->clear();
}

void MainWindow::on_ccbLoopSend_clicked()
{
    loopSendFlag = !loopSendFlag;
    if (!loopSendFlag) {
        if (timer) {
            disconnect(timer, &QTimer::timeout, this, &MainWindow::sendData);
            delete timer;
            timer = nullptr;
        }
    }
}

void MainWindow::updateCbCom()
{
    ui->cbCom->clear();
    comsMutex.lock();
    if (coms.size()) ui->cbCom->addItems(coms);
    else ui->cbCom->addItem("COM1");
    comsMutex.unlock();
    if (coms.contains(currentCOM)) ui->cbCom->setCurrentText(currentCOM);
    else ui->cbCom->setCurrentIndex(0);
}

void MainWindow::sendData()
{
    QString data = ui->teDataSend->toPlainText();
    int res = serialPort->write(data);
    qDebug() << "send data == " << res;
}

void MainWindow::readData(QString data)
{
    QString str = ui->teDataReceived->toPlainText();
    if (ui->ccbHex->checkState()) {
        QByteArray b = data.toUtf8();
        char *ch = b.data();
        char s[8] = {'\0'};
        QString str = "";
        for (int i = 0; i < b.size(); ++i) {
            sprintf(s, "%02x", ch[i]);
            str.append(s);
        }
    } else {
        str += data;
    }
    ui->teDataReceived->setText(str);
}
