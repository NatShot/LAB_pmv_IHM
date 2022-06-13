#ifndef CGERERCLIENT_H
#define CGERERCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <unistd.h>

#include "cprotocole.h"
#include "cbdd.h"


class CGererClient : public QObject
{
    Q_OBJECT
public:
    explicit CGererClient(QTcpSocket *sock = nullptr, CBdd *bdd = nullptr, QObject *parent = nullptr);
    ~CGererClient();

public slots:
    void on_erreurReseau(QAbstractSocket::SocketError err);
    void on_readyRead();
    void on_sendJson(QString type, QString param);
    void on_clientGetControl();

private:
    CProtocole _prot;
    QTcpSocket *_sock;
    QString sessionName;
    int emettreVersClient(QString mess);
    CBdd *_bdd;

signals:
    void sig_dataClient(QString adrIpClient, QString data);
    void sig_remoteGetControl();

};

#endif // CGERERCLIENT_H

