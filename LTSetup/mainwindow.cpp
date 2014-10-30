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

void MainWindow::on_btn_versionsel_clicked()
{
   ui->lb_version->setText(versionnum);
   VersionDialog versiondialog;
   versiondialog.setModal(true);
   versiondialog.exec();

}
