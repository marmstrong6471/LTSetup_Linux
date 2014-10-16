#include "filesystem.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QString>



    bool backup_file(QString filename)
    {
        return true;
    }

    bool write_file(QString filename)
    {
        QFile config(filename);

        if(!config.open(QFile::WriteOnly | QFile::Text))
        {
            QDebug("Could not open file for writing");
            return false;
        }

        QTextStream lts_settings(&config);
        out << "Test data";

        config.flush();
        config.close();
        return true;
    }

    bool file_wrapper(QString filename)
    {
        if(!write_file(filename))
        {
            QDebug("File write failed");
            return false;
        }
        else
            return true;
    }
