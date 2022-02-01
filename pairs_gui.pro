QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    card.cpp \
    gameboard.cpp \
    main.cpp \
    mainwindow.cpp \
    newgamedialog.cpp \
    player.cpp \
    playernamesdialog.cpp

HEADERS += \
    card.hh \
    gameboard.hh \
    mainwindow.hh \
    newgamedialog.hh \
    player.hh \
    playernamesdialog.hh

FORMS += \
    mainwindow.ui \
    newgamedialog.ui \
    playernamesdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/card.png \
    images/cat_1.png \
    images/cat_10.png \
    images/cat_11.png \
    images/cat_12.png \
    images/cat_2.png \
    images/cat_3.png \
    images/cat_4.png \
    images/cat_5.png \
    images/cat_6.png \
    images/cat_7.png \
    images/cat_8.png \
    images/cat_9.png \
    instructions.txt
