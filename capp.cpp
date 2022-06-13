#include "capp.h"

CApp::CApp()
{
    /* Initialisation des capteurs de passage */
    _capteurPassage1 = new CCapteurPassage(nullptr, 17, 1);
    _capteurPassage2 = new CCapteurPassage(nullptr, 27, 2);

    /* Initialisation des objets de communications
     * avec la tablette */
    _zdc = new CZdc();
    _bdd = new CBdd();
    _serv = new CServeur(_bdd);

    /* Initialisation de la signalisation */
    _th = new QThread();
    _sign = new CSignalisation();
    _sign->moveToThread(_th);

    /* Connexion des signaux de contrôle de la tablette */
    connect(this, &CApp::sig_srvGetControl, _serv, &CServeur::on_srvGetControl);
    connect(_serv, &CServeur::sig_srvRemoteGetControl, this, &CApp::on_srvRemoteGetControl);

    /* Connexion et lancement des signaux du thread */
    connect(_th, &QThread::finished, _sign, &QObject::deleteLater);
    connect(this, &CApp::sig_workerThread, _sign, &CSignalisation::on_goTravail);
    connect(this, &CApp::sig_checkCredentials, _bdd, &CBdd::on_checkCredentials);
    connect(_bdd, &CBdd::sig_credentials, this, &CApp::on_credentials);
    connect(this, &CApp::sig_sessionName, _bdd, &CBdd::on_sessionName);
    _th->start();


    /* Initialisation de la variable de numérotation de course */
    _ligne = -1;

}

CApp::~CApp()
{
    delete _sign;
    delete _zdc;
    _th->quit();
    _th->wait();
    delete _serv;
    delete _bdd;
    delete _capteurPassage2;
    delete _capteurPassage1;
}


void CApp::on_timerStart()
{
    _ligne++;

    _dt1 = QDateTime::currentDateTime();
    connect(_capteurPassage1, &CCapteurPassage::sig_coureurArrived, this, &CApp::on_timerStop);
    connect(_capteurPassage2, &CCapteurPassage::sig_coureurArrived, this, &CApp::on_timerStop);
}

void CApp::on_timerStop(int ordre, QDateTime dt2)
{
    CCapteurPassage *cp = static_cast<CCapteurPassage *>(sender());
    calculateTime(dt2, ordre);
    disconnect(cp, &CCapteurPassage::sig_coureurArrived, this, &CApp::on_timerStop);
    // si les deux sont arrivés alors fin de course
    if ( _zdc->getCoureurArrived(1) && _zdc->getCoureurArrived(2)) {
        // TODO
    } // 2 arrived


}

void CApp::calculateSpeed(int ordre)
{
    double deltaTs = _deltaTs;
    double deltaTms = _deltaTms;

    if(_deltaTm > 0)
        deltaTs += 60; //Si la course dure plus d'1 min, on rajoute 60s au delta T qui représente que les secondes
    deltaTs = deltaTs + (deltaTms / 1000);

    double Calcul = 50.0 / deltaTs * 3.6;
    _zdc->setVitesse(ordre, Calcul);
    // TODO sauver Calcul dans la bdd
    QString resultatVitesse = QString::number(Calcul, 'g', 2);
    emit sig_resVitesse(resultatVitesse, ordre, _ligne);
}

void CApp::calculateTime(QDateTime dt2, int ordre)
{
    _deltaTms = static_cast<quint64> (_dt1.msecsTo(dt2));
    _zdc->setTemps(ordre, _deltaTms);
    // sauver _deltaTms dans la bdd
    _deltaTm = _deltaTms / 60000;
    _deltaTs = (_deltaTms % 60000) / 1000;
    _deltaTms = (_deltaTms % 60000) % 1000;
    calculateSpeed(ordre);

    QString resultatTemps = QString::number(_deltaTm) + " : " + QString::number(_deltaTs) +" : " + QString::number(_deltaTms);
    emit sig_resTemps(resultatTemps, ordre, _ligne);
}

void CApp::on_runnersImport(QStringList nomEleves){
    _bdd->setListeEleves(static_cast<QList<QString>>(nomEleves));
}

void CApp::on_getControl()
{
    emit sig_srvGetControl();
}

void CApp::on_srvRemoteGetControl()
{
    emit sig_appRemoteGetControl();
}

void CApp::on_workerThread(){
    emit sig_workerThread();
}

void CApp::on_checkCredentials(QString login, QString pass)
{
    emit sig_checkCredentials(login, pass);
}

void CApp::on_credentials(bool state)
{
    emit CApp::sig_credentials(state);
}

void CApp::on_nomSession(QString nomSession)
{
    emit sig_sessionName(nomSession);
}

