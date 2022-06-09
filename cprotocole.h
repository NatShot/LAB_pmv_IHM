#ifndef CPROTOCOLE_H
#define CPROTOCOLE_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QString>

#include "cbdd.h"

#define MAX_CHAR 25

typedef struct sCoureur{
    int id;
    char nom[MAX_CHAR]; //Longueur estimée
} T_COUREUR;

typedef struct sTimeRun {
    char time1[MAX_CHAR];
    char wind1[MAX_CHAR];
    char speed1[MAX_CHAR];
    char time2[MAX_CHAR];
    char wind2[MAX_CHAR];
    char speed2[MAX_CHAR];
} T_TIMERUN;

typedef struct sCsv {
    int idRun;
    char name[MAX_CHAR];
    char time[MAX_CHAR];
    char wind[MAX_CHAR];
    char speed[MAX_CHAR];
} T_CSV;

typedef struct sBtnState {
    bool btnSess;
    bool btnPrep;
    bool btnAVM;
    bool btnReady;
    bool btnGo;
} T_BTN_STATE;

class CProtocole : public QObject
{
    Q_OBJECT
public:
    explicit CProtocole(QObject *parent = nullptr);
    ~CProtocole();

    // Méthodes pour préparer une trame de protocole
    QString prepareJsonTransfertRunner(int idCourse, QList<int> idRunners); // bi-directionnel
    QString prepareJsonTimeRun(int idCourse, T_TIMERUN timeRun); // bi-dir
    QString prepareJsonTransfertCsv(int nbCoureurs, T_CSV *csv); // vers la tablette
    QString prepareJsonAuthCheck(bool res=false, CBdd *bdd=nullptr);  // vers tablette
    QString prepareJsonTransfertAllRunners(QString sessionName, QList<QString> nomCoureurs);
    QString prepareJsonBtnState(T_BTN_STATE state);
    QString prepareJsonGetControl();

    // Méthodes pour parser les trames JSON arrivant du terminal
    bool parseJsonGetCsv(QString trame);  // vers le serveur
    bool parseJsonGetControl(QString trame); // bi dir
    bool parseJsonTransferAllRunners(int *nbCoureurs, QList<T_COUREUR>*coureurs); // vers serveur
    bool parseJsonBtnState(QString trame, T_BTN_STATE *state); // bi dir
    bool parseJsonTimeRun(int *idCourse, T_TIMERUN *timeRun); // bi-dir
    bool parseJsonTransferRunner(int *idCourse, QList<QString> *idRunners); // bi-directionnel
    bool parseJsonAuthCheck(QString trame, QString &login, QString &mdp);  // vers tablette

private:
    // méthodes internes pour former une trame JSON
    QString addEnteteJson(QString commande="command", bool suite=true);
    QString addPiedJson(int nb = 1);
    QString addSectionJson(QString nom="section", int dec=2);
    QString addFinSectionJson(int dec=2, int suite=true);
    QString addParamTexteJson(QString nom="param", QString valeur="0", int dec=2, bool suite=true);
    QString addParamIntJson(QString nom="param", int valeur=0, int dec=2, bool suite=true);
    QString addParamTableauJson(QString nom, QList<int> valeur, int dec=2, bool suite=true);
    QString filtreAvantParser(QString trame);

signals:
    void sig_finished();

private slots:
    void on_resVitesse(QString resVitesse, int ordre, int ligne);
    void on_resTemps(QString resTemps, int ordre, int ligne);
};

#endif // CPROTOCOLE_H
