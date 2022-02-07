#ifndef CUSTOMLISTWIDGET_H
#define CUSTOMLISTWIDGET_H

#include <QWidget>

namespace Ui {
class CustomListWidget;
}

class CustomListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomListWidget(QWidget *parent = nullptr);
    ~CustomListWidget();

private:
    Ui::CustomListWidget *ui;
};

#endif // CUSTOMLISTWIDGET_H
