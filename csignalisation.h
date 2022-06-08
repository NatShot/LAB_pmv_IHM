#ifndef CSIGNALISATION_H
#define CSIGNALISATION_H

#include <QObject>
#include "biblis/cgpio.h"
#include "czdc.h"

class CSignalisation : public QObject
{
    Q_OBJECT
public:
    explicit CSignalisation(QObject *parent = nullptr);
    ~CSignalisation();

public slots:
    void on_goTravail();

signals:
    void sig_threadRestart();

private:
    CGpio *_gpioRed;
    CGpio *_gpioGreen;
    CGpio *_gpioFan;
    CGpio *_gpioBuzzer;
    CZdc *_zdc;
};

#endif // CSIGNALISATION_H
