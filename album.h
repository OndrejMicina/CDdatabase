#ifndef ALBUM_H
#define ALBUM_H

#include <QObject>
#include <QDate>

class Album : public QObject
{
    Q_OBJECT

private:
    QString albumName;
    QString authorName;
    QString imgPath;
    QDate releaseDate;
    QStringList songList;


public:   
    explicit Album(QObject *parent = nullptr);
     void FillInfo();


signals:

private slots:


};

#endif // ALBUM_H
