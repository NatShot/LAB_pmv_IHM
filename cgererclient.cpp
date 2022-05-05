#include "cgererclient.h"

CGererClient::CGererClient(QTcpSocket *sock, QObject *parent) :
    QObject(parent), _sock(sock)
{
    connect(_sock, &QTcpSocket::readyRead, this, &CGererClient::onReadyRead);
//    _protocole = new CProtocole(); // enlever explicit dans le cprotocole.h CA MARCHE
}

void CGererClient::onReadyRead()
{
    _request = _sock->readAll();
    emit sigPrintTxt(_request);

    _sock->close();
}
