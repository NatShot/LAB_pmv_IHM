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

    _sqlQuery->first();
    return (_sqlQuery->value(0).toString() == "1" ? true : false);
}

void CBdd::setSessionActive(bool s) {
    s=false;
}

void CBdd::setSessionName(QString sessionName) {
    clearSessionName();
    _sqlQuery->prepare("INSERT OR REPLACE INTO Session (ID_Session, Nom_Session) VALUES (:id, :Nom_Session);");
    _sqlQuery->bindValue(":id", 1);
    _sqlQuery->bindValue(":Nom_Session", sessionName);
    _sqlQuery->exec();
}

void CBdd::getSession(T_SESSION &data) {
}

void CBdd::setListeEleves(QList<QString> liste) {

    clearElevesList();
    qDebug() << "liste Eleves : " << liste;
    for(int i = 0; i < liste.size(); i++){ // Récupération du nombre de lignes dans la liste (NOM + Prénom sur une seule ligne)
        _name = liste.at(i).split(" ").at(0); // Découpage et séparation du NOM
        _firstname = liste.at(i).split(" ").at(1); // Découpage et séparation du PRÉNOM

        _sqlQuery->prepare("INSERT OR REPLACE INTO Eleves (ID_Eleves, Nom, Prenom) VALUES (:id, :Nom, :Prenom);");

        _sqlQuery->bindValue(":id", i+1);
        //qDebug() << "ID = " << i+1;

        _sqlQuery->bindValue(":Nom", _name);
        //qDebug() << "Nom = " << _name;

        _sqlQuery->bindValue(":Prenom", _firstname);
        //qDebug() << "Prénom = " << _firstname;

        _sqlQuery->exec();
        //qDebug() << "sqlQuery : " << _sqlQuery->executedQuery();
    }
}

QList<QString> CBdd::getListeEleves()
{
    /* Déclaration de la variable tampon */
    QList<QString> values;

    /* Récupération de la liste des Eleves */

    _sqlQuery->prepare("SELECT * FROM Eleves;");
    _sqlQuery->exec();

    /* Récupération du nombre de lignes */

    _sqlQuery->last();
    QString queryLast = _sqlQuery->value(0).toString();
    qDebug() << "Query size = " << queryLast;
    _sqlQuery->first();
    /* while(!end){
        values.append(_sqlQuery->value(cptr).toString());
        if(_sqlQuery->value(cptr).toString() == queryLast){
            end = true;
        }else{

        }
    } */

    for(int i = 0; i < queryLast.toInt(); i++){
        values.append(_sqlQuery->value(1).toString() + " " + _sqlQuery->value(2).toString());
        _sqlQuery->next();
    }

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

void CBdd::on_checkCredentials(QString login, QString pass)
{
    qDebug() << "Login: " << login;
    qDebug() << "Pass: " << pass;
    emit sig_credentials(verifConnection(login, pass));
}

void CBdd::on_sessionName(QString nomSession)
{
    setSessionName(nomSession);
}

bool CBdd::verifConnection(QString Login, QString Pass) {

        /* Récupération du nombre de lignbe correspondant dans la BDD */

    _sqlQuery->prepare("SELECT * FROM Authentification");
    _sqlQuery->bindValue(":Login", Login);
    _sqlQuery->bindValue(":Password", Pass);
    _sqlQuery->exec();
    qDebug() << _sqlQuery->lastError().text();
    qDebug() << Login;
    qDebug() << Pass;
    _sqlQuery->first();

        /* Vérification de la présence de la ligne correspondante dans la BDD */

    if(_sqlQuery->value(1).toString() == Login && _sqlQuery->value(2).toString() == Pass){
        qDebug() << "VERIF OK";
        return true;
    }
    else {
        return false;
    }
}

QString CBdd::getSessionName()
{

    _sqlQuery->prepare("SELECT Nom_Session FROM Session;");
    _sqlQuery->exec();

    _sqlQuery->first();
    QString value(_sqlQuery->value(0).toString());

    if(!value.isEmpty())
    {
        return value;
    }else {
        return "Unknown session.";
    }

}

void CBdd::clearElevesList()
{
    _sqlQuery->prepare("DELETE FROM Eleves;");
    _sqlQuery->exec();
}

void CBdd::clearSessionName()
{
    _sqlQuery->prepare("DELETE FROM Session;");
    _sqlQuery->exec();
}

