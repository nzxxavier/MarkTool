#ifndef CORRECTWIDGET_H
#define CORRECTWIDGET_H

#include <QtCharts>
QT_CHARTS_USE_NAMESPACE

#include <QWidget>
#include <QRadioButton>
#include <QFormLayout>
#include <QDesktopWidget>
#include <Controller/databasecontroller.h>
#include "tocorrectwidget.h"
#include "mymessagebox.h"

namespace Ui {
class CorrectWidget;
}

class CorrectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CorrectWidget(QWidget *parent = nullptr);
    ~CorrectWidget();

    void reLoad();

public slots:

    void correct_receive_userId(QList<QList<QString>>* userId);
    void correct_receive_markId(QList<QList<QString>>* markId);
    void correct_receive_markClass(QList<QList<qint32>>* markClass);
    void correct_receive_markCreddit(QList<QList<qint32>>* markCreddit);
    void correct_receive_markContents(QList<QString>* markContents);

private slots:
    void on_btn_Star1_clicked();
    void on_btn_Star2_clicked();
    void on_btn_Star3_clicked();
    void on_btn_Star4_clicked();
    void on_btn_Star5_clicked();

    void on_btn_Type1_toggled(bool checked);
    void on_btn_Type2_toggled(bool checked);
    void on_btn_Type3_toggled(bool checked);
    void on_btn_Type4_toggled(bool checked);
    void on_btn_Type5_toggled(bool checked);
    void on_btn_Type6_toggled(bool checked);
    void on_btn_Type7_toggled(bool checked);
    void on_btn_Type8_toggled(bool checked);
    void on_btn_Type9_toggled(bool checked);
    void on_btn_Type10_toggled(bool checked);

    void on_btn_Submit_clicked();

    void on_btn_Last_clicked();

    void on_btn_Next_clicked();

private:
    Ui::CorrectWidget *ui;
    MyMessageBox* box;
    qint32 correctType = 0;
    qint32 correctCreddit = 0;
    qint32 currentCount = 0;

    QRadioButton* chooseTypeButton(qint32 type);
    void clean();
    qint32 getMarkClass();
    qint32 getMarkCreddit();

    QList<QList<QString>>* userId;
    QList<QList<QString>>* markId;
    QList<QList<qint32>>* markClass;
    QList<QList<qint32>>* markCreddit;
    QList<QString>* markContent;
};

#endif // CORRECTWIDGET_H
