#ifndef ALBUM_H
#define ALBUM_H


#include <QString>
#include <QDate>

class Album
{

public:

    QString albumName;
    QString author;
    QDate date;
    QString genre;
    QStringList musicFiles;
    QString imageFile;

    Album(QString albumName,QString author,QDate date,QString genre,QStringList musicFiles,QString imageFile);



};

#endif // ALBUM_H
