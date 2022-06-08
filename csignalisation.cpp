#include "csignalisation.h"

CSignalisation::CSignalisation(QObject *parent): QObject(parent)
{
    connect(this, &CSignalisation::sig_threadRestart, this, &CSignalisation::on_goTravail);
    _gpioRed = new CGpio(this, 18, OUT);
    _gpioFan = new CGpio(this, 4, BOTH);
    _gpioGreen = new CGpio(this, 23, OUT);
    _gpioBuzzer = new CGpio(this, 18, OUT);
    _zdc = new CZdc();
}

CSignalisation::~CSignalisation()
{
    delete _zdc;
    delete _gpioBuzzer;
    delete _gpioGreen;
    delete _gpioFan;
    delete _gpioRed;
}

void CSignalisation::on_goTravail()
{
    T_DATAS datas;
    _zdc->getDatas(datas);
    switch(datas.modeDeFonctionnement) {
    case LENT:
        _gpioFan->ecrire(1);
        _gpioRed->ecrire(1);
        qDebug() << "Allumage Lent";
        usleep(500000);
        _gpioFan->ecrire(0);
        _gpioRed->ecrire(0);
        qDebug() << "Extinction Lent";
        usleep(500000);
        break;
    case RAPIDE:
        _gpioFan->ecrire(1);
        _gpioRed->ecrire(1);
        qDebug() << "Allumage Rapide";
        usleep(100000);
        _gpioFan->ecrire(0);
        _gpioRed->ecrire(0);
        qDebug() << "Extinction Rapide";
        usleep(100000);
        break;
    case ETEINT:
        //_gpioRed->ecrire(0);
        usleep(100000);
        break;
    case FIXE:
        _gpioFan->ecrire(1);
        _gpioGreen->ecrire(1);
        _gpioBuzzer->ecrire(1);
        qDebug() << "Allumage Fixe";
        usleep(5000000);
        _gpioFan->ecrire(0);
        _gpioGreen->ecrire(0);
        _gpioBuzzer->ecrire(0);
        qDebug() << "Extinction Fixe";
        break;
    } // sw

    if (datas.activeSignalisation)
        emit sig_threadRestart();
} // method

