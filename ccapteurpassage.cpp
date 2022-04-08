#include "ccapteurpassage.h"

CCapteurPassage::CCapteurPassage(QObject *parent, int noGpio, int ordre) : QObject(parent)
{
    _ordre = ordre;
    _gpio = new CGpio(this, noGpio, IN);
    QString path("/sys/class/gpio/gpio"+QString::number(noGpio)+"/value");
    _file.addPath(path);
    connect(&_file, &QFileSystemWatcher::fileChanged, this, &CCapteurPassage::on_filechanged);

}

CCapteurPassage::~CCapteurPassage()
{
    delete _gpio;
}

void CCapteurPassage::on_filechanged()
{
    QDateTime dt2 = QDateTime::currentDateTime();
    emit sig_coureurArrived(_ordre, dt2);
}




