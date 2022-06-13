#include "czdc.h"

CZdc::CZdc(QObject *parent) : QSharedMemory(parent)
{
    setKey("PMV");
    int res = create(sizeof(T_DATAS));
    if (!res) {
        attach();
        _datas = static_cast<T_DATAS *>(data());
    } else {
        _datas = static_cast<T_DATAS *>(data());
        bzero(_datas, sizeof(T_DATAS));
    } // else
}

CZdc::~CZdc()
{
    detach();
}

void CZdc::sauveDatas(T_DATAS &datas)
{
    lock();
    memcpy(_datas, &datas, sizeof(T_DATAS));
    unlock();
    emit sig_newDatas();
} // sauveMesures

void CZdc::getDatas(T_DATAS &datas)
{
    lock();
    memcpy(&datas, _datas, sizeof(T_DATAS));
    unlock();
}

void CZdc::sauveAddrClient(CGererClient *_Cgc)
{
    //QString addrClient = *_Cgc->;
    //emit sig_addrClient(); //Connect avec slot de CApp
}

void CZdc::sauveButtons(T_BUTTONS &buttons)
{
    lock();
        _datas->buttons = buttons;
    unlock();
    emit sig_newBtnState(buttons);
}

void CZdc::getButtons(T_BUTTONS &buttons)
{
    lock();
        buttons = _datas->buttons;
    unlock();
}

void CZdc::setTemps(int ordre, quint64 temps)
{
    lock();
        _datas->t[ordre-1] = temps;
    unlock();
}

quint64 CZdc::getTemps(int ordre)
{
    lock();
        quint64 tmps = _datas->t[ordre-1];
    unlock();
    return tmps;
}

void CZdc::setVitesse(int ordre, double vit)
{
    lock();
    _datas->v[ordre-1] = vit;
    unlock();
}

double CZdc::getVitesse(int ordre)
{
    lock();
    double vitesse = _datas->v[ordre-1];
    unlock();
    return vitesse;
}

void CZdc::setCoureurArrived(int ordre, bool etat)
{
    lock();
    _datas->b[ordre-1] = etat;
    unlock();
}

bool CZdc::getCoureurArrived(int ordre)
{
    lock();
    bool fini = _datas->b[ordre-1];
    unlock();
    return fini;
}


