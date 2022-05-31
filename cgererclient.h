#ifndef CGERERCLIENT_H
#define CGERERCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>

#include "cprotocole.h"

class CGererClient : public QObject
{
    Q_OBJECT
public:
    explicit CGererClient(QTcpSocket *sock = nullptr, QObject *parent = nullptr);
    ~CGererClient();

    int emettreVersClients(QString mess);
    QTcpSocket *_sock;

public slots:
    void on_erreurReseau(QAbstractSocket::SocketError err);
    void onReadyRead();
    void on_sendJson(QString type, QString param);

private:
    CProtocole _prot;

signals:
    void sig_dataClient(QString adrIpClient, QString data);

};

#endif // CGERERCLIENT_H

