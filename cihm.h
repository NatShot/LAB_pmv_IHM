#ifndef CIHM_H
#define CIHM_H

#include <QMainWindow>
#include <QHeaderView>
#include <QMessageBox>
#include <QInputDialog>
#include <QDateTime>
#include <QTableWidget>
#include <QThread>

#include "clogindialog.h"
#include "capp.h"
#include "ccsv.h"
#include "czdc.h"
#include "csignalisation.h"

//Include commandes système
#include <unistd.h>
#include <sys/reboot.h>
#include <sys/socket.h>
//
#include <QComboBox>
#include <QList>
#include <QStringList>

#define DELIMITER ";"

QT_BEGIN_NAMESPACE
namespace Ui { class CIhm; }
QT_END_NAMESPACE

class CIhm : public QMainWindow
{
    Q_OBJECT

public:
    CIhm(QWidget *parent = nullptr);
    ~CIhm();

private slots:
    void on_pbPreparation_clicked();
    void on_pbAvm_clicked();
    void on_pbPret_clicked();
    void on_pbPartez_clicked();
    void on_pbStop_clicked();
    void on_pbStart_clicked();// Start la session => Devient Stop la session
    void on_tableWidget_cellClicked(int row, int column);
    void on_reboot();
    void on_shutdown();
    void on_quitterApp();
    void on_afficherResTemps(QString resultat, int ordre, int ligne);
    void on_afficherResVitesse(QString resultat, int ordre, int ligne);
    void on_afficherNomsEleves(QStringList nomsEleves);
    void on_exportCsv();
    void on_btnState(char boutons);


    void on_pbControl_clicked();

signals:
    void sig_timerStart();
    void sig_coucou();
    void sig_runnersImport(QStringList nomEleves);
    void sig_getControl();
    void sig_nomSession(QString nomSession);
    void sig_toWorkerThread();
    void sig_ihmGetControl();

public slots:
    void on_badPassword();
    void on_appRemoteGetControl();
    void on_newBtnState(T_BUTTONS buttons);
    void on_stopRun();

private:
    Ui::CIhm *ui;
    CZdc *_zdc;
    void idPage();
    void mdpPage();
    int cpt1;
    int cpt2;
    CLoginDialog *_loginDialog;
    CApp *_app;
    CCsv *_csv;
    QList<QComboBox *> _combos;
    QStringList _nom;
    QStringList _temps;
    QStringList _vitesse;
    QStringList _vent;
    QList<QString> ListTpm;
    int _security = 0;
    T_BUTTONS _buttons;
};
#endif // CIHM_H
