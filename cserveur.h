#ifndef CSERVEUR_H
#define CSERVEUR_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

#include "cgererclient.h"
#include "CZdc.h"

#define PORT 2314

class CServeur : public QObject
{
    Q_OBJECT
public:
    CServeur(QObject *parent = nullptr);
    ~CServeur();
    QTcpSocket *_sock;

public slots:
    void onPrintTxt(QString txt);

private:
    QTcpServer _serv;


signals:
    void sigPrintTxt(QString txt);
    void sigPrintError(QString err);

private slots:
    void onPrintError(QString err);
    void onNewConnection();

};

#endif // CSERVEUR_H
