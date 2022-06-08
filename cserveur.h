#ifndef CSERVEUR_H
#define CSERVEUR_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

#include "cgererclient.h"
#include "czdc.h"
#include "cbdd.h"

#define PORT 2314

class CServeur : public QObject
{
    Q_OBJECT
public:
    CServeur(CBdd *bdd, QObject *parent = nullptr);
    ~CServeur();

public slots:
    void on_printTxt(QString txt);
    void on_disconnectedClient();
    void on_srvGetControl();
    void on_remoteGetControl();

private:
    QTcpServer _serv;
    QTcpSocket *_sock;
    CGererClient *_client;
    quint16 _noPort;
    QString cgererclient;
    CBdd *_bdd;

signals:
    void sig_evenementServeur(QString eve);
    void sig_erreur(QAbstractSocket::SocketError err);
    void sig_adrClient(QString adrClient);
    void sig_maJClients(QList<QTcpSocket *> liste);
    void sig_clientGetControl();
    void sig_srvRemoteGetControl();

private slots:
    void on_printError(QString err);
    void on_newConnection();

};

#endif // CSERVEUR_H
