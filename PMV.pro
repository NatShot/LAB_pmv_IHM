QT       += core gui widgets network sql

greaterThan(QT_MAJOR_VERSION, 4): QT +=

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    biblis/cgpio.cpp \
    biblis/ci2c.cpp \
    capp.cpp \
    cbdd.cpp \
    ccapteurpassage.cpp \
    cgererclient.cpp \
    clogindialog.cpp \
    cprotocole.cpp \
    cserveur.cpp \
    czdc.cpp \
    main.cpp \
    cihm.cpp \
    ccsv.cpp \
    csignalisation.cpp \
    canemometre.cpp

HEADERS += \
    biblis/cgpio.h \
    biblis/ci2c.h \
    capp.h \
    cbdd.h \
    ccapteurpassage.h \
    cgererclient.h \
    clogindialog.h \
    cprotocole.h \
    cserveur.h \
    czdc.h \
    ccsv.h \
    cihm.h \
    csignalisation.h \
    canemometre.h

FORMS += \
    cihm.ui \
    clogindialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
