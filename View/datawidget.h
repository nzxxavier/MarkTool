#ifndef DATAWIDGET_H
#define DATAWIDGET_H

#include <QtCharts>
QT_CHARTS_USE_NAMESPACE

#include <QWidget>
#include <QRadioButton>
#include <QFormLayout>
#include <QDesktopWidget>
#include <Controller/databasecontroller.h>
#include <Controller/usercontroller.h>
#include "tocorrectwidget.h"
#include "mymessagebox.h"

namespace Ui {
class DataWidget;
}

class DataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DataWidget(QWidget *parent = nullptr);
    ~DataWidget();

private slots:
    void on_btn_Creddit_clicked();

    void on_btn_Class_clicked();

    void on_btn_Correct_clicked();

private:
    Ui::DataWidget *ui;
    MyMessageBox *box;
};

#endif // DATAWIDGET_H
