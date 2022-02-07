#include "album.h"


Album::Album(QString albumName, QString author, QString date, QString genre, QStringList albumSongList, QString imageFile){
    this->albumName=albumName;
    this->author=author;
    this->date=date;
    this->genre=genre;
    this->albumSongList=albumSongList;
    this->imageFile=imageFile;
}
