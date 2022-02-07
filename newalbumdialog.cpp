#include "newalbumdialog.h"
#include "ui_newalbumdialog.h"

#include <QFileDialog>


#include "databasemanager.h"
#include "album.h"

QStringList musicFiles;
QString imageFile;

NewAlbumDialog::NewAlbumDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAlbumDialog)
{
    ui->setupUi(this);

}

NewAlbumDialog::~NewAlbumDialog()
{    
    delete ui;
}

void NewAlbumDialog::on_addSongsButton_clicked()
{

    musicFiles = QFileDialog::getOpenFileNames(this,
                                                      "Select one or more files to open",
                                                      "/home",
                                                      "Audio (*.mp3 *.waw)");
    ui->songsListWidget->clear();
    ui->songsListWidget->addItems(musicFiles);

    ui->songsListWidget->update();
}


void NewAlbumDialog::on_AlbumImagePreview_clicked()
{
    QString imgPath = QFileDialog::getOpenFileName(this,
                                                      "Select file to open",
                                                      "/home",
                                                      "Image (*.bmp)");
    if(imgPath!=""){

        imageFile=imgPath;

        ui->AlbumImagePreview->setPixmap(imageFile);
        ui->genreLineEdit->setText("IMAGE CLICKED");
    }
}



void NewAlbumDialog::on_albumAddOkButton_clicked()
{
   DatabaseManager *dm = new DatabaseManager();

   if(dm->ensureCreated()){

       Album album(
                   ui->albumNameLineEdit->text(),
                   ui->authorNameLineEdit->text(),
                   ui->dateEdit->date(),
                   ui->genreLineEdit->text(),
                   musicFiles,
                   imageFile);

       dm->addAlbum(album);
       close();
   }
}


void NewAlbumDialog::on_closeButton_clicked()
{
    close();
}

