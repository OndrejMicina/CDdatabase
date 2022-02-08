#ifndef NEWALBUMDIALOG_H
#define NEWALBUMDIALOG_H

#include <QDialog>

namespace Ui {
class NewAlbumDialog;
}

class NewAlbumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewAlbumDialog(QWidget *parent = nullptr);
    ~NewAlbumDialog();


private slots:


    void on_addSongsButton_clicked();

    void on_albumAddOkButton_clicked();

    void on_closeButton_clicked();

    void on_AlbumImagePreview_clicked();

private:
    Ui::NewAlbumDialog *ui;
};

#endif // NEWALBUMDIALOG_H
