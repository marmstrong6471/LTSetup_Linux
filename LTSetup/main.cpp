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



    //QObject::connect(v.ui->pushButton, SIGNAL(version_out(QString)), w, SLOT(slot_versionupdate));

    if(version_select.exec() == QDialog::Accepted)
    {
        main_window.show();
    }

    return a.exec();
}
