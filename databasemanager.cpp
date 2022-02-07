#include "databasemanager.h"

#include <QStandardPaths>
#include <QFile>
#include <QtXml>
#include <QTextStream>
#include "album.h"

DatabaseManager::DatabaseManager()
{

}



QString DatabaseManager::createAlbumFolder(QString albumName)
{
    QDir currentLocation= QDir::currentPath();
    QDir databaseFolder=currentLocation.absolutePath()+"/database/"+albumName;


    if(!QFileInfo::exists(databaseFolder.absolutePath())){
        currentLocation.mkdir(databaseFolder.absolutePath());
         qDebug() << "Created album folder - "+albumName;
    };

    return databaseFolder.absolutePath();


}

void DatabaseManager::addSongsToAlbum(QString albumFolder, QStringList musicFiles)
{
    for(QString filePath : musicFiles){

        QFile file(filePath);
        QFileInfo fileInfo(file.fileName());

        QString filename(fileInfo.fileName());

        if (QFile::exists(albumFolder+"/"+filename))
        {
            QFile::remove(albumFolder+"/"+filename);
        }

        QFile::copy(filePath, albumFolder+"/"+filename);
    }



}

void DatabaseManager::addAlbumImage(QString albumFolder,QString imagePath){

    QString filename = "ALBUM_IMAGE.bmp";

    if (QFile::exists(albumFolder+"/"+filename))
    {
        QFile::remove(albumFolder+"/"+filename);
    }

    QFile::copy(imagePath, albumFolder+"/"+filename);

}



bool DatabaseManager::ensureCreated()
{

    QDir currentLocation= QDir::currentPath();
    QDir databaseFolder=currentLocation.absolutePath()+"/database";
    QFile xmlFile(databaseFolder.absolutePath()+"/albumDatabase.xml");

    if(!QFileInfo::exists(databaseFolder.absolutePath())){  //create database folder
        if(!currentLocation.mkdir(databaseFolder.absolutePath())){
            qDebug() << "Unable to create album directory";
            return false;
        }
    };


    if(!xmlFile.exists()){
        QDomDocument document;
        QDomElement root = document.createElement("AlbumList");
        document.appendChild(root);

        //create new xmlFile
        if (!xmlFile.open(QIODevice::WriteOnly | QIODevice::Text ))
            {
                qDebug() << "Already opened or there is another issue";
                return false;
            }
        else{
            QTextStream stream(&xmlFile);
            stream<<document.toString();
            xmlFile.close();
            return true;
        }
    }
    else{
         //is already created
        return true;
    }

}

void DatabaseManager::addAlbum(Album album)
{
    QString albumFolder = createAlbumFolder(album.albumName);        //create folder here, return path

    QDir currentLocation= QDir::currentPath();
    QDir databaseFolder=currentLocation.absolutePath()+"/database";
    QFile xmlFile(databaseFolder.absolutePath()+"/albumDatabase.xml");

    QDomDocument document; //create document, first read data and assing content then write

    if(xmlFile.exists()){

        //**********************READ*****************
        if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text )){
            qDebug() << "Failed to open file";
            return;
        }
        else{
            if(!document.setContent(&xmlFile)){
                qDebug() << "Failed to set content";
                return;
            }
            else{
                xmlFile.close();
            }
        }

        //**********************WRITE*****************
        if(!xmlFile.open(QIODevice::WriteOnly | QIODevice::Text)){
             qDebug() << "Failed to open file";
        }
        else{

            QDomNode elementList= document.namedItem("AlbumList");
            QDomElement albumElement = document.createElement("Album");

            albumElement.setAttribute("albumName", album.albumName);
            albumElement.setAttribute("author", album.author);
            albumElement.setAttribute("date", album.date);
            albumElement.setAttribute("genre", album.genre);
            albumElement.setAttribute("albumFolder", albumFolder);

            for(QString filePath : album.albumSongList){
                 QDomElement song = document.createElement("AlbumSong");
                 QDomText fPath = document.createTextNode(filePath);
                song.appendChild(fPath);
                albumElement.appendChild(song);
            }


            elementList.appendChild(albumElement);

            QTextStream stream(&xmlFile);
            stream<<document.toString();
            xmlFile.close();

            addSongsToAlbum(albumFolder,album.albumSongList);
            addAlbumImage(albumFolder,album.imageFile);

        }
    }
    else{
        qDebug() << "Failed to open file";
    }
}

QList<Album *> DatabaseManager::listOfAlbums()
{
    QList<Album *> albumsList;

    QDir currentLocation= QDir::currentPath();
    QDir databaseFolder=currentLocation.absolutePath()+"/database";
    QFile xmlFile(databaseFolder.absolutePath()+"/albumDatabase.xml");

     QDomDocument document; //create document,assing content

    if(xmlFile.exists()){

        //**********************READ*****************
        if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text )){
            qDebug() << "Failed to open file";
        }
        else{
            if(!document.setContent(&xmlFile)){
                qDebug() << "Failed to set content";
            }
            else{
                xmlFile.close();
            }
        }
    }


    QDomElement topElement = document.documentElement();
    QDomNode domNode = topElement.firstChild();

    while (!domNode.isNull()) {
            QDomElement domElement = domNode.toElement();
            if (!domElement.isNull()) {
                //create album here
                QString albumName = domElement.attribute("albumName");      //name
                QString author = domElement.attribute("author");         //author
                QString date = domElement.attribute("date");           //date
                QString genre = domElement.attribute("genre");          //genre
                QString albumFolder = domElement.attribute("albumFolder");    //albumFolderPath
                QString imageFile = domElement.attribute("albumFolder")+"/ALBUM_IMAGE.bmp";  //imageFile

                QDomNodeList nodeList = domElement.elementsByTagName("AlbumSong");
                QStringList albumSongList;

                for(int i =0; i<nodeList.count();i++){
                    QString songRow = nodeList.at(i).toElement().text();
                    albumSongList.append(songRow);
                    qDebug() << "ADDING TO LIST"+songRow;
                }

                Album *album = new Album(albumName,author,date,genre,albumSongList,imageFile);
                albumsList.append(album);
            }
            domNode = domNode.nextSibling();
        }



    return albumsList;
}



