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
    QString getSessionName ();

    void getSession (T_SESSION &data);

    void setListeEleves (QList<QString> liste); // Liste des élèves de la clé prof
    QList<QString> getListeEleves();

    void setCoureurAuDepart (QString _name, int ligne, int couloir);
    bool verifConnection (QString bddLogin, QString bddPass);

private:

    QSqlDatabase PMVBdd;

    QString _sqlPath;
    QSqlQuery *_sqlQuery;
    int _index;
    QString _name;
    QString _firstname;
    int _exit;
    void clearElevesList();

signals:
//    void sig_authentification (QString txt){}
    void sig_connectionOK (bool connectionOK);

private slots:
    void on_valeursCoureur(QString restTemps, QString resVitesse, QString vent, QString id);

};
#endif // CBDD_H
