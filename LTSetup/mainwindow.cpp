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
    FileSystem fsys;

    QString filename = "./testfile.txt";

    fsys.file_wrapper(filename);

}
