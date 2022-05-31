#ifndef CAPP_H
#define CAPP_H

#include <QMainWindow>
#include <QObject>
#include <QDateTime>
#include <QString>

#include "ccapteurpassage.h"
#include "cserveur.h"
#include "canemometre.h"
#include "cbdd.h"

class CApp : public QObject
{
    Q_OBJECT
public:
    CApp();
    ~CApp();

signals:
    void sig_timerStart();
    void sig_timerStop();
    void sig_resTemps(QString resultatTemps, int ordre, int ligne);
    void sig_resVitesse(QString resultatVitesse, int ordre, int ligne);
    void sig_calculateSpeed(QString resultat);

public slots:
    void on_timerStart();
    void on_timerStop(int ordre, QDateTime dt2);

private:
    QDateTime _dt1;
    qint64 _deltaTm;
    qint64 _deltaTs;
    qint64 _deltaTms;
    CCapteurPassage *_capteurPassage1;
    CCapteurPassage *_capteurPassage2;
    int _ligne;

    void calculateTime(QDateTime dt2, int ordre);
    void calculateSpeed(int ordre);


};

#endif // CAPP_H
