#ifndef COMMENTWIDGET_H
#define COMMENTWIDGET_H

#include <QWidget>
#include "ui_commentwidget.h"
#include "Model/comment.h"
#include "Controller/databasecontroller.h"
#include "Controller/usercontroller.h"
#include "markwidget.h"
#include "correctwidget.h"
#include "mymessagebox.h"
#include <QTextDocumentFragment>
#include <QDesktopWidget>

namespace Ui {
class CommentWidget;
}

class CommentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommentWidget(QWidget *parent = nullptr);
    ~CommentWidget();
    void initValue(QString appName, QString appValue, QString cmtTheme, QString comment, qint32 current, qint32 max);

signals:
    void comment_send_commentId(QString commentId);

private slots:
    void on_btn_Next_clicked();
    void on_btn_Last_clicked();
    void on_toolButton_clicked();
    void on_btn_Note_clicked();

private:
    Ui::CommentWidget *ui;
    MarkWidget* mark;
    MyMessageBox* box;
    QString currentText;

    void openMark();
    void closeMark();

};

#endif // COMMENTWIDGET_H
