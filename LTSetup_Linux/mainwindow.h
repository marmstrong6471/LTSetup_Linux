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

    void on_cb_nbdswap_toggled(bool checked);

    void on_cb_localapp_toggled(bool checked);

    void on_cb_scripts_toggled(bool checked);

    void on_com_printertype_currentIndexChanged(int index);

    void on_cb_keyboard_toggled(bool checked);

    void on_cb_customxorg_toggled(bool checked);

    void on_cb_xserver_toggled(bool checked);

    void on_cb_xmouse_toggled(bool checked);

    void on_com_autologin_currentIndexChanged(int index);

    void on_sb_logtimeout_valueChanged(int arg1);

    void on_cb_localappsmenu_toggled(bool checked);

    void on_cb_whitelist_toggled(bool checked);

private:
    //static int current_version;
    Ui::MainWindow *ui;

    QString config_compile();
};

#endif // MAINWINDOW_H
