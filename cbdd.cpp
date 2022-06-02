#include "cbdd.h"

using namespace std;
CBdd::CBdd(QObject *parent): QObject(parent)
{
    PMVBdd = QSqlDatabase::addDatabase("QSQLITE");
    PMVBdd.setDatabaseName(sqlPath);

    QSqlQuery sqlQuery(PMVBdd);

    if(!PMVBdd.open()) {
        qDebug() << "Unable to open database" << endl;
    } else {
        qDebug() << "Opened database" << endl;
    }

}

CBdd::~CBdd()
{
}

bool CBdd::isSessionActive(QString sessionName) {
    sqlQuery.prepare("SELECT * FROM Session WHERE Nom_Session = :Nom_Session;");
    sqlQuery.bindValue(":Nom_Session", sessionName);
    sqlQuery.exec();

    bool isSessionFound = sqlQuery.size() == 1;
    return isSessionFound;
}

void CBdd::setSessionActive(bool s) {

}

void CBdd::setSessionName(QString sessionName) {
    sqlQuery.prepare("INSERT INTO Session (:id, :Nom_Session)");
    sqlQuery.bindValue(":id", 1);
    sqlQuery.bindValue(":Nom_Session", sessionName);
    sqlQuery.exec();
}

void CBdd::getSession(T_SESSION &data) {
}

void CBdd::setListeEleves(QList<QString> liste) {
    sqlQuery.prepare("UPDATE Eleves SET (:id, :Nom, :Prenom)");

    sqlQuery.bindValue(":id", index);
    sqlQuery.bindValue(":Nom", name);
    sqlQuery.bindValue(":Prenom", firstname);
    sqlQuery.exec();
}

void CBdd::setCoureurAuDepart(QString name, int ligne, int couloir) {

}

void CBdd::on_valeursCoureur(QString resTemps, QString resVitesse, QString id, QString vent){
    sqlQuery.prepare("INSERT INTO Coureurs (Temps, Vent, Vitesse)"
                     "VALUES (:Temps, :Vent, :Vitesse);"
                     "WHERE \"ID_Coureurs\" = \"" + id + "\" ;");
    sqlQuery.bindValue(":Temps", resTemps);
    sqlQuery.bindValue(":Vitesse", resVitesse);
    sqlQuery.bindValue(":Vent", vent);
    sqlQuery.exec();
}

void CBdd::on_elevesRcv(QString eleves) {

}

bool CBdd::verifConnection(QString Login, QString Pass) {

        /* Récupération du nombre de lignbe correspondant dans la BDD */

    sqlQuery.prepare("SELECT * FROM Authentification WHERE Login = :Login AND Password = :Password;");
    sqlQuery.bindValue(":Login", Login);
    sqlQuery.bindValue(":Password", Pass);
    sqlQuery.exec();

        /* Vérification de la présence de la ligne correspondante dans la BDD */

    bool isUserFound = sqlQuery.size() == 1;
        return isUserFound;
}
