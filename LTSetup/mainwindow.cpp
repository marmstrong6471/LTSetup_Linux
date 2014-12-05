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
    scripts_tab = ui->tabWidget->widget(2);
    xorgoptions_tab = ui->tabWidget->widget(7);
    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(5);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_versionupdate(QString version_label, int version_num)
{
   ui->lb_version->setText(version_label);
   ver_persistent = version_num;

   if(version_num <= 1404)
   {
        //fstab_tab = ui->tabWidget->widget(3);
        //ui->tabWidget->removeTab(3);
        //ui->cb_fstab->setDisabled(true);
   }

    /*
   if(version_num >= 1404 && !(ui->cb_fstab->isEnabled()))
   {
       ui->cb_fstab->setEnabled(true);
   }


    if(version_num >= 1404 && fstab_tab != NULL)
   {
       ui->tabWidget->insertTab(3, fstab_tab, "Printer");
       fstab_tab = NULL;
   }
    */
}

inline QString bool_to_string(bool b)
{
    return b ? "True" : "False";
}

QString MainWindow::config_compile()
{
    QString config = "";

    config = "[General]\n";

    config  += "CONFIGURE_FSTAB=";

    config += bool_to_string(ui->cb_fstab->isChecked()) + "\n";

    if (ui->cb_crontab->isChecked())
    {
        QLineEdit* crontabs[] = {ui->txt_crontab_0, ui->txt_crontab_1, ui->txt_crontab_2, ui->txt_crontab_3, ui->txt_crontab_4, ui->txt_crontab_5, ui->txt_crontab_6, ui->txt_crontab_7, ui->txt_crontab_8, ui->txt_crontab_9};

        for(int i = 0; i < 10; i++)
        {
            if(crontabs[i]->text() != "")
            {
                if(i < 9)
                {
                    config += "CRONTAB_0" + QString::number(i+1);
                    config += "=" + crontabs[i]->text() + "\n";
                }
                else if(i == 9)
                {
                    config += "CRONTAB_" + QString::number(i+1);
                    config += "=" + crontabs[i]->text() + "\n";
                }
            }
        }
    }

    if(ui->txt_dnsserver->text() != "")
        config += "DNS_SERVER=" + ui->txt_dnsserver->text() + "\n";

    if(ui->txt_searchdomain->text() != "" && ui->txt_dnsserver->text() != "")
        config += "SEARCH_DOMAIN=" + ui->txt_searchdomain->text() + "\n";

    config += "LOCAL_APPS=" + bool_to_string(ui->cb_localapp->isChecked()) + "\n";

    if(ui->cb_localapp->isChecked() && ui->txt_localappextra->text() != "")
        config += "LOCAL_APPS_EXTRAMOUNTS=" + ui->txt_localappextra->text() + "\n";

    config += "LOCALDEV=" + bool_to_string(ui->cb_ldev->isChecked()) + "\n";

    config += "LOCALDEV_DENY_CD=" + bool_to_string(ui->cb_ldevdenycd->isChecked()) + "\n";

    config += "LOCALDEV_DENY_FLOPPY=" + bool_to_string(ui->cb_ldevdenyfloppy->isChecked()) + "\n";

    config += "LOCALDEV_DENY_INTERNAL_DISKS=" + bool_to_string(ui->cb_ldevdenyinternal->isChecked()) + "\n";

    config += "LOCALDEV_DENY_USB=" + bool_to_string(ui->cb_ldevdenyusb->isChecked()) + "\n";

    if(ui->txt_ldevdeny->text() != "")
        config += "LOCALDEV_DENY=" + ui->txt_ldevdeny->text() + "\n";

    config += "NBD_SWAP=" + bool_to_string(ui->cb_nbdswap->isChecked()) + "\n";

    if(ui->cb_nbdswap->isChecked())
    {
        config += "NBD_SWAP_PORT=";
        if(ui->txt_nbdswapport->text() != "")
        {
            config += ui->txt_nbdswapport->text() + "\n";
        }
        else if (ver_persistent < 1404)
        {
            config += "9572\n";
        }
        else
        {
            config += "10809\n";
        }
        config += "NBD_SWAP_SERVER=";
        if(ui->txt_nbdswapserver->text() != "")
        {
            config += ui->txt_nbdswapserver->text() + "\n";
        }
        else
        {
            config += "SERVER\n";
        }
    }

    if(ui->txt_server->text() != "")
    config += "SERVER=" + ui->txt_server->text() + "\n";

    if(ui->txt_sysloghost->text() != "")
    config += "SYSLOG_HOST=" + ui->txt_sysloghost->text() + "\n";

    config += "USE_LOCAL_SWAP=" + bool_to_string(ui->cb_localswap->isChecked()) + "\n";

    if (ui->cb_scripts->isChecked())
    {
        config += "\n[Scripts and Modules]\n";

        QLineEdit* scripts[] = {ui->txt_RC0, ui->txt_RC1, ui->txt_RC2, ui->txt_RC3, ui->txt_RC4, ui->txt_RC5, ui->txt_RC6, ui->txt_RC7, ui->txt_RC8, ui->txt_RC9};
        QLineEdit* modules[] = {ui->txt_mod0, ui->txt_mod1, ui->txt_mod2, ui->txt_mod3, ui->txt_mod4, ui->txt_mod5, ui->txt_mod6, ui->txt_mod7, ui->txt_mod8, ui->txt_mod9};

        for(int g = 0; g < 10; g++)
        {
            if(modules[g]->text() != "")
            {
                if(g < 9)
                {
                    config += "MODULE_0" + QString::number(g+1);
                    config += "=" + modules[g]->text() + "\n";
                }
                else if(g == 9)
                {
                    config += "MODULE_" + QString::number(g+1);
                    config += "=" + modules[g]->text() + "\n";
                }
            }
        }

        for(int h = 0; h < 10; h++)
        {
            if(scripts[h]->text() != "")
            {
                if(h < 9)
                {
                    config += "RCFILE_0" + QString::number(h+1);
                    config += "=" + scripts[h]->text() + "\n";
                }
                else if(h == 9)
                {
                    config += "RCFILE_" + QString::number(h+1);
                    config += "=" + scripts[h]->text() + "\n";
                }
            }
        }
    }

    config += "\n[Printer]\n";

    if(ui->txt_printerdevice->text() != "")
    {
        config += "PRINTER_0_DEVICE=" + ui->txt_printerdevice->text() + "\n";

        config += "PRINTER_0_PORT=";
        if (ui->txt_printerport->text() != "")
            config += ui->txt_printerport->text() + "\n";
        else
            config += "9100\n";

        if(ui->com_printertype->currentIndex() > 0)
        {
            config += "PRINTER_0_TYPE=";
            switch(ui->com_printertype->currentIndex())
            {
            case 1:
                config += "P\n";
                break;
            case 2:
                config += "U\n";
                break;
            case 3:
                config += "S\n";
                break;
            }
        }

        config += "PRINTER_0_WRITE_ONLY=" + bool_to_string(ui->cb_printer_write->isChecked()) + "\n";

        if(ui->com_printertype->currentIndex() == 3)
        {
        config += "PRINTER_0_SPEED=";
        if(ui->txt_printerspeed->text() != "")
            config += ui->txt_printerspeed->text() + "\n";
        else
            config += "9600\n";
        config += "PRINTER_0_PARITY=" + bool_to_string(ui->cb_printparity->isChecked()) + "\n";

        config += "PRINTER_0_DATABITS=";
        if(ui->txt_printerdatabits->text() != "")
            config += ui->txt_printerdatabits->text() + "\n";
        else
            config += "8\n";

        if(ui->txt_printeroptions->text() != "")
            config += "PRINTER_0_OPTIONS=" + ui->txt_printeroptions->text() + "\n";
        }

     }

        if(ui->txt_printerlist->text() != "")
            config += "LDM_PRINTER_LIST=" + ui->txt_printerlist->text() + "\n";

        if(ui->txt_printerdefault->text() != "")
            config += "LDM_PRINTER_DEFAULT=" + ui->txt_printerdefault->text() + "\n";

        config += "SCANNER=" + bool_to_string(ui->cb_scanner->isChecked()) + "\n";

        if(ui->cb_keyboard->isChecked())
        {
            config += "\n[Keyboard]\n";

            config += "CONSOLE_KEYMAP=";
            if(ui->txt_keymap->text() != "")
                config += ui->txt_keymap->text() + "\n";
            else
                config += "en\n";

            if(ui->txt_xkblayout->text() != "")
                config += "XKBLAYOUT=" + ui->txt_xkblayout->text() + "\n";

            if(ui->txt_xkbmodel->text() != "")
                config += "XKBMODEL=" + ui->txt_xkbmodel->text() + "\n";

            if(ui->txt_xkboptions->text() != "")
                config+= "XKBOPTIONS=" + ui->txt_xkboptions->text() + "\n";

            if(ui->txt_xkbrules->text() != "")
                config += "XKBRULES=" + ui->txt_xkbrules->text() + "\n";

            if(ui->txt_xkbvariant->text() != "")
                config += "XKBVARIANT=" + ui->txt_xkbvariant->text() + "\n";
        }

        config += "\n[Sound]\n";

        config += "SOUND=" + bool_to_string(ui->cb_sound->isChecked()) + "\n";

        config += "SOUND_DAEMON=";
        switch(ui->com_sounddaemon->currentIndex())
        {
        case 0:
            config += "pulse\n";
            break;
        case 1:
            config += "esd\n";
            break;
        case 2:
            config += "nasd\n";
            break;
        }

        config += "VOLUME=";
        if(ui->txt_volume->text() != "")
            config += ui->txt_volume->text() + "\n";
        else
            config += "90\n";

        if(ui->txt_headphonevolume->text() != "")
            config += "HEADPHONE_VOLUME=" + ui->txt_headphonevolume->text() + "\n";

        if(ui->txt_pcmvolume->text() != "")
            config += "PCM_VOLUME=" + ui->txt_pcmvolume->text() + "\n";

        if(ui->txt_cdvolume->text() != "")
            config += "CD_VOLUME=" + ui->txt_cdvolume->text() + "\n";

        if(ui->txt_frontvolume->text() != "")
            config += "FRONT_VOLUME=" + ui->txt_frontvolume->text() + "\n";

        if(ui->txt_micvolume->text() != "")
            config += "MIC_VOLUME=" + ui->txt_micvolume->text() + "\n";

        config += "\n[Xorg Parameters]\n";

        config += "USE_XFS=" + bool_to_string(ui->cb_xfs->isChecked()) + "\n";

        if(ui->txt_xfsserver->text() != "")
            config += "XFS_SERVER=" + ui->txt_xfsserver->text() + "\n";

        if(ui->cb_configx->isChecked())
            config += "CONFIGURE_X=True";

        if(ui->txt_xconfig->text() != "")
            config += "X_CONF=" + ui->txt_xconfig->text() + "\n";

        if(ui->sb_xramperc->value() > 100)
            config += "X_RAMPERC=100\n";
        else
            config += "X_RAMPERC=" + QString::number(ui->sb_xramperc->value()) + "\n";

        if(ui->txt_xvirtual->text() != "")
            config += "X_VIRTUAL=" + ui->txt_xvirtual->text() + "\n";

        if(ui->txt_xdmserver->text() != "")
            config += "XDM_SERVER=" + ui->txt_xdmserver->text() + "\n";

        if(ui->cb_xserver->isChecked())
            config += "XSERVER=" + ui->txt_xserver->text() + "\n";

        if(ui->cb_xmouse->isChecked())
        {
            config += "X_MOUSE_DEVICE=" + ui->txt_xmousedev->text() + "\n";
            config += "X_MOUSE_PROTOCOL=" + ui->txt_xmousepro->text() + "\n";
        }

        if(ui->cb_mouseemu->isChecked())
            config += "X_MOUSE_EMULATE3BTN=Y\n";

        config += "X_NUMLOCK=" + bool_to_string(ui->cb_numlock->isChecked()) + "\n";

        config += "X_COLOR_LEVEL=" + ui->com_colordepth->currentText() + "\n";

        if(ui->cb_customxorg->isChecked())
        {
            config += "\n[Custom Xorg Options]\n";

            QLineEdit* xoptions[] = {ui->txt_xoption0, ui->txt_xoption1, ui->txt_xoption2, ui->txt_xoption3, ui->txt_xoption4, ui->txt_xoption5, ui->txt_xoption6, ui->txt_xoption7, ui->txt_xoption8, ui->txt_xoption9, ui->txt_xoption10, ui->txt_xoption11};

            for(int j = 0; j < 12; j++)
            {
                if(xoptions[j]->text() != "")
                {
                    if(j < 9)
                    {
                        config += "X_OPTION_0" + QString::number(j+1);
                        config += "=" + xoptions[j]->text() + "\n";
                    }
                    else if(j >= 9)
                    {
                        config += "X_OPTION_" + QString::number(j+1);
                        config += "=" + xoptions[j]->text() + "\n";
                    }
                }
            }

            if(ui->txt_xmode0->text() != "")
                config += "X_MODE_0=" + ui->txt_xmode0->text() + "\n";

            if(ui->txt_xmode1->text() != "")
                config += "X_MODE_1=" + ui->txt_xmode1->text() + "\n";

            if(ui->txt_xmode2->text() != "")
                config += "X_MODE_2=" + ui->txt_xmode2->text() + "\n";
        }

       config += "X_BLANKING=" + QString::number(ui->sb_xblanking->value()) + "\n";

       config += "\n[Screen Scripts]\n";

       QComboBox* screens[] = {ui->com_screen0, ui->com_screen1, ui->com_screen2, ui->com_screen3, ui->com_screen4, ui->com_screen5, ui->com_screen6, ui->com_screen7, ui->com_screen8, ui->com_screen9, ui->com_screen10, ui->com_screen11};

       for(int k = 0; k < 12; k++)
       {
               if(k < 9)
               {
                   config += "SCREEN_0" + QString::number(k+1);
                   config += "=" + screens[k]->currentText() + "\n";
               }
               else if(k >= 9)
               {
                   config += "SCREEN_" + QString::number(k+1);
                   config += "=" + screens[k]->currentText() + "\n";
               }
       }

       if(ui->txt_telnethost->text() != "")
           config += "TELNET_HOST=" + ui->txt_telnethost->text() + "\n";

       config += "\n[LDM Options]\n";

       if(ui->com_autologin->currentIndex() == 1)
       {
           config += "LDM_AUTOLOGIN=True\n";

           if(ui->txt_autouser->text() != "")
               config += "LDM_USERNAME=" + ui->txt_autouser->text() + "\n";

           if(ui->txt_autopass->text() != "")
               config += "LDM_PASSWORD=" + ui->txt_autopass->text() + "\n";
       }
       else
           config += "LDM_AUTOLOGIN=False\n";

        switch(ui->com_debug->currentIndex())
        {
            case 0:
                break;
            case 1:
                config += "LDM_DEBUG=True\n";
                break;
            case 2:
                config += "LDM_DEBUG=False\n";
                break;
        }

        config += "LDM_DIRECTX=" + bool_to_string(ui->cb_directx->isChecked()) + "\n";

        config += "LDM_GUESTLOGIN=" + bool_to_string(ui->cb_guestlogin->isChecked()) + "\n";

        if(ui->sb_logtimeout->value() > 0)
        {
            config += "LDM_LOGIN_TIMEOUT=" + QString::number(ui->sb_logtimeout->value()) + "\n";

            if(ui->txt_autouser->text() != "")
                config += "LDM_USERNAME=" + ui->txt_autouser->text() + "\n";

            if(ui->txt_autopass->text() != "")
                config += "LDM_PASSWORD=" + ui->txt_autopass->text() + "\n";
        }

        config += "LDM_SYSLOG=" + bool_to_string(ui->cb_syslog->isChecked()) + "\n";

        if(ui->txt_language->text() != "")
            config += "LDM_LANGUAGE=" + ui->txt_language->text() + "\n";

        config += "NETWORK_COMPRESSION=" + bool_to_string(ui->cb_netcompress->isChecked()) + "\n";

        if(ui->txt_sshoverride->text() != "")
            config += "SSH_OVERRIDE_PORT=" + ui->txt_sshoverride->text() + "\n";

        config += "SSH_FOLLOW_SYMLINKS=" + bool_to_string(ui->cb_symlinks->isChecked()) + "\n";

        if(ui->txt_session->text() != "")
            config += "LDM_SESSION=" + ui->txt_session->text() + "\n";

        if(ui->txt_xsession->text() != "")
            config += "LDM_XSESSION=" + ui->txt_xsession->text() + "\n";
        else
            config += "LDM_XSESSION=Xsession\n";

        config += "\n[Local Applications]\n";

        config += "LOCAL_APPS=" + bool_to_string(ui->cb_localapps->isChecked()) + "\n";

        config += "LOCAL_APPS_MENU=" + bool_to_string(ui->cb_localappsmenu->isChecked()) + "\n";

        if(ui->cb_localappsmenu->isChecked() && ui->txt_localappmenu->text() != "")
            config += "LOCAL_APPS_MENU_ITEMS=" + ui->txt_localappmenu->text() + "\n";

        if(ui->txt_appwhitelist->text() != "")
            config += "LOCAL_APPS_WHITELIST=" + ui->txt_appwhitelist->text() + "\n";

        config += "\n[End Config]\n";

    return config;
}

void MainWindow::on_btn_genfile_clicked()
{
    FileSystem fsys;
    //QString test_data = "Test test test";

    QString config_string = config_compile();

    fsys.write_file(config_string);

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

void MainWindow::on_cb_nbdswap_toggled(bool checked)
{
    if (checked)
    {
        ui->txt_nbdswapport->setEnabled(true);
        ui->txt_nbdswapserver->setEnabled(true);
    }
    else
    {
        ui->txt_nbdswapport->setEnabled(false);
        ui->txt_nbdswapserver->setEnabled(false);
    }
}

void MainWindow::on_cb_localapp_toggled(bool checked)
{
    if(checked)
        ui->txt_localappextra->setEnabled(true);
    else
        ui->txt_localappextra->setEnabled(false);
}

void MainWindow::on_cb_scripts_toggled(bool checked)
{
    if (checked)
    {
        QString tabname = "Scripts and Modules";

        if(crontab_tab != NULL)
            ui->tabWidget->insertTab(1, scripts_tab, tabname);
        else
            ui->tabWidget->insertTab(2, scripts_tab, tabname);

        scripts_tab = NULL;

    }
    else if (!checked)
    {
        if(crontab_tab != NULL)
        {
            scripts_tab = ui->tabWidget->widget(1);
            ui->tabWidget->removeTab(1);
        }
        else
        {
            scripts_tab = ui->tabWidget->widget(2);
            ui->tabWidget->removeTab(2);
        }
    }
}

void MainWindow::on_com_printertype_currentIndexChanged(int index)
{
    if(index == 3)
    {
        ui->txt_printerflow->setEnabled(true);
        ui->txt_printerdatabits->setEnabled(true);
        ui->txt_printeroptions->setEnabled(true);
        ui->txt_printerspeed->setEnabled(true);
        ui->cb_printparity->setEnabled(true);
    }
    else
    {
        ui->txt_printerflow->setEnabled(false);
        ui->txt_printerdatabits->setEnabled(false);
        ui->txt_printeroptions->setEnabled(false);
        ui->txt_printerspeed->setEnabled(false);
        ui->cb_printparity->setEnabled(false);
    }
}

void MainWindow::on_cb_keyboard_toggled(bool checked)
{
    if(checked)
    {
        ui->txt_keymap->setEnabled(true);
        ui->txt_xkblayout->setEnabled(true);
        ui->txt_xkbmodel->setEnabled(true);
        ui->txt_xkboptions->setEnabled(true);
        ui->txt_xkbrules->setEnabled(true);
        ui->txt_xkbvariant->setEnabled(true);
    }
    else
    {
        ui->txt_keymap->setEnabled(false);
        ui->txt_xkblayout->setEnabled(false);
        ui->txt_xkbmodel->setEnabled(false);
        ui->txt_xkboptions->setEnabled(false);
        ui->txt_xkbrules->setEnabled(false);
        ui->txt_xkbvariant->setEnabled(false);
    }
}

void MainWindow::on_cb_customxorg_toggled(bool checked)
{
    if(checked)
    {
        QString tabname = "Xorg Options";
        if(crontab_tab != NULL && scripts_tab != NULL)
        {
            ui->tabWidget->insertTab(5, xorgoptions_tab, tabname);
            xorgoptions_tab = NULL;
        }
        else if(crontab_tab == NULL ^ scripts_tab == NULL)
        {
            ui->tabWidget->insertTab(6, xorgoptions_tab, tabname);
            xorgoptions_tab = NULL;
        }
        else if(crontab_tab == NULL && scripts_tab == NULL)
        {
            ui->tabWidget->insertTab(7, xorgoptions_tab, tabname);
            xorgoptions_tab = NULL;
        }
    }
        else
        {
        if(crontab_tab != NULL && scripts_tab != NULL)
            {
            xorgoptions_tab = ui->tabWidget->widget(5);
            ui->tabWidget->removeTab(5);
            }
        else if(crontab_tab == NULL ^ scripts_tab == NULL)
            {
            xorgoptions_tab = ui->tabWidget->widget(6);
            ui->tabWidget->removeTab(6);
            }
        else if(crontab_tab == NULL && scripts_tab == NULL)
            {
            xorgoptions_tab = ui->tabWidget->widget(7);
            ui->tabWidget->removeTab(7);
            }
        }
}

void MainWindow::on_cb_xserver_toggled(bool checked)
{
    if(checked)
        ui->txt_xserver->setEnabled(true);
    else
        ui->txt_xserver->setEnabled(false);
}

void MainWindow::on_cb_xmouse_toggled(bool checked)
{
    if(checked)
    {
        ui->txt_xmousedev->setEnabled(true);
        ui->txt_xmousepro->setEnabled(true);
    }
    else
    {
        ui->txt_xmousedev->setEnabled(false);
        ui->txt_xmousepro->setEnabled(false);
    }
}

void MainWindow::on_com_autologin_currentIndexChanged(int index)
{
    if(index == 1)
    {
        ui->txt_autouser->setEnabled(true);
        ui->txt_autopass->setEnabled(true);
        ui->sb_logtimeout->setEnabled(false);
    }
    else
    {
        ui->txt_autouser->setEnabled(false);
        ui->txt_autopass->setEnabled(false);
        ui->sb_logtimeout->setEnabled(true);
    }
}

void MainWindow::on_sb_logtimeout_valueChanged(int arg1)
{
    if(arg1 > 0)
    {
        ui->txt_autouser->setEnabled(true);
        ui->txt_autopass->setEnabled(true);
        ui->com_autologin->setEnabled(false);
    }
    else
    {
        ui->txt_autouser->setEnabled(false);
        ui->txt_autopass->setEnabled(false);
        ui->com_autologin->setEnabled(true);
    }
}

void MainWindow::on_cb_localappsmenu_toggled(bool checked)
{
    if(checked)
        ui->txt_localappmenu->setEnabled(true);
    else
        ui->txt_localappmenu->setEnabled(false);
}

void MainWindow::on_cb_whitelist_toggled(bool checked)
{
    if(checked)
        ui->txt_appwhitelist->setEnabled(true);
    else
        ui->txt_appwhitelist->setEnabled(false);
}
