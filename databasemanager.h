#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H


#include <QString>
#include <QDate>

class DatabaseManager
{
public:
    DatabaseManager();
    bool ensureCreated();
    void addAlbum(QString albumName="name",QString author="author", QDate date=QDate(0,0,0),QString genre="genre",QString albumFolder="");
    QString createAlbumFolder(QString albumName="AlbumName");
    bool addSongsToAlbum(QString albumFolder,QStringList musicFiles);

};

#endif // DATABASEMANAGER_H
