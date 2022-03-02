#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include <QLocale>
#include <QTranslator>
#include <QtDebug>
#include <QScreen>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    //centralization of window
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int x = (screenGeometry.width()-w.width()) / 2;
    int y = (screenGeometry.height()-w.height()) / 2;
    w.move(x, y);

    w.show();
    return a.exec();
}
