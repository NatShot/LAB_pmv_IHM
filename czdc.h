#ifndef CZDC_H
#define CZDC_H
//#pragma once

#include <QObject>
#include <QSharedMemory>
#include "cgererclient.h"


typedef enum {
    ETEINT,
    FIXE,
    LENT,
    RAPIDE
} T_MODE_FEU;

typedef struct s_data {
    T_MODE_FEU modeDeFonctionnement;
    bool activeSignalisation;
    //int tempo;
} T_DATAS;

class CZdc : public QSharedMemory
{
    Q_OBJECT

public:
    CZdc(QObject *parent = nullptr);
    ~CZdc();
    void sauveDatas(T_DATAS &datas);
    void getDatas(T_DATAS &datas);
    void sauveAddrClient(CGererClient *_Cgc);

signals:
    void sig_newDatas();
    void sig_addrClient();

private:
    T_DATAS *_datas;
};

#endif // CZDC_H
