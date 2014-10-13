#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filesystem.h"

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
    filesystem fsys;

    QString filename = "./testfile.txt";

    filesystem::fsys.write_file(filename);
}
