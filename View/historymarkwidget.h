#ifndef HISTORYMARKWIDGET_H
#define HISTORYMARKWIDGET_H

#include <QWidget>

namespace Ui {
class HistoryMarkWidget;
}

class HistoryMarkWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryMarkWidget(QString markId, QString value, qint32 rowCount, QWidget *parent = nullptr);
    ~HistoryMarkWidget();
    void focused(bool focus);
    qint32 getRowCount();

signals:
    void historyMarkWidget_clicked(QString markId);

private slots:
    void on_pushButton_clicked();

private:
    Ui::HistoryMarkWidget *ui;
    QString markId;
    qint32 rowCount;
};

#endif // HISTORYMARKWIDGET_H
