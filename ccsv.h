#ifndef CCSV_H
#define CCSV_H

#include <QObject>
#include <QFile>
#include <QFileDialog>
#include <QTableWidget>
#include <QTextStream>
#include <QStringList>

#define DELIMITER ";"

class CCsv : public QObject
{
    Q_OBJECT
public:
    explicit CCsv(QObject *parent = nullptr);
    void on_exportCSV();

signals:
    void sig_PathFile(QString path);
    void sig_afficherNomsEleves(QStringList nomsEleves);

public slots:
    void on_importCSV(QString path);
    void on_QFileDialog4Path();

private:
    QFile _file;
    QStringList _nomsEleves;

};

#endif // CCSV_H
