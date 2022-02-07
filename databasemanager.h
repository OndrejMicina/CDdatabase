#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H


#include <QString>
#include <QDate>
#include "album.h"

class DatabaseManager
{
public:
    DatabaseManager();
    bool ensureCreated();
    QString createAlbumFolder(QString albumName);
    void addSongsToAlbum(QString albumFolder,QStringList musicFiles);
    void addAlbumImage(QString albumFolder,QString imagePath);
    void addAlbum(Album album);
    QList<Album*> albumList();
};

#endif // DATABASEMANAGER_H
