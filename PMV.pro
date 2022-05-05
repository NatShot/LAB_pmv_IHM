QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT +=

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    biblis/cgpio.cpp \
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
    csignalisation.cpp

HEADERS += \
    biblis/cgpio.h \
    capp.h \
    cbdd.h \
    ccapteurpassage.h \
    cgererclient.h \
    cihm.h \
    clogindialog.h \
    ccsv.h \
    cprotocole.h \
    cserveur.h \
    csignalisation.h \
    czdc.h

FORMS += \
    cihm.ui \
    clogindialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
