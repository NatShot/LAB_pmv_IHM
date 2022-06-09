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
} // CLoginDialog


CLoginDialog::~CLoginDialog()
{
    delete ui;
} // ~CLoginDialog


void CLoginDialog::on_pbValider_clicked()
{
    if(ui->leId->text().isEmpty() || ui->leMdp->text().isEmpty())
        {
            if(cpt < 2)
            {
                cpt ++;
                QMessageBox::critical(this,"ERREUR","Les champs d'authentifications ne peuvent pas être vides!");
            }else{
                bascule = false;
                emit sig_badPassword();
            }
    }else{
        emit sig_checkCredentials(ui->leId->text(), ui->leMdp->text());
    }
} // on_pbValider_clicked


void CLoginDialog::on_leId_returnPressed()
{
    ui->leMdp->setFocus();
} // on_leId_returnPressed


void CLoginDialog::on_leMdp_returnPressed()
{
    on_pbValider_clicked();
} // on_leMdp_returnPressed


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

void CLoginDialog::on_credentials(bool state)
{
    if(state)
    {
        bascule = state;
        this->close();
    }
    else
    {
        if(cpt < 2)
        {
            cpt ++;
            QMessageBox::critical(this,"ERREUR","Identifiant ou mot de passe incorrect.");
        }else{
            bascule = state;
            emit sig_badPassword();
        }
    }
}

