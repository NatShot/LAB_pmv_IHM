#ifndef CSERVEUR_H
#define CSERVEUR_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

#include "cgererclient.h"
#include "czdc.h"

#define PORT 2314

class CServeur : public QTcpServer
{
    Q_OBJECT
public:
    CServeur(QObject *parent = nullptr);
    ~CServeur();

public slots:
    void onPrintTxt(QString txt);
    void on_newConnectionClient();
    void on_disconnectedClient();

private:
    QTcpServer _serv;
    QList<QTcpSocket *> _listeClients;
    quint16 _noPort;
    QString cgererclient;


signals:
    void sig_evenementServeur(QString eve);
    void sig_erreur(QAbstractSocket::SocketError err);
    void sig_adrClient(QString adrClient);
    void sig_maJClients(QList<QTcpSocket *> liste);

private slots:
    void onPrintError(QString err);
    void onNewConnection();

};

#endif // CSERVEUR_H
