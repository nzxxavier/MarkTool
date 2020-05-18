#ifndef TOCORRECTWIDGET_H
#define TOCORRECTWIDGET_H

#include <QWidget>
#include <Model/mark.h>

namespace Ui {
class ToCorrectWidget;
}

class ToCorrectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToCorrectWidget(QString userName, qint32 markClass, qint32 markCreddit, QWidget *parent = nullptr);
    ~ToCorrectWidget();
    void focused(bool focus);

signals:
    void toCorrectWidget_clicked();

private:
    Ui::ToCorrectWidget *ui;
    void setMarkClassLabel(qint32 markClass);
    void setMarkCreddit(qint32 markCreddit);
};

#endif // TOCORRECTWIDGET_H
