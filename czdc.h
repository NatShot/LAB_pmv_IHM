#ifndef CZDC_H
#define CZDC_H

#include <QObject>
#include <QSharedMemory>

typedef enum {
    ETEINT,
    FIXE,
    LENT,
    RAPIDE
} T_MODE_FEU;

typedef struct s_data {
    T_MODE_FEU modeDeFonctionnement;
    bool activeSignalisation;
    //int tempo;
} T_DATAS;

class CZdc : public QSharedMemory
{
    Q_OBJECT

public:
    CZdc(QObject *parent = nullptr);
    ~CZdc();
    void sauveDatas(T_DATAS &datas);
    void getDatas(T_DATAS &datas);

signals:
    void sig_newDatas();

private:
    T_DATAS *_datas;
};

#endif // CZDC_H
