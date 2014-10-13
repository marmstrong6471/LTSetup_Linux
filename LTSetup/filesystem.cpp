#include "filesystem.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QString>


    bool backup_file(QString filename)
    {

    }

    void write_file(QString filename)
    {
        QFile config(filename);

        if(!config.open(QFile::WriteOnly | QFile::Text))
        {
            QDebug() << "Could not open file for writing";
            return;
        }

        QTextStream lts_settings(&config);
        out << "Test data";

        config.flush();
        config.close();
    }
