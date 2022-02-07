#include "newalbumdialog.h"
#include "ui_newalbumdialog.h"

#include <QFileDialog>


#include "databasemanager.h"

QStringList musicFiles;
QString albumImage;

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

        albumImage=imgPath;

        ui->AlbumImagePreview->setPixmap(albumImage);
        ui->genreLineEdit->setText("IMAGE CLICKED");
    }

}



void NewAlbumDialog::on_albumAddOkButton_clicked()
{
   DatabaseManager *dm = new DatabaseManager();

   if(dm->ensureCreated()){


       //create folder here, return path
       QString albumPath= dm->createAlbumFolder(ui->albumNameLineEdit->text());

       dm->addAlbum(
                   ui->albumNameLineEdit->text(),  //get all parameters from UI
                   ui->authorNameLineEdit->text(),
                   ui->dateEdit->date(),
                   ui->genreLineEdit->text(),
                   albumPath
                   );

       dm->addSongsToAlbum(albumPath,musicFiles);
   }


}


void NewAlbumDialog::on_closeButton_clicked()
{
    close();
}

