#include "cgererclient.h"

CGererClient::CGererClient(QTcpSocket *sock, CBdd *bdd, QObject *parent) :
    QObject(parent), _sock(sock), _bdd(bdd)
{
    connect(_sock, &QTcpSocket::readyRead, this, &CGererClient::on_readyRead);
}

CGererClient::~CGererClient(){

}

void CGererClient::on_readyRead()
{
    QList<QString> nomCoureurs;
    QString nomSession;
    QByteArray ba;
    QString trame, command;
    QTcpSocket *client = static_cast<QTcpSocket*>(sender());

    ba = client->readAll();

    if((ba.indexOf(':') >= 0) && (ba.indexOf('"') >= 0))
        command = ba.split(':')[1].split('"')[1];
    else
        return;

    if(command == "authCheck"){
        QString login, mdp;
        if(_prot.parseJsonAuthCheck(QString(ba), login, mdp)){
            trame = _prot.prepareJsonAuthCheck(true);
            client->write(trame.toStdString().c_str());
            client->write("\r\n");
            client->flush();
            emit sig_dataClient("", trame);
            // provoquer l'envoi des valeurs de la session en cours.
            // Lire les datas dans la BDD
            sessionName = _bdd->getSessionName();
            qDebug() << "Nom de la session : " << sessionName;
            nomCoureurs = _bdd->getListeEleves();
            qDebug() << "Nombre de lignes : " << nomCoureurs;
            // former la trame d'envoi
            command = _prot.prepareJsonTransfertAllRunners(sessionName, nomCoureurs);
            // envoyer la trame
            qDebug() << "TransfertAllRunners : " << command;
            client->write(command.toStdString().c_str());
            client->write("\r\n");
            client->flush();
            emit sig_dataClient("", command);
        } //if
    } // if

    if(command == "getCsv"){
        if(_prot.parseJsonGetCsv(QString(ba))){
            T_CSV csv[40] = {
                {1, "coureur1", "00:03:01.230", "5.6 km/h", "4.9 km/h"},
                {2, "coureur2", "00:03:01.230", "5.6 km/h", "4.9 km/h"},
                {3, "coureur3", "00:03:01.230", "5.6 km/h", "4.9 km/h"},
                {4, "coureur4", "00:03:01.230", "5.6 km/h", "4.9 km/h"},
                {5, "coureur5", "00:03:01.230", "5.6 km/h", "4.9 km/h"},
                {6, "coureur6", "00:03:01.230", "5.6 km/h", "4.9 km/h"},
                {7, "coureur7", "00:03:01.230", "5.6 km/h", "4.9 km/h"},
                {8, "coureur8", "00:03:01.230", "5.6 km/h", "4.9 km/h"},
                {9, "coureur9", "00:03:01.230", "5.6 km/h", "4.9 km/h"},
                {10, "coureur10", "00:03:01.230", "5.6 km/h", "4.9 km/h"},
                {11, "coureur11", "00:03:01.230", "5.6 km/h", "4.9 km/h"},
                {12, "coureur12", "00:03:01.230", "5.6 km/h", "4.9 km/h"},
                {13, "coureur13", "00:03:01.230", "5.6 km/h", "4.9 km/h"},
                {14, "coureur14", "00:03:01.230", "5.6 km/h", "4.9 km/h"}
            };
            trame = _prot.prepareJsonTransfertCsv(14, csv);
            client->write(trame.toStdString().c_str());
            client->write("\r\n");
        } //if
    } //if

    if(command == "getControl"){
        emit sig_dataClient(client->peerAddress().toString(), "Reprise de contrôle par la tablette.");
    }

    if(command == "btnState"){
        T_BTN_STATE state;
        if(_prot.parseJsonBtnState(QString(ba), &state)){
            // TODO
        } //if
    } //if

    qDebug() << "Client : " << client << ba;
    emit sig_dataClient(client->peerAddress().toString(), QString(ba));
}

void CGererClient::on_sendJson(QString type, QString param){
    QString trame;

    if(type == "getControl"){
        trame = _prot.parseJsonGetControl(trame);
        emettreVersClients(trame);
    } //getControl

    if(type == "btnState"){
        T_BTN_STATE state;
        state.btnSess = param.toUInt()&0x01;
        state.btnPrep = param.toUInt()&0x02;
        state.btnAVM = param.toUInt()&0x04;
        state.btnReady = param.toUInt()&0x08;
        state.btnGo = param.toUInt()&0x10;
        trame = _prot.prepareJsonBtnState(state);
        emettreVersClients(trame);
    } //btnState
}

void CGererClient::on_clientGetControl()
{
    QString trame;
    trame = _prot.prepareJsonGetControl();
    emettreVersClients(trame);
} //onSendJson

int CGererClient::emettreVersClients(QString mess){
    _sock->write(mess.toStdString().c_str());
    _sock->write("\r\n");
    _sock->flush();
    qDebug() << "Envois vers " << _sock->peerAddress().toString();
    return 1;
}

void CGererClient::on_erreurReseau(QAbstractSocket::SocketError err)
{

}
