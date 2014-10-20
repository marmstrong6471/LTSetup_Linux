#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QFile>
#include <QString>

class FileSystem
{
private:
    bool backup_file();

public:
    FileSystem();
    ~FileSystem();
    bool write_file(QString *settings);
};

#endif // FILESYSTEM_H
