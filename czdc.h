#ifndef CZDC_H
#define CZDC_H
//#pragma once

#include <QObject>
#include <QSharedMemory>
#include <string.h>
#include "cgererclient.h"


typedef enum {
    ETEINT,
    FIXE,
    LENT,
    RAPIDE
} T_MODE_FEU;

typedef struct s_buttons {
    bool btnSession;
    bool btnPreparation;
    bool btnAVM;
    bool btnReady;
    bool btnGo;
    bool btnStop;
} T_BUTTONS;

typedef struct s_data {
    T_BUTTONS buttons;
    T_MODE_FEU modeDeFonctionnement;
    bool activeSignalisation;
    quint64 t[2]; // pour les 2 coureurs d'une course
    double v[2];
    bool b[2];  // true si coureur arrivé
    char chaine[2][50];
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
    void sauveButtons(T_BUTTONS &buttons);
    void getButtons(T_BUTTONS &buttons);
    void setTemps(int ordre, quint64 temps);
    quint64 getTemps(int ordre);
    void setVitesse(int ordre, double vit);
    double getVitesse(int ordre);
    void setCoureurArrived(int ordre, bool etat);
    bool getCoureurArrived(int ordre);

signals:
    void sig_newDatas();
    void sig_addrClient();
    void sig_newBtnState(T_BUTTONS buttons);

private:
    T_DATAS *_datas;
};

#endif // CZDC_H
