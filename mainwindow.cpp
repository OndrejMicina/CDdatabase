#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newalbumdialog.h"
#include "databasemanager.h"
#include "album.h"
#include <QFile>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->albumTree->setColumnWidth(0, 300);
    ui->albumTree->setColumnWidth(1, 200);
    QFont font=QFont("Segoe UI",11);
    ui->albumTree->setFont(font);

    UpdateAlbumList();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_newAlbumButton_clicked()
{
    NewAlbumDialog *newAlbumDialog = new NewAlbumDialog(this);

    connect(newAlbumDialog,SIGNAL(accepted()),this,SLOT(UpdateAlbumList()));

    newAlbumDialog->show();

}

/*void MainWindow::UpdateAlbumList()
{
    DatabaseManager *dm = new DatabaseManager();
    QList<Album*> listOfAlbums = dm->listOfAlbums();

    ui->albumTable->clear();
    ui->albumTable->setRowCount(listOfAlbums.count());

    for(int row =0;row<listOfAlbums.count();row++){
        QTableWidgetItem *icon = new QTableWidgetItem();
        QIcon *qicon= new QIcon(listOfAlbums[row]->imageFile);

        icon->setIcon(*qicon);
        QTableWidgetItem *albumName = new QTableWidgetItem(listOfAlbums[row]->albumName);
        QTableWidgetItem *author = new QTableWidgetItem(listOfAlbums[row]->author);
        QTableWidgetItem *date = new QTableWidgetItem(listOfAlbums[row]->date);
        QTableWidgetItem *genre = new QTableWidgetItem(listOfAlbums[row]->genre);


        ui->albumTable->setItem(row,0,icon);    //icon
        ui->albumTable->setItem(row,1,albumName);    //Name
        ui->albumTable->setItem(row,2,author);    //Author
        ui->albumTable->setItem(row,3,date);    //date
        ui->albumTable->setItem(row,4,genre);    //genre
    }

    ui->albumTable->update();
}*/


void MainWindow::UpdateAlbumList()
{
    DatabaseManager *dm = new DatabaseManager();
    QList<Album*> listOfAlbums = dm->listOfAlbums();

    ui->albumTree->clear();
    QTreeWidgetItem *wdItem= new QTreeWidgetItem(ui->albumTree);
    ui->albumTree->addTopLevelItem(wdItem);

    for(int row =0;row<listOfAlbums.count();row++){

        QTreeWidgetItem *root= new QTreeWidgetItem(ui->albumTree);
        QIcon *qicon;
        if (QFile::exists(listOfAlbums[row]->imageFile))
        {
             qicon= new QIcon(listOfAlbums[row]->imageFile);
        }
        else{
            qicon= new QIcon(":/Images/Images/default_album.png");
        }

        root->setIcon(0,*qicon);
        root->setText(0,listOfAlbums[row]->albumName);
        root->setText(1,listOfAlbums[row]->author);
        root->setText(2,listOfAlbums[row]->date);
        root->setText(3,listOfAlbums[row]->genre);

        for (QString songPath : listOfAlbums[row]->albumSongList) {
            QFile file(songPath);
            QFileInfo fileInfo(file.fileName());

            QString song(fileInfo.fileName());

            QTreeWidgetItem *child= new QTreeWidgetItem();

            child->setText(0,song);

            root->addChild(child);
        }
    }

    ui->albumTree->update();
}



