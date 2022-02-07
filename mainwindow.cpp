#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newalbumdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->albumTable->setColumnWidth(0, 85);
    ui->albumTable->setColumnWidth(1, 125);
    QFont font=QFont("Segoe UI",12);
    font.setBold(false);
    ui->albumTable->setFont(font);





}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_newAlbumButton_clicked()
{
    NewAlbumDialog *newAlbumDialog = new NewAlbumDialog(this);

    newAlbumDialog->show();
}

