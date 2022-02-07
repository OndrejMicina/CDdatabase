#include "album.h"


Album::Album(QString albumName, QString author, QDate date, QString genre, QStringList musicFiles, QString imageFile){
    this->albumName=albumName;
    this->author=author;
    this->date=date;
    this->genre=genre;
    this->musicFiles=musicFiles;
    this->imageFile=imageFile;
}
