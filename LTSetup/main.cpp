#include "mainwindow.h"
#include <QApplication>
#include "common.h"
#include "versiondialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow main_window;
    VersionDialog version_select;
    //version_select.show();



    QObject::connect(&version_select, SIGNAL(version_out(QString, int)), &main_window, SLOT(slot_versionupdate(QString, int)));

    version_select.exec();
    main_window.show();

    return a.exec();
}
