#include "clogindialog.h"
#include "ui_clogindialog.h"

CLoginDialog::CLoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CLoginDialog)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Authentification");
    ui->pbAnnuler->setAutoDefault(false);
    ui->pbValider->setAutoDefault(false);
    cpt = 0;
    bascule = false;
    //_bdd = new CBdd();
}


CLoginDialog::~CLoginDialog()
{
    //delete _bdd;
    delete ui;
}


void CLoginDialog::on_pbValider_clicked()
{
    if(ui->leId->text().isEmpty() || ui->leMdp->text().isEmpty() || ui->leId->text() != "ID" || ui->leMdp->text() != "MDP")
    {
        if(cpt < 2)
        {
            cpt ++;
            QMessageBox::critical(this,"ERREUR","Identifiant ou mot de passe incorrect.");
        }
        else
        {
            bascule = false;
            emit sig_badPassword();
        }
    }else if(ui->leId->text() == "ID" && ui->leMdp->text() == "MDP")
    {
        bascule = true;
        this->close();
    }
}

//Nouvelle méthode qui fonctionne avec la vérif BDD

/*void CLoginDialog::on_pbValider_clicked(){

    QString ID = ui->leId->text();
    QString MDP = ui->leMdp->text();

    if(verifConnexion(ID, MDP) == True){
        bascule = true;
        this->close();
    }else{
        cpt++;
        if(cpt < 2)
            QMessageBox::critical(this,"ERREUR","Identifiant ou mot de passe incorrect.");
        else{
        bascule = false;
        emit sig_badPassword();
        }
    }
}*/


void CLoginDialog::on_leId_returnPressed()
{
    ui->leMdp->setFocus();
}


void CLoginDialog::on_leMdp_returnPressed()
{
    on_pbValider_clicked();
}


void CLoginDialog::closeEvent(QCloseEvent *event)
{
    if(bascule == false)
    {
        event->accept();
        exit(EXIT_FAILURE);
    }else
        event->accept();
}


void CLoginDialog::on_pbAnnuler_clicked()
{
    this->close();
}

