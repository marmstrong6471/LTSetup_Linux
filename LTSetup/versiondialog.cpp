#include "versiondialog.h"
#include "ui_versiondialog.h"
#include "common.h"
#include "mainwindow.h"

VersionDialog::VersionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VersionDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(done(ui->combox_version->currentText())));
}

VersionDialog::~VersionDialog()
{
    delete ui;
}


void VersionDialog::on_pushButton_clicked()
{
        //versionnum = ui->combox_version->currentText();
        //emit version_out(ui->combox_version->currentText());


}
