#include "cprotocole.h"


CProtocole::CProtocole(QObject *parent) : QObject(parent)
{
//trame << "transfertCsv" << "authCheck_TRa" << "authCheck_RaT" << "btnPrep";
    connect(_sock, &QTcpSocket::readyRead, this, &CProtocole::timeRun);
}

QJsonObject CProtocole::btnAVM()
{

}

QJsonObject CProtocole::btnPrep()
{

}

QJsonObject CProtocole::btnStartSession()
{

}

QJsonObject CProtocole::btnStopSession()
{

}

CProtocole::~CProtocole()
{

}

QJsonObject CProtocole::decodeTrame()
{
//    switch(trames.indexOf(trame)){

    //    }
}

QJsonObject CProtocole::getCSV(QString csv)
{

}

QJsonObject CProtocole::sendTrame()
{

}

QString CProtocole::timeRun(int ligne)
{
    QByteArray timeRun = QString("{\"command\": \"timeRun\", \"data\": { \"id\": " + QString::number(ligne) + ", \"time1\":" + _time1 + ", \"wind1\":" + _wind1 + ", \"speed1\":" + _speed1 + ", \"time2\":" + _time2 + ", \"wind2\":" + _wind2 + ",\"speed2\":" + _speed2 + "}}").toStdString().c_str();
    return 0;
}

QJsonObject CProtocole::transfertAllRunners()
{

}

QJsonObject CProtocole::transfertCSV()
{

}

QJsonObject CProtocole::transfertRunner(int ID)
{

}

bool CProtocole::authCheck()
{

}

bool CProtocole::oldSessionExist()
{

}

bool CProtocole::rememberLastSession()
{

}

void CProtocole::on_resTemps(QString resTemps, int ordre, int ligne)
{
    _ligne = ligne;
    if(ordre == 1) {
        _time1.toStdString() = resTemps.toStdString();
    }
    else if (ordre == 2) {
        _time2.toStdString() = resTemps.toStdString();
    }
}

void CProtocole::on_resVitesse(QString resVitesse, int ordre, int ligne)
{
    _ligne = ligne;
    if (ordre == 1) {
        _speed1.toStdString() = resVitesse.toStdString();
    }
    else if (ordre == 2) {
        _speed2.toStdString() = resVitesse.toStdString();
    }
}


QJsonObject CProtocole::onReplyFinished(QNetworkReply *reply)
{
    QByteArray response = reply->readAll();

    if (!response.isEmpty()) {

    QJsonDocument jdoc = QJsonDocument::fromJson(response);
    QJsonObject jobj = jdoc.object();
    QJsonObject data = jobj ["data"].toObject();

    QString dataType = data["type"].toString();
    qDebug() << "Filtre du type de data : " << dataType;

    emit finished();
    }else{
        std::cout << "Erreur" << std::endl;
    }
    reply->deleteLater();

}

