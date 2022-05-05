#include "cserveur.h"
#include "cprotocole.h"

CServeur::CServeur(QObject *parent): QObject(parent)
{
    _serv.listen(QHostAddress::Any, PORT);
    connect(&_serv, &QTcpServer::newConnection, this, &CServeur::onNewConnection);
//    connect(&_trame, &CProtocole::, this, &CServeur::onNewConnection);
}

CServeur::~CServeur()
{

}

void CServeur::onPrintTxt(QString txt)
{
    emit sigPrintTxt(txt);
}

void CServeur::onPrintError(QString err)
{
    emit sigPrintError(err);
}

void CServeur::onNewConnection()
{
    _sock = _serv.nextPendingConnection();
    CGererClient *client = new CGererClient(_sock);
    connect(client, &CGererClient::sigPrintTxt, this, &CServeur::onPrintTxt);
    connect(client, &CGererClient::sigPrintError, this, &CServeur::onPrintError);
    QByteArray bienvenue = "{\"command\": \"authCheck\", \"data\": { \"success\": 1 }}";
    _sock->write(bienvenue, bienvenue.size());
    _sock->flush();

    //leId  ID
    //leMdp  MDP
}
