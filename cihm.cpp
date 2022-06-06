#include "cihm.h"
#include "ui_cihm.h"

CIhm::CIhm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CIhm)
{
    //loginDialog
    _loginDialog = new CLoginDialog();
    connect(_loginDialog,&CLoginDialog::sig_badPassword,this,&CIhm::on_badPassword);
    _loginDialog->exec();
    //

    ui->setupUi(this);

    //Tableau de valeurs (en responsive)+ ComboBox des coureurs après import CSV
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for(int i = 0; i < 40; i++){
        _combos.append(new QComboBox);
    }

    for(int i = 0; i < _combos.count(); i++){
        if(i % 2 == 0){
            ui->tableWidget->setCellWidget(i / 2, 0, _combos.at(i));
        }else{
            ui->tableWidget->setCellWidget(i /2, 4, _combos.at(i));
        }
    }

    //Instanciation des objets
    _zdc = new CZdc();
    _app = new CApp();
    _csv = new CCsv();
    _th = new QThread();
    _sign = new CSignalisation();
    _sign->moveToThread(_th);
    //

    //emit sig_workerThread();
    //

    //Démarrage de la course
    connect(this,&CIhm::sig_timerStart,_app, &CApp::on_timerStart);
    //

    //Execution commandes système
    connect(ui->actionRedemarrage,&QAction::triggered,this,&CIhm::on_reboot);
    connect(ui->actionArreter, &QAction::triggered, this, &CIhm::on_shutdown);
    connect(ui->actionQuitter, &QAction::triggered, this, &CIhm::on_quitterApp);
    //

    //Execution des commandes CSV
    connect(ui->actionImport_CSV,&QAction::triggered,_csv, &CCsv::on_QFileDialog4Path);
    connect(_csv, &CCsv::sig_afficherNomsEleves, this, &CIhm::on_afficherNomsEleves);
    connect(ui->actionExportCSV, &QAction::triggered, this, &CIhm::on_exportCsv);

    //Boutons au démarrage
    ui->pbPreparation->setDisabled(true);
    ui->pbAvm->setDisabled(true);
    ui->pbPret->setDisabled(true);
    ui->pbPartez->setDisabled(true);
    ui->pbStop->setDisabled(true);
    //

    //Lancement du Thread
    //connect Thread
    connect(_th, &QThread::finished, _sign, &QObject::deleteLater);
    connect(this, &CIhm::sig_workerThread, _sign, &CSignalisation::on_goTravail);
    _th->start();
    //


    //Connects a l'arrache
    connect(this, &CIhm::sig_runnersImport, _app, &CApp::on_runnersImport);
    connect(ui->actionGetControl, &QAction::triggered, _app, &CApp::on_getControl);
    //
}

CIhm::~CIhm()
{
    for(int i = 0; i < _combos.count(); i++){
        delete _combos.at(i);
    }
    _combos.clear();
    delete _sign;
    _th->quit();
    _th->wait();
    delete _csv;
    delete _app;
    delete _loginDialog;
    delete _zdc;
    delete ui;
}

            //----BOUTONS----//
void CIhm::on_pbPreparation_clicked()
{
    T_DATAS datas;
    datas.activeSignalisation = true;
    datas.modeDeFonctionnement = RAPIDE;
    _zdc->sauveDatas(datas);

    ui->pbAvm->setEnabled(true);
    emit sig_workerThread();
}


void CIhm::on_pbAvm_clicked()
{
    T_DATAS datas;
    datas.activeSignalisation = true;
    datas.modeDeFonctionnement = LENT;
    _zdc->sauveDatas(datas);

    ui->pbPret->setEnabled(true);
}


void CIhm::on_pbPret_clicked()
{
    T_DATAS datas;
    datas.activeSignalisation = true;
    datas.modeDeFonctionnement = ETEINT;
    _zdc->sauveDatas(datas);

    ui->pbPartez->setEnabled(true);
    ui->pbPreparation->setDisabled(true);
}


void CIhm::on_pbPartez_clicked()
{
    T_DATAS datas;
    datas.activeSignalisation = false;
    datas.modeDeFonctionnement = FIXE;
    //datas.tempo = 5000;
    _zdc->sauveDatas(datas);
    //emit sig_workerThread();

    ui->pbPreparation->setDisabled(true);
    ui->pbAvm->setDisabled(true);
    ui->pbPret->setDisabled(true);
    ui->pbPartez->setDisabled(true);
    ui->pbStop->setEnabled(true);

    connect(_app, &CApp::sig_resTemps, this, &CIhm::on_afficherResTemps);
    connect(_app, &CApp::sig_resVitesse, this, &CIhm::on_afficherResVitesse);

    emit sig_timerStart();
}


void CIhm::on_pbStop_clicked()
{
    T_DATAS datas;
    datas.activeSignalisation = false;
    datas.modeDeFonctionnement = ETEINT;
    _zdc->sauveDatas(datas);

    ui->pbPreparation->setEnabled(true);
    ui->pbStop->setDisabled(true);
}


void CIhm::on_pbStart_clicked()
{
    if(ui->pbStart->text()=="START")
    {
        QMessageBox msgBox;
        msgBox.setText("Voulez-vous lancer une nouvelle session?");
        msgBox.setInformativeText("Le nom de la session ne pourra plus être modifié");
        msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::No);
        int reponse = msgBox.exec();
        if(reponse == QMessageBox::No){}
        else
        {
            ui->pbStart->setText("STOP");
            ui->pbPreparation->setEnabled(true);
            ui->leNomSession->setReadOnly(true);
            //Start la session;
        }
     }//IF START

    else
    {
        QMessageBox msgBox;
        msgBox.setText("Voulez-vous arreter la session en cours?");
        msgBox.setInformativeText("Pensez à EXPORTER la session");
        msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::No);
        int reponse = msgBox.exec();
        if(reponse == QMessageBox::No){}
        else
        {
            ui->pbStart->setText("START");
            ui->pbPreparation->setDisabled(true);
            ui->pbAvm->setDisabled(true);
            ui->pbPret->setDisabled(true);
            ui->pbPartez->setDisabled(true);
            ui->leNomSession->setReadOnly(false);
            //Stop la session;
        }
    }//IF STOP
}

void CIhm::on_btnState(char boutons)
{
    switch(boutons)
    {
    case 1:
        on_pbStart_clicked();
        break;
    case 2:
        on_pbPreparation_clicked();
        break;
    case 4:
        on_pbAvm_clicked();
        break;
    case 8:
        on_pbPret_clicked();
        break;
    case 16:
        on_pbPartez_clicked();
        break;
    case 32:
        on_pbStop_clicked();
        break;
    default:
        break;
    }
}
            //----BOUTONS----//

                        //

            //----BARRE DE MENU----//

void CIhm::on_quitterApp()
{
     QMessageBox msgBox;
     msgBox.setText("Voulez-vous quitter l'application?");
     msgBox.setInformativeText("Pensez à STOPPER et EXPORTER la session");
     msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
     msgBox.setDefaultButton(QMessageBox::No);
     int reponse = msgBox.exec();
     if(reponse == QMessageBox::No){
     }else
         QCoreApplication::quit();
}


void CIhm::on_tableWidget_cellClicked(int row, int column)
{

}

void CIhm::on_reboot()
{
    QMessageBox msgBox;
    msgBox.setText("Voulez-vous redémarrer l'appareil??");
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::No);
    int reponse = msgBox.exec();
    if(reponse == QMessageBox::No){}
    else
    {
    system("/usr/bin/systemctl reboot");
    }
}


void CIhm::on_shutdown()
{
    QMessageBox msgBox;
    msgBox.setText("Voulez-vous éteindre l'appareil??");
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::No);
    int reponse = msgBox.exec();
    if(reponse == QMessageBox::No){}
    else
    {
    system("sudo shutdown -h now");
    }
}
            //----BARRE DE MENU----//

                        //

            //----AFFICHAGE IHM----//
void CIhm::on_afficherResTemps(QString resultatTemps, int ordre, int ligne)
{
    if(ordre == 1){
        ui->tableWidget->setItem(ligne,1,new QTableWidgetItem(resultatTemps));
        ui->tableWidget->item(ligne, 1)->setFlags(ui->tableWidget->item(ligne, 1)->flags() ^ Qt::ItemIsEditable ^ Qt::ItemIsSelectable);
    }else{
        ui->tableWidget->setItem(ligne,5,new QTableWidgetItem(resultatTemps));
        ui->tableWidget->item(ligne, 5)->setFlags(ui->tableWidget->item(ligne, 5)->flags() ^ Qt::ItemIsEditable ^ Qt::ItemIsSelectable);
    }
}

void CIhm::on_afficherResVitesse(QString resultatVitesse, int ordre, int ligne)
{
    if(ordre == 1){
        ui->tableWidget->setItem(ligne,2,new QTableWidgetItem(resultatVitesse));
        ui->tableWidget->item(ligne, 2)->setFlags(ui->tableWidget->item(ligne, 2)->flags() ^ Qt::ItemIsEditable ^ Qt::ItemIsSelectable);
    }else{
        ui->tableWidget->setItem(ligne,6,new QTableWidgetItem(resultatVitesse));
        ui->tableWidget->item(ligne, 6)->setFlags(ui->tableWidget->item(ligne, 6)->flags() ^ Qt::ItemIsEditable ^ Qt::ItemIsSelectable);
    }
}

void CIhm::on_afficherNomsEleves(QStringList _nomsEleves)
{
    for(int i = 0; i < _combos.count(); i++){
        _combos.at(i)->clear();
        _combos.at(i)->addItems(_nomsEleves);
        _combos.at(i)->update();
    }
    emit sig_runnersImport(_nomsEleves);
}

void CIhm::on_exportCsv()
{

}



            //----AFFICHAGE IHM----//




void CIhm::on_badPassword()
{
    QMessageBox::critical(this,"ERREUR","Echec de la connexion après 3 tentatives.\nFermeture de l'application.");
    exit(EXIT_FAILURE);
}

