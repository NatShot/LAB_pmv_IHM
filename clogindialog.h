#ifndef CLOGINDIALOG_H
#define CLOGINDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <stdio.h>
#include <stdlib.h>

namespace Ui {
class CLoginDialog;
}

class CLoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CLoginDialog(QWidget *parent = nullptr);
    ~CLoginDialog();

private:
    Ui::CLoginDialog *ui;
    int cpt;
    bool bascule;

signals:
    void sig_badPassword();

private slots:
    void on_pbValider_clicked();
    void on_leId_returnPressed();
    void on_leMdp_returnPressed();
    void on_pbAnnuler_clicked();

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // CLOGINDIALOG_H
