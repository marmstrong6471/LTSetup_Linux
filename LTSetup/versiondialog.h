#ifndef VERSIONDIALOG_H
#define VERSIONDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class VersionDialog;
}

class VersionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VersionDialog(QWidget *parent = 0);
    ~VersionDialog();

private slots:

    void on_pushButton_clicked();

private:
    Ui::VersionDialog *ui;
};

#endif // VERSIONDIALOG_H
