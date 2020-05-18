#ifndef CORRECTWIDGET_H
#define CORRECTWIDGET_H

#include <QWidget>

namespace Ui {
class CorrectWidget;
}

class CorrectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CorrectWidget(QWidget *parent = nullptr);
    ~CorrectWidget();

private:
    Ui::CorrectWidget *ui;
};

#endif // CORRECTWIDGET_H
