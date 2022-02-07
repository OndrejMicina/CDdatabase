#include "databasemanager.h"

#include <QStandardPaths>
#include <QFile>
#include <QtXml>
#include <QTextStream>

DatabaseManager::DatabaseManager()
{

}

bool DatabaseManager::ensureCreated()
{

    QDir currentLocation= QDir::currentPath();
    QDir databaseFolder=currentLocation.absolutePath()+"/database";
    QFile xmlFile(databaseFolder.absolutePath()+"/albumDatabase.xml");

    if(!QFileInfo::exists(databaseFolder.absolutePath())){  //create database folder
        currentLocation.mkdir(databaseFolder.absolutePath());
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
        }
    }
    else{
         //is already created
        return true;
    }

}

void DatabaseManager::addAlbum(QString albumName,QString author, QDate date,QString genre,QString albumFolder)
{
    QDir currentLocation= QDir::currentPath();
    QDir databaseFolder=currentLocation.absolutePath()+"/database";
    QFile xmlFile(databaseFolder.absolutePath()+"/albumDatabase.xml");

    QDomDocument document; //create document, first read data and assing content then write

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

        //**********************WRITE*****************
        if(!xmlFile.open(QIODevice::WriteOnly | QIODevice::Text)){
             qDebug() << "Failed to open file";
        }
        else{

            QDomNode elementList= document.namedItem("AlbumList");
            QDomElement album = document.createElement("Album");

            album.setAttribute("albumName", albumName);
            album.setAttribute("author", author);
            album.setAttribute("date", date.toString());
            album.setAttribute("genre", genre);
            album.setAttribute("albumFolder", albumFolder);
            elementList.appendChild(album);

            QTextStream stream(&xmlFile);
            stream<<document.toString();
            xmlFile.close();
        }
    }



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

bool DatabaseManager::addSongsToAlbum(QString albumFolder, QStringList musicFiles)
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


    return true;
}
