#ifndef CGERERCLIENT_H
#define CGERERCLIENT_H

#include <QObject>
#include <QTcpSocket>

#include "cprotocole.h"

class CGererClient : public QObject
{
    Q_OBJECT
public:
    explicit CGererClient(QTcpSocket *sock = nullptr, QObject *parent = nullptr);
    //CProtocole *_protocole;
    ~CGererClient(){}

signals:
    void sigPrintTxt(QString txt);
    void sigPrintError(QString err);
    void sigEndClient();

private slots:
    void onReadyRead();

private:
    QTcpSocket *_sock;

    QByteArray _request;

    void prepareAnswerOK(){}
    void prepareAnswerErr(){}
    void answer(){}

};

#endif // CGERERCLIENT_H
