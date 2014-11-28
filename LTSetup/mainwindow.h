#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void slot_versionupdate(QString version_label, int version_num);

private slots:
    void on_btn_genfile_clicked();

    void on_cb_crontab_toggled(bool checked);

    void on_btn_versionsel_clicked();

private:
    //static int current_version;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
