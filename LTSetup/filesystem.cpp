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

        if(bak.exists())    //Check if a backup already exists
        {
            bak.remove();   //If it does, delete it
        }
        file.copy(bak_name);    //Backup the lts.conf if it exists
        return true;
    }

    bool FileSystem::write_file(QString settings)
    {
        QFile file("lts.conf");

        backup_file();

        if(!file.open(QFile::WriteOnly | QFile::Text))  //Check if we can open the lts.conf for writing
        {
            qDebug() << "Could not open file for writing" << endl;  //Return an error if we can't open it
            return false;
        }

        QTextStream lts_settings(&file);    //Open a textstream for inserting things into the file
        lts_settings << settings;   //Write settings into lts.conf

        file.flush();   //Flush the file contents to ensure everything is written to disk
        file.close();
        return true;
    }
