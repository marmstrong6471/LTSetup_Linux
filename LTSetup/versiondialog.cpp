#include "versiondialog.h"
#include "ui_versiondialog.h"
#include "common.h"
#include "mainwindow.h"

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
        //versionnum = ui->combox_version->currentText();
        //emit version_out(ui->combox_version->currentText());

        //emit version_out(ui->combox_version->currentText(), ui->combox_version->currentIndex());
        switch(ui->combox_version->currentIndex())
        {
            case 0:
                emit version_out("Ubuntu 10.04 LTS (Lucid Lynx)", 1004);
                break;
            case 1:
                emit version_out("Ubuntu 10.10 (Maverick Meerkat)", 1010);
                break;
            case 2:
                emit version_out("Ubuntu 11.04 (Natty Narwhal)", 1104);
                break;
            case 3:
                emit version_out("Ubuntu 11.10 (Oneiric Ocelot)", 1110);
                break;
            case 4:
                emit version_out("Ubuntu 12.04 LTS (Precise Pangolin)", 1204);
                break;
            case 5:
                emit version_out("Ubuntu 12.10 (Quantal Quetzal)", 1210);
                break;
            case 6:
                emit version_out("Ubuntu 13.04 (Raring Ringtail)", 1304);
                break;
            case 7:
                emit version_out("Ubuntu 13.10 (Saucy Salamander)", 1310);
                break;
            case 8:
                emit version_out("Ubuntu 14.04 LTS (Trusty Tahr)", 1404);
                break;
            case 9:
                emit version_out("Ubuntu 14.10 (Utopic Unicorn)", 1410);
                break;

            default:
                emit version_out("ERROR - Invalid value, select version again", 0000);
        }
        accept();

}
