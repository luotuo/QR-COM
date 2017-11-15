#include "updatecominfo.h"

UpdateComInfo::UpdateComInfo() : QThread(NULL), startFlag(false) {

}

UpdateComInfo::~UpdateComInfo() {

}

void UpdateComInfo::run() {
    startFlag = true;
    while (startFlag) {
        // Update com info
        coms.clear();
        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
            coms.append(info.portName());
        }
        updateComInfo();
        QThread::sleep(1);
    }
}
