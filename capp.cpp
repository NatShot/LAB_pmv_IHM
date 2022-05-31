#include "capp.h"

CApp::CApp()
{
    _capteurPassage1 = new CCapteurPassage(nullptr, 17, 1);
    _capteurPassage2 = new CCapteurPassage(nullptr, 27, 2);
    _ligne = -1;

    _serv = new CServeur();
}

CApp::~CApp()
{
    delete _capteurPassage1;
    delete _capteurPassage2;
}


void CApp::on_timerStart()
{
    _ligne++;

    _dt1 = QDateTime::currentDateTime();
    connect(_capteurPassage1, &CCapteurPassage::sig_coureurArrived, this, &CApp::on_timerStop);
    connect(_capteurPassage2, &CCapteurPassage::sig_coureurArrived, this, &CApp::on_timerStop);
    //emit sig_base de données
    //emit sig_affichage feu

}

void CApp::on_timerStop(int ordre, QDateTime dt2)
{
    CCapteurPassage *cp = static_cast<CCapteurPassage *>(sender());
    calculateTime(dt2, ordre);
    disconnect(cp, &CCapteurPassage::sig_coureurArrived, this, &CApp::on_timerStop);
}

void CApp::calculateSpeed(int ordre)
{
    double deltaTs = _deltaTs;
    double deltaTms = _deltaTms;

    if(_deltaTm > 0)
        deltaTs += 60; //Si la course dure plus d'1 min, on rajoute 60s au delta T qui représente que les secondes
    deltaTs = deltaTs + (deltaTms / 1000);

    double Calcul = 50.0 / deltaTs * 3.6;
    QString resultatVitesse = QString::number(Calcul, 'g', 2);
    emit sig_resVitesse(resultatVitesse, ordre, _ligne);

}

void CApp::calculateTime(QDateTime dt2, int ordre)
{
    _deltaTms = _dt1.msecsTo(dt2);
    _deltaTm = _deltaTms / 60000;
    _deltaTs = (_deltaTms % 60000) / 1000;
    _deltaTms = (_deltaTms % 60000) % 1000;
    calculateSpeed(ordre);

    QString resultatTemps = QString::number(_deltaTm) + " : " + QString::number(_deltaTs) +" : " + QString::number(_deltaTms);
    emit sig_resTemps(resultatTemps, ordre, _ligne);

}


