#include "cbdd.h"

using namespace std;
CBdd::CBdd(QObject *parent): QObject(parent)
{
    //PMVBdd = QSqlDatabase::addDatabase("QSQLITE", "PMVBdd_connect");
    _sqlPath = "/home/pi/Documents/PMVBdd";
    PMVBdd = QSqlDatabase::addDatabase("QSQLITE");
    PMVBdd.setDatabaseName(_sqlPath);
    if(!PMVBdd.open()) {
        qDebug() << "Unable to open database" << endl;
    } else {
        qDebug() << "Opened database" << endl;
    }
    _sqlQuery = new QSqlQuery(PMVBdd);
}

CBdd::~CBdd()
{
    delete _sqlQuery;
    PMVBdd.close();
}

bool CBdd::isSessionActive(QString sessionName) {
    _sqlQuery->prepare("SELECT * FROM Session WHERE Nom_Session = :Nom_Session;");
    _sqlQuery->bindValue(":Nom_Session", sessionName);
    _sqlQuery->exec();
    return (_sqlQuery->size() == 1);
}

void CBdd::setSessionActive(bool s) {
    s=false;
}

void CBdd::setSessionName(QString sessionName) {
    _sqlQuery->prepare("UPDATE Session (:id, :Nom_Session)");
    _sqlQuery->bindValue(":id", 1);
    _sqlQuery->bindValue(":Nom_Session", sessionName);
    _sqlQuery->exec();
}

void CBdd::getSession(T_SESSION &data) {
}

void CBdd::setListeEleves(QList<QString> liste) {

    qDebug() << "liste Eleves : " << liste;
    for(int i = 0; i < liste.count(); i++){
        _name = liste.at(i).split(" ").at(0);
        _firstname = liste.at(i).split(" ").at(1);
        _sqlQuery->prepare("UPDATE Eleves SET Nom = :Nom, Prenom = :Prenom WHERE ID_Eleves=:id;");
        _sqlQuery->bindValue(":id", i+1);
        _sqlQuery->bindValue(":Nom", _name);
        _sqlQuery->bindValue(":Prenom", QString(_firstname.left(1) + "."));
        _sqlQuery->exec();
    }
}

QList<QString> CBdd::getListeEleves()
{
    /* Récupération de la liste des Eleves */

    _sqlQuery->prepare("SELECT Nom, Prenom FROM Eleves;");
    _sqlQuery->exec();

    /* Récupération du nombre de lignes */

    QString lines(_sqlQuery->size());

    QList<QString> values;
    values.append(lines);

    return values;


}

void CBdd::setCoureurAuDepart(QString name, int ligne, int couloir) {

}

void CBdd::on_valeursCoureur(QString resTemps, QString resVitesse, QString id, QString vent){
    _sqlQuery->prepare("INSERT INTO Coureurs (Temps, Vent, Vitesse)"
                     "VALUES (:Temps, :Vent, :Vitesse)"
                     "WHERE \"ID_Coureurs\" = \"" + id + "\" ;");
    _sqlQuery->bindValue(":Temps", resTemps);
    _sqlQuery->bindValue(":Vitesse", resVitesse);
    _sqlQuery->bindValue(":Vent", vent);
    _sqlQuery->exec();
}

bool CBdd::verifConnection(QString Login, QString Pass) {

        /* Récupération du nombre de lignbe correspondant dans la BDD */

    _sqlQuery->prepare("SELECT * FROM Authentification WHERE Login = :Login AND Password = :Password;");
    _sqlQuery->bindValue(":Login", Login);
    _sqlQuery->bindValue(":Password", Pass);
    _sqlQuery->exec();

        /* Vérification de la présence de la ligne correspondante dans la BDD */

    bool isUserFound = _sqlQuery->size() == 1;
    return isUserFound;
}

QString CBdd::getSessionName()
{

    if(PMVBdd.isOpen())
    {
        _sqlQuery->prepare("SELECT Nom_Session FROM Session;");
        _sqlQuery->exec();


        _sqlQuery->first();
        QString value(_sqlQuery->value(0).toString());
        qDebug() << "Value of getSessionName : " << value;

        return value;
    }else {
        qDebug() << "BDD PAS OUVERTE!!!";
    }

}

