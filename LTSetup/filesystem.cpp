#include "filesystem.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QString>


    FileSystem::FileSystem()
    {

    }

    FileSystem::~FileSystem()
    {

    }

    bool FileSystem::backup_file()
    {
        QFile file("lts.conf");
        QFile bak("lts.conf.bak");
        QString bak_name = "lts.conf.bak";

        if(bak.exists())
        {
            bak.remove();
        }
        file.copy(bak_name);
        return true;
    }

    bool FileSystem::write_file(QString settings)
    {
        QFile file("lts.conf");

        backup_file();

        if(!file.open(QFile::WriteOnly | QFile::Text))
        {
            qDebug() << "Could not open file for writing" << endl;
            return false;
        }

        QTextStream lts_settings(&file);
        lts_settings << settings;

        file.flush();
        file.close();
        return true;
    }
