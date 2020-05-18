#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include <Controller/databasecontroller.h>
#include <Controller/usercontroller.h>
#include <QAxObject>
#include <QDir>
#include <QFile>


class FileController : public QThread
{
public:
    //构造单例模式（懒汉单例模式）
    ~FileController()
    {
        qDebug()<<"destructor called!";
    }

    FileController(const FileController&)=delete;
    FileController& operator=(const FileController&)=delete;

    static FileController& getInstance(){
        static FileController instance;
        return instance;
    }

    void startOutPut(const QString fileName, QList<App*> apps);
    void startInPut(const QString fileName);
    void inputApp(QString appName);//库内所有app写入文件

private:
    FileController(){
        qDebug()<<"constructor called!";
    }

    void newExcel(const QString fileName);
    void openExcel(const QString fileName);
    void appendSheet(const QString sheetName);
    void setCellValue(int row, int column, const QString value);
    void saveExcel(const QString fileName);
    void freeExcel();

    QAxObject *qApplication;
    QAxObject *qWorkBooks;
    QAxObject *qWorkBook;
    QAxObject *qSheets;
    QAxObject *qSheet;
};

#endif // FILECONTROLLER_H
