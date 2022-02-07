#ifndef ALBUM_H
#define ALBUM_H


#include <QString>
#include <QDate>

class Album
{

public:

    QString albumName;
    QString author;
    QString date;
    QString genre;
    QStringList albumSongList;
    QString imageFile;

    Album(QString albumName,QString author,QString date,QString genre,QStringList albumSongList,QString imageFile);



};

#endif // ALBUM_H
