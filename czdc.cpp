#include "czdc.h"

CZdc::CZdc(QObject *parent) : QSharedMemory(parent)
{
    setKey("PMV");
    int res = create(sizeof(T_DATAS));
    if (!res) {
        attach();
    }
    _datas = static_cast<T_DATAS *>(data());
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
    QString addrClient = *_Cgc;
    emit sig_addrClient(); //Connect avec slot de CApp
} // getMesures


