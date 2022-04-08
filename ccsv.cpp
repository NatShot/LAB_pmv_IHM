#include "ccsv.h"
#include "cihm.h"

#include <iostream>
#include <fstream>

CCsv::CCsv(QObject *parent) : QObject(parent)
{

}

void CCsv::on_importCSV(QString path)
{
    _file.setFileName(path);
    _file.open(QIODevice::ReadOnly);
    while(!_file.atEnd()){
        QString name = _file.readLine();
        name = name.remove("\n");
        _nomsEleves.append(name);
    }
    _file.close();
    emit sig_afficherNomsEleves(_nomsEleves);
}

void CCsv::on_QFileDialog4Path()
{
    QFileDialog myDialog;
    QString path = myDialog.getOpenFileName();

    connect(this, &CCsv::sig_PathFile, this, &CCsv::on_importCSV);
    emit sig_PathFile(path);
}

void CCsv::on_exportCSV()
{

}










