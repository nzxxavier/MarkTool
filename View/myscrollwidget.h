#ifndef MYSCROLLWIDGET_H
#define MYSCROLLWIDGET_H

#include <QWidget>
#include <QPainter>

#include "commentwidget.h"
#include "Controller/usercontroller.h"
#include "Controller/databasecontroller.h"

namespace Ui {
class MyScrollWidget;
}

class MyScrollWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyScrollWidget(QWidget *parent = nullptr);
    ~MyScrollWidget();
    void initValue(QString appName, QString appVer, qint32 commentNum, QString lastTime);

signals:
    void myscrollwidget_delete_clicked(QString appName);
    void myscrollwidget_edit_clicked(QString appName);
    void myscrollwidget_correct_clicked(QString appName);
    void myscrollwidget_data_clicked(QString appName);

private slots:
    void on_btn_edit_clicked();

    void on_btn_delete_clicked();

    void paintEvent(QPaintEvent *event);

    void on_btn_correct_clicked();

    void on_btn_data_clicked();

private:
    Ui::MyScrollWidget *ui;
    qint32 type;
};

#endif // MYSCROLLWIDGET_H
