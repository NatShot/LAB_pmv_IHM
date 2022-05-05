#include "cbdd.h"
#include "ui_cbdd.h"

using namespace std;
CBdd::CBdd(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::CBdd)
{
    ui->setupUi(this);

    PMVBdd = QSqlDatabase::addDatabase("QSQLITE");
    PMVBdd.setDatabaseName(sqlPath);

    QSqlQuery sqlQuery(PMVBdd);

    if(!PMVBdd.open()) {
        cout << "Unable to open database" << endl;
    } else {
        cout << "Opened database" << endl;
    }

}

CBdd::~CBdd()
{
    delete ui;
}

bool CBdd::isSessionActive() {
    if (startSession == 1) {
        isSessionActive = true;
    } else {
        isSessionActive = false;
    }
}

void CBdd::setSessionActive(bool s) {

}

void CBdd::setSessionName(QString sessionName) {
    sqlQuery.prepare("UPDATE Session SET (:id, :Nom_Session)");
    sqlQuery.bindValue(":id", 1);
    sqlQuery.bindValue(":Nom_Session", sessionName);
    sqlQuery.exec();
}

void CBdd::getSession(T_SESSION &data) {

}

void CBdd::setListeEleves(QStringList liste) {
    sqlQuery.prepare("UPDATE Eleves SET (:id, :Nom, :Prenom)");

    sqlQuery.bindValue(":id", index);
    sqlQuery.bindValue(":Nom", name);
    sqlQuery.bindValue(":Prenom", firstname);
    sqlQuery.exec();
}

void CBdd::setCoureurAuDepart(QString name, int ligne, int couloir) {

}

void CBdd::setValeursCoureur(int couloir, int ligne, QString resTemps, QString resVitesse, QString vent) {
        sqlQuery.prepare("UPDATE Coureurs SET (ID_Coureurs, ID_Course, Nom, Prenom, Temps, Vent, Vitesse)"
                         "VALUES (:ID_Coureurs, :ID_Course, :Nom, :Prenom, :Temps, :Vent, :Vitesse);");


        //si ordre = 0 alors, affecte les valeurs au coureur gauche
        //si ordre = 1 alors, affecte les valeurs au coureur droit
}

void CBdd::on_elevesRcv(QString eleves) {

}

void CBdd::on_resTemps(QString resTemps) {
    sqlQuery.prepare("INSERT INTO Coureurs (ID_coureurs, ID_Course, Nom, Prenom, Temps, Vent, Vitesse)"
                     "VALUES (:ID_Coureurs, :ID_Course, :Nom, :Prenom, :Temps, :Vent, :Vitesse);");
    sqlQuery.bindValue(":Temps", resTemps);
    sqlQuery.exec();
}

void CBdd::on_resVent(QString resVent) {
    sqlQuery.prepare("INSERT INTO Coureurs (ID_Coureurs, ID_Course, Nom, Prenom, Temps, Vent, Vitesse)"
                     "VALUES (:ID_Coureurs, :ID_Course, :Nom, :Prenom, :Temps, :Vent, :Vitesse);");
    sqlQuery.bindValue(":Vent", resVent);
    sqlQuery.exec();
}

void CBdd::on_resVitesse(QString resVitesse) {
    sqlQuery.prepare("INSERT INTO Coureurs (ID_Coureurs, ID_Course, Nom, Prenom, Temps, Vent, Vitesse)"
                     "VALUES (:ID_Coureurs, :ID_Course, :Nom, :Prenom, :Temps, :Vent, :Vitesse);");
    sqlQuery.bindValue(":Vitesse", resVitesse);
    sqlQuery.exec();
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
