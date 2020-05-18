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
    explicit HistoryMarkWidget(QWidget *parent = nullptr);
    ~HistoryMarkWidget();

private:
    Ui::HistoryMarkWidget *ui;
};

#endif // HISTORYMARKWIDGET_H
