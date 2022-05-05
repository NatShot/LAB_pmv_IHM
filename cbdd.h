#ifndef CBDD_H
#define CBDD_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSql>
#include <iostream>
#include "canemometre.h"
#include "cprotocole.h"

#define PATH "../../"

QT_BEGIN_NAMESPACE
namespace Ui { class CBdd; }
QT_END_NAMESPACE

typedef struct {

} T_SESSION; // à voir avec le prof

class CBdd : public QMainWindow
{
    Q_OBJECT

public:
    CBdd(QWidget *parent = nullptr);
    ~CBdd();

    bool isSessionActive ();
    void setSessionActive (bool s);
    void setSessionName (QString sessionName);
    void getSession (T_SESSION &data);
    void setListeEleves (QStringList liste); // Liste des élèves de la clé prof
    void setCoureurAuDepart (QString name, int ligne, int couloir);
    void setValeursCoureur (int couloir, int ligne, QString resTemps, QString resVitesse, QString vent);
    bool verifConnection (QString bddLogin, QString bddPass);

private:
    Ui::CBdd *ui;

    QSqlDatabase PMVBdd;

    QString sqlPath = "/Users/natshot/Desktop/Projet_PMV_2022/PMVBdd";
    QSqlQuery sqlQuery;
    int index;
    QString name;
    QString firstname;

signals:
//    void sig_authentification (QString txt){}
    void sig_connectionOK (bool connectionOK);

private slots:
    void on_elevesRcv (QString eleves);
    void on_resTemps (QString resTemps);
    void on_resVent (QString resVent);
    void on_resVitesse (QString resVitesse);

};
#endif // CBDD_H
