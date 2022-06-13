#ifndef CAPP_H
#define CAPP_H

#include <QMainWindow>
#include <QObject>
#include <QDateTime>
#include <QString>
#include <QThread>

#include "ccapteurpassage.h"
#include "cserveur.h"
#include "canemometre.h"
#include "cbdd.h"
#include "czdc.h"
#include "csignalisation.h"

class CApp : public QObject
{
    Q_OBJECT
public:
    CApp();
    ~CApp();

    CBdd *_bdd;
    CZdc *_zdc;

signals:
    void sig_timerStart();
    void sig_timerStop();
    void sig_resTemps(QString resultatTemps, int ordre, int ligne);
    void sig_resVitesse(QString resultatVitesse, int ordre, int ligne);
    void sig_calculateSpeed(QString resultat);
    void sig_readBdd(QString data);
    void sig_srvGetControl();
    void sig_appRemoteGetControl();
    void sig_workerThread();
    void sig_checkCredentials(QString login, QString pass);
    void sig_credentials(bool state);
    void sig_sessionName(QString nomSession);
    void sig_endRun();

public slots:
    void on_timerStart();
    void on_timerStop(int ordre, QDateTime dt2);
    void on_runnersImport(QStringList nomEleves);
    void on_getControl();
    void on_srvRemoteGetControl();
    void on_workerThread();
    void on_checkCredentials(QString login, QString pass);
    void on_credentials(bool state);
    void on_nomSession(QString nomSession);

private:
    QDateTime _dt1;
    quint64 _deltaTm;
    quint64 _deltaTs;
    quint64 _deltaTms;
    CCapteurPassage *_capteurPassage1;
    CCapteurPassage *_capteurPassage2;
    int _ligne;

    QThread *_th;
    CSignalisation *_sign;
    CServeur *_serv;


    void calculateTime(QDateTime dt2, int ordre);
    void calculateSpeed(int ordre);


};

#endif // CAPP_H
