QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QListViewExplorerModel.cpp \
    main.cpp \
    mainwindow.cpp \
    newfile.cpp

HEADERS += \
    QListViewExplorerModel.h \
    mainwindow.h \
    newfile.h

TRANSLATIONS += \
    file-manager_rus.ts \
    file-manager_en.ts

FORMS += \
    mainwindow.ui \
    newfile.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    file-manager_rus.qm \
    file-manager_rus.ts
