#include <qdialog.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filesystem.h"
#include "versiondialog.h"
#include "common.h"
#include <QObject>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    crontab_tab = ui->tabWidget->widget(1);
    ui->tabWidget->removeTab(1);
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

void MainWindow::slot_versionupdate(QString version_label, int version_num)
{
   ui->lb_version->setText(version_label);

   if(version_num <= 1404)
   {
        fstab_tab = ui->tabWidget->widget(3);
        ui->tabWidget->removeTab(3);
        ui->cb_fstab->setDisabled(true);
   }


   if(version_num >= 1404 && !(ui->cb_fstab->isEnabled()))
   {
       ui->cb_fstab->setEnabled(true);
   }

   if(version_num >= 1404 && fstab_tab != NULL)
   {
       ui->tabWidget->insertTab(3, fstab_tab, "Printer");
       fstab_tab = NULL;
   }

}

void MainWindow::on_cb_crontab_toggled(bool checked)
{
    if (checked)
    {
        QString tabname = "Crontab Lines";
        ui->tabWidget->insertTab(1, crontab_tab, tabname);
        crontab_tab = NULL;

    }
    else if (!checked)
    {
        crontab_tab = ui->tabWidget->widget(1);
        ui->tabWidget->removeTab(1);
    }
}

void MainWindow::on_btn_versionsel_clicked()
{
    VersionDialog ver_dialog;
    QObject::connect(&ver_dialog, SIGNAL(version_out(QString, int)), this, SLOT(slot_versionupdate(QString, int)));
    ver_dialog.exec();
}
