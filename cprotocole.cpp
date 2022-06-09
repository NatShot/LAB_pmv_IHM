#include "cprotocole.h"


CProtocole::CProtocole(QObject *parent) : QObject(parent)
{

}

CProtocole::~CProtocole()
{

}

QString CProtocole::prepareJsonTransfertRunner(int idCourse, QList<int> idRunners){
    QString json;
    json = addEnteteJson("transferRunner");
    json += addSectionJson("data");
    json += addParamIntJson("id", idCourse, 4);
    json += addParamTableauJson("runners", idRunners, 4, false);
    json += addPiedJson(2);
    return json;
} //prepareJsonTransferRunner

bool CProtocole::parseJsonTransferAllRunners(int *nbCoureurs, QList<T_COUREUR> *coureurs){

    return true;
}

bool CProtocole::parseJsonBtnState(QString trame, T_BTN_STATE *state){
    if(trame.indexOf("btnState") < 0)
        return false;
    QStringList elements = trame.split(','); //6 éléments
    state->btnSess = (elements[1].split(':')[2].indexOf('1') > 0 ? true : false);
    state->btnSess = (elements[2].split(':')[1].indexOf('1') > 0 ? true : false);
    state->btnAVM = (elements[3].split(':')[1].indexOf('1') > 0 ? true : false);
    state->btnReady = (elements[4].split(':')[1].indexOf('1') > 0 ? true : false);
    state->btnGo = (elements[5].split(':')[1].indexOf('1') > 0 ? true : false);
    return true;
} //parseJsonBtnState

bool CProtocole::parseJsonTimeRun(int *idCourse, T_TIMERUN *timeRun){
    return true;
} //parseJsonTimeRun

bool CProtocole::parseJsonTransferRunner(int *idCourse, QList<QString> *idRunners){
    return true;
} //parseJsonTransferRunner

bool CProtocole::parseJsonAuthCheck(QString trame, QString &login, QString &mdp){
    if(trame.indexOf("authCheck") < 0)
        return false;
    QStringList elements = trame.split(',');
    login = elements[1].split(':')[2].split('"')[1];
    mdp = elements[2].split(':')[1].split('"')[1];
    return true;
} //parseJsonAuthCheck

bool CProtocole::parseJsonGetCsv(QString trame){
    // Retourne -1 si incorrect sinon >= 0
    return trame.indexOf("getCsv");
} //parseJsonGetCsv

bool CProtocole::parseJsonGetControl(QString trame)
{
    return trame.indexOf("getControl");

} //parseJsonGetControl

QString CProtocole::prepareJsonTimeRun(int idCourse, T_TIMERUN timeRun){
    QString json;
    json = addEnteteJson("timeRun");
    json += addSectionJson("data");
    json += addParamTexteJson("id", QString::number(idCourse), 4);
    json += addParamTexteJson("time1", timeRun.time1, 4);
    json += addParamTexteJson("wind1", timeRun.wind1, 4);
    json += addParamTexteJson("speed1", timeRun.speed1, 4);
    json += addParamTexteJson("time2", timeRun.time2, 4);
    json += addParamTexteJson("wind2", timeRun.wind2, 4);
    json += addParamTexteJson("speed2", timeRun.speed2, 4, false);
    json += addPiedJson(2);
    return json;
} //prepareJsonTimeRun

QString CProtocole::prepareJsonTransfertCsv(int nbCoureurs, T_CSV *csv){
    QString json;
    json = addEnteteJson("transferCsv");
    json = addSectionJson("data");
    json += addParamTexteJson("runnersCnt", QString::number(nbCoureurs), 4);

    for(int i=0; i < nbCoureurs; i++){
        json += addSectionJson("runner" + QString::number(i+1), 4);
        json += addParamTexteJson("idRun", QString::number(csv[i].idRun), 6);
        json += addParamTexteJson("name", csv[i].name, 6);
        json += addParamTexteJson("time", csv[i].time, 6);
        json += addParamTexteJson("wind", csv[i].wind, 6);
        json += addParamTexteJson("speed", csv[i].speed, 6, false);
        json += addFinSectionJson(4, (i < (nbCoureurs - 1) ? true : false));
    } //for
    json += addPiedJson(2);
    return json;
} //prepareJsonTransfertCsv

QString CProtocole::prepareJsonAuthCheck(bool res, CBdd *bdd){
    QString json;
    json = addEnteteJson("authCheck");
    json += addSectionJson("data");
    if(bdd->isSessionActive(bdd->getSessionName())){
        json += addParamIntJson("success", (res ? 1 : 0 ), 4, false);
    }else{
        json += addParamIntJson("success", 2, 4, false);
    }
    json += addPiedJson(2);
    return json;
} //prepareJsonAuthCheck

QString CProtocole::prepareJsonTransfertAllRunners(QString sessionName, QList<QString> nomCoureurs)
{
    QString json;
    json = addEnteteJson("transfertAllRunners");
    json += addSectionJson("data");
    json += addParamTexteJson("sessionName", sessionName, false);
    json += addParamIntJson("runnersCnt", nomCoureurs.size(), 1);
    for (int i=0 ; i<nomCoureurs.size() ; i++) {
        json += addSectionJson("runner"+QString::number(i+1),4);
        json += addParamTexteJson("name", nomCoureurs.at(i), 1, false);
        json += addFinSectionJson(4, (i<(nomCoureurs.size()-1)?true:false));
    } // for i
    json += addPiedJson(2);
    return json;
} //prepareJsonTransfertAllRunners

QString CProtocole::prepareJsonBtnState(T_BTN_STATE state){
    QString json;
    json = addEnteteJson("btnState");
    json += addSectionJson("data");
    json += addParamTexteJson("btnSess", QString::number(state.btnSess), 4);
    json += addParamTexteJson("btnPrep", QString::number(state.btnPrep), 4);
    json += addParamTexteJson("btnAVM", QString::number(state.btnAVM), 4);
    json += addParamTexteJson("btnReady", QString::number(state.btnReady), 4);
    json += addParamTexteJson("btnGo", QString::number(state.btnGo), 4, false);
    json += addPiedJson(2);
    return json;
} //prepareJsonBtnState

QString CProtocole::prepareJsonGetControl()
{
    QString json;
    json = addEnteteJson("getControl", false);
    json += addPiedJson(1);
    return json;
} //prepareJsonGetControl

QString CProtocole::addEnteteJson(QString commande, bool suite){
    QString json;
    json.append("{\"command\": \"" + commande + "\"");
    if(suite)
        json.append(",");
    return json;
} //addEnteteJson

QString CProtocole::addPiedJson(int nb){
    QString json;
    if(nb > 0){
        for(int i = 0; i < nb; i++){
            json.append("}");
        }
    }
    return json;
} //addPiedJson

QString CProtocole::addSectionJson(QString nom, int dec){
    QString json;
    json.fill(' ', dec);
    json.append("\"" + nom + "\": {");
    return json;
} //addSectionJson

QString CProtocole::addFinSectionJson(int dec, int suite){
    QString json;
    json.fill(' ', dec);
    json.append("}");
    if(suite)
        json.append(",");
    return json;
} //addFinSectionJson

QString CProtocole::addParamTexteJson(QString nom, QString valeur, int dec, bool suite){
    QString json;
    json.fill(' ', dec);
    json.append("\"" + nom + "\": \"" + valeur + "\"");
    if(suite)
        json.append(',');
    return json;
} //addParamTexteJson

QString CProtocole::addParamIntJson(QString nom, int valeur, int dec, bool suite){
    QString json;
    json.fill(' ', dec);
    json.append("\"" + nom + "\": " + QString::number(valeur));
    if(suite)
        json.append(",");
    return json;
} //addParamIntJson

QString CProtocole::addParamTableauJson(QString nom, QList<int> valeur, int dec, bool suite){
    QString json;
    json.fill(' ', dec);
    json.append("\""+nom+"\": [");
    for (int i=0 ; i<valeur.size() ; i++) {
        json.fill(' ', dec+2);
        json.append(valeur.at(i));
        if (i < valeur.size()-1)
            json.append(",");
    } // for
    json.fill(' ', dec);
    json.append("]");
    if (suite)
        json.append(",");
    return json;
} //addParamTableauJson

QString CProtocole::filtreAvantParser(QString trame)
{
    int pos;
    do {
        pos = trame.indexOf("\r\n");
        if (pos >= 0)
            trame.remove(pos, 2);

    } while(pos >= 0);
    do {
        pos = trame.indexOf("\n");
        if (pos >= 0)
            trame.remove(pos, 1);
    } while(pos >= 0);
    do {
        pos = trame.indexOf("\r");
        if (pos >= 0)
            trame.remove(pos, 1);
    } while(pos >= 0);
    return trame;
}

void CProtocole::on_resVitesse(QString resVitesse, int ordre, int ligne)
{

}

void CProtocole::on_resTemps(QString resTemps, int ordre, int ligne)
{

} //filtreAvantParser
