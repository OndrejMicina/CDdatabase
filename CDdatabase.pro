QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    album.cpp \
    clickablelabel.cpp \
    customlistwidget.cpp \
    databasemanager.cpp \
    main.cpp \
    mainwindow.cpp \
    newalbumdialog.cpp

HEADERS += \
    album.h \
    clickablelabel.h \
    customlistwidget.h \
    databasemanager.h \
    mainwindow.h \
    newalbumdialog.h

FORMS += \
    customlistwidget.ui \
    mainwindow.ui \
    newalbumdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
