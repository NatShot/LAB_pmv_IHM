#include "csignalisation.h"

CSignalisation::CSignalisation(QObject *parent): QObject(parent)
{
    connect(this, &CSignalisation::sig_threadRestart, this, &CSignalisation::on_goTravail);
    _gpio = new CGpio(this, 27, OUT);
    _zdc = new CZdc();
}

CSignalisation::~CSignalisation()
{
    delete _zdc;
    delete _gpio;
}

void CSignalisation::on_goTravail()
{
    T_DATAS datas;
    _zdc->getDatas(datas);
    switch(datas.modeDeFonctionnement) {
    case LENT:
        _gpio->ecrire(1);
        usleep(500000);
        _gpio->ecrire(0);
        usleep(500000);
        break;
    case RAPIDE:
        _gpio->ecrire(1);
        usleep(100000);
        _gpio->ecrire(0);
        usleep(100000);
        break;
    case ETEINT:
        _gpio->ecrire(0);
        usleep(100000);
        break;
    case FIXE:
        _gpio->ecrire(1);
        usleep(5000000);
        _gpio->ecrire(0);
        break;
    } // sw

    if (datas.activeSignalisation)
        emit sig_threadRestart();
} // method

