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
#include "csignalisation.h"

class CApp : public QObject
{
    Q_OBJECT
public:
    CApp();
    ~CApp();

    CBdd *_bdd;

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

public slots:
    void on_timerStart();
    void on_timerStop(int ordre, QDateTime dt2);
    void on_runnersImport(QStringList nomEleves);
    void on_getControl();
    void on_srvRemoteGetControl();
    void on_workerThread();

private:
    QDateTime _dt1;
    qint64 _deltaTm;
    qint64 _deltaTs;
    qint64 _deltaTms;
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
