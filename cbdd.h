#ifndef CBDD_H
#define CBDD_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSql>
#include <QDebug>

#define PATH "../../"

typedef struct {

} T_SESSION; // à voir avec le prof

class CBdd : public QObject
{
    Q_OBJECT

public:
    CBdd(QObject *parent = nullptr);
    ~CBdd();

    bool isSessionActive (QString sessionName);
    void setSessionActive (bool s);
    void setSessionName (QString sessionName);
    void getSession (T_SESSION &data);
    void setListeEleves (QList<QString> liste); // Liste des élèves de la clé prof
    void setCoureurAuDepart (QString name, int ligne, int couloir);
    bool verifConnection (QString bddLogin, QString bddPass);

private:

    QSqlDatabase PMVBdd;

    QString sqlPath = "/home/pi/Documents/PMVBdd";
    QSqlQuery sqlQuery;
    int index;
    QString name;
    QString firstname;

signals:
//    void sig_authentification (QString txt){}
    void sig_connectionOK (bool connectionOK);

private slots:
    void on_elevesRcv (QString eleves);
    void on_valeursCoureur(QString restTemps, QString resVitesse, QString vent, QString id);

};
#endif // CBDD_H
