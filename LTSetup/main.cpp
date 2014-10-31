#include "mainwindow.h"
#include <QApplication>
#include "common.h"
#include "versiondialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    VersionDialog v;
    v.show();

    //QObject::connect(v.ui->pushButton, SIGNAL(clicked()), w, SLOT(show()));

    return a.exec();
}
