#include <qdialog.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filesystem.h"
#include "versiondialog.h"
#include "common.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_genfile_clicked()
{
    FileSystem fsys;
    QString test_data = "Test test test";

    fsys.write_file(test_data);

}

void MainWindow::slot_versionupdate(QString version)
{
   ui->lb_version->setText(version);
   /*VersionDialog versiondialog;
   versiondialog.setModal(true);
   versiondialog.exec();*/

}

void MainWindow::on_cb_crontab_toggled(bool checked)
{
    if (checked)
    {
        QString tabname = "Crontab Lines";
        ui->tabWidget->insertTab(1, crontab_tab, tabname);

    }
    else if (!checked)
    {
        crontab_tab = ui->tabWidget->widget(1);
        ui->tabWidget->removeTab(1);
    }
}
