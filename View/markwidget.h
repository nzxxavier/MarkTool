#ifndef MARKWIDGET_H
#define MARKWIDGET_H

#include <QWidget>
#include <QFormLayout>
#include <Model/mark.h>
#include <Controller/databasecontroller.h>
#include <View/historymarkwidget.h>

namespace Ui {
class MarkWidget;
}

class MarkWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MarkWidget(QWidget *parent = nullptr);

    ~MarkWidget();

    void reLoad();

    qint32 getMarkClass();

    qint32 getMarkCreddit();

    QString getMarkNote();

public slots:

    void mark_receive_commentId(QString commentId);
    void mark_receive_markId(QString markId);

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

private:
    Ui::MarkWidget *ui;

    qint32 markClass = -1;

    QString commentId;

    void clean();
};

#endif // MARKWIDGET_H
