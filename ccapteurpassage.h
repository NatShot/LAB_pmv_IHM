#ifndef CCAPTEURPASSAGE_H
#define CCAPTEURPASSAGE_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QDateTime>
#include "biblis/cgpio.h"


class CCapteurPassage : public QObject
{
    Q_OBJECT

public:
    explicit CCapteurPassage(QObject * parent = nullptr, int gpio = 17, int ordre = 1);
    ~CCapteurPassage();

private:
    QFileSystemWatcher _file;
    CGpio *_gpio;
    int _ordre;

signals:
    void sig_coureurArrived(int no, QDateTime dt2);

public slots:
    void on_filechanged();
};

#endif // CCAPTEURPASSAGE_H

