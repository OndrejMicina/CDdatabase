#include "customlistwidget.h"
#include "ui_customlistwidget.h"



CustomListWidget::CustomListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomListWidget)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0, 85);
    ui->tableWidget->setColumnWidth(1, 125);
    QFont font=QFont("Segoe UI",12);
    font.setBold(false);
    ui->tableWidget->setFont(font);






}

CustomListWidget::~CustomListWidget()
{
    delete ui;
}
