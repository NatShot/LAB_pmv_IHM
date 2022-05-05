#ifndef CPROTOCOLE_H
#define CPROTOCOLE_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <iostream>
#include <stdio.h>
#include <QString>
#include <string>
#include "cserveur.h"

using namespace std;

class CProtocole : public QObject
{
    Q_OBJECT
public:
    CProtocole();
    ~CProtocole();

    explicit CProtocole(QObject *parent = nullptr);

    QJsonObject btnAVM();
    QJsonObject btnPrep();
    QJsonObject btnStartSession();
    QJsonObject btnStopSession();
    QJsonObject onReplyFinished(QNetworkReply *reply);
    QJsonObject decodeTrame();
    QJsonObject getCSV(QString csv);
    QJsonObject sendTrame();
    QString timeRun(int ligne);
    QJsonObject transfertAllRunners();
    QJsonObject transfertCSV();
    QJsonObject transfertRunner(int ID);

    bool authCheck();
    bool oldSessionExist();
    bool rememberLastSession();

private:
    QTcpSocket *_sock;
    QJsonValue *_trame;
    int _ligne;

    QString _wind1;
    QString _speed1;
    QString _time1;
    QString _wind2;
    QString _speed2;
    QString _time2;

signals:
    void finished();

private slots:
    void on_resVitesse(QString resVitesse, int ordre, int ligne);
    void on_resTemps(QString resTemps, int ordre, int ligne);
};

#endif // CPROTOCOLE_H
