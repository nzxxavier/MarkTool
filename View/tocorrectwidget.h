#ifndef TOCORRECTWIDGET_H
#define TOCORRECTWIDGET_H

#include <QWidget>

namespace Ui {
class ToCorrectWidget;
}

class ToCorrectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToCorrectWidget(QWidget *parent = nullptr);
    ~ToCorrectWidget();

private:
    Ui::ToCorrectWidget *ui;
};

#endif // TOCORRECTWIDGET_H
