#include "versiondialog.h"
#include "ui_versiondialog.h"
#include "common.h"

VersionDialog::VersionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VersionDialog)
{
    ui->setupUi(this);
}

VersionDialog::~VersionDialog()
{
    delete ui;
}


void VersionDialog::on_pushButton_clicked()
{
        versionnum = ui->combox_version->currentText();

        this->close();
}
