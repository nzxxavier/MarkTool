#include "filecontroller.h"

void FileController::startOutPut(const QString fileName, QList<App *> apps)
{
    newExcel(fileName);
    for(int i = 0; i < apps.size(); i ++) {
        inputApp(apps.at(i)->getAppName());
    }
    saveExcel(fileName);
    freeExcel();
}

void FileController::startInPut(const QString fileName)
{
    openExcel(fileName);
}

void FileController::inputApp(QString appName)
{
    DataBaseController& db = DataBaseController::getInstance();
    App* app = db.queryApp(appName, App::APP_NAME).first();
    QList<Comment*> comments = db.queryComment(app->getAppId(), Comment::APP_ID);
    qint32 markCount = 2;
    qint32 correctionCount = 2;

    appendSheet(app->getAppName());//写入表头
    setCellValue(1, 1, "评论ID");
    setCellValue(1, 2, "评论主题");
    setCellValue(1, 3, "评论内容");
    setCellValue(1, 4, "评论置信度");

    setCellValue(1, 6, "标注ID");
    setCellValue(1, 7, "评论ID");
    setCellValue(1, 8, "标注时间");
    setCellValue(1, 9, "标注类型");
    setCellValue(1, 10, "标注置信度");
    setCellValue(1, 11, "标注内容");
    setCellValue(1, 12, "标注备注");

    setCellValue(1, 14, "审阅ID");
    setCellValue(1, 15, "标注ID");
    setCellValue(1, 16, "审阅时间");
    setCellValue(1, 17, "审阅类型");
    setCellValue(1, 18, "审阅置信度");
    setCellValue(1, 19, "标注内容");

    for (int i = 0; i < comments.size(); i ++) {//写入评论
        setCellValue(i + 2, 1, comments[i]->getCmtID());
        setCellValue(i + 2, 2, comments[i]->getCmtTheme());
        setCellValue(i + 2, 3, comments[i]->getCmtContent());
        setCellValue(i + 2, 4, QString::number(comments[i]->getCmtCreddit()));
        QList<Mark*> marks = db.queryMark(comments.at(i)->getCmtID(), Mark::COMMENT_ID);
        qint32 m_len = marks.size();
        for (int j = 0; j < m_len; j ++) {//写入标注
            setCellValue(markCount, 6, marks[j]->getMarkId());
            setCellValue(markCount, 7, comments[i]->getCmtID());
            setCellValue(markCount, 8, marks[j]->getAddTime());
            setCellValue(markCount, 9, QString::number(marks[j]->getMarkClass()));
            setCellValue(markCount, 10, QString::number(marks[j]->getMarkCredit()));
            setCellValue(markCount, 11, marks[j]->getMarkContent());
            setCellValue(markCount, 12, marks[j]->getMarkNode());
            markCount ++;
            QList<Correction*> corrections = db.queryCorrection(marks[j]->getMarkId(), Correction::MARK_ID);
            qint32 c_len = corrections.size();
            for (int k = 0; k < c_len; k ++)
            {
                setCellValue(correctionCount, 14, corrections[k]->getCorrectID());
                setCellValue(correctionCount, 15, marks[j]->getMarkId());
                setCellValue(correctionCount, 16, corrections[k]->getCorrectTime());
                setCellValue(correctionCount, 17, QString::number(corrections[k]->getMarkClass()));
                setCellValue(correctionCount, 18, QString::number(corrections[k]->getMarkCreddit()));
                setCellValue(correctionCount, 19, corrections[k]->getMarkContent());
                correctionCount ++;
            }
        }
    }


}

void FileController::newExcel(const QString fileName)
{
    qApplication = new QAxObject();
    qApplication->setControl("Excel.Application"); //连接Excel控件
    qApplication->dynamicCall("SetVisible(bool)", false); //false不显示窗体
    qApplication->setProperty("DisplayAlerts", false); //不显示任何警告信息。
    qWorkBooks = qApplication->querySubObject("Workbooks");
    QFile file(fileName);
    if(file.exists()){
        qWorkBook = qWorkBooks->querySubObject("Open(const QString &)", fileName);
    }
    else{
        qWorkBooks->dynamicCall("Add");
        qWorkBook = qApplication->querySubObject("ActiveWorkBook");
    }

    //默认有一个sheet
    qSheets = qWorkBook->querySubObject("Sheets");
    qSheet = qSheets->querySubObject("Item(int)", 1);
}

void FileController::openExcel(const QString fileName)
{
    DataBaseController& db = DataBaseController::getInstance();
    UserController& uc = UserController::getInstance();
    if(qApplication == nullptr)
    {
        qApplication = new QAxObject();
        qApplication->setControl("Excel.Application"); //连接Excel控件
        qApplication->dynamicCall("SetVisible(bool)", false); //false不显示窗体
        qApplication->setProperty("DisplayAlerts", false); //不显示任何警告信息。
        qWorkBooks = qApplication->querySubObject("Workbooks");
    }
    QFile file(fileName);
    qWorkBook = qWorkBooks->querySubObject("Open(const QString &)", fileName);
    //默认有一个sheet
    qSheets = qWorkBook->querySubObject("Sheets");
    int sheetNum = qSheets->property("Count").toInt();
    for (int i = 2; i <= sheetNum; i ++) {
        qSheet = qSheets->querySubObject("Item(int)", i);
        QString appName = qSheet->property("Name").toString();
        //db.insertApp(uc.getFormalUser()->getUserId(), appName, "1.0");
        QAxObject *usedRange = qSheet->querySubObject("UsedRange");
        QVariant cell = usedRange->dynamicCall("Value");
        QVariantList cellList = cell.toList();
        qint32 row = cellList.size();
        for (qint32 j = 1; j < row; j ++) //导入评论
        {
            QVariantList rowList = cellList[j].toList();
            QString cmtId = rowList[0].toString();
            if (cmtId != "")
                db.insertOldComment(rowList[0].toString(), appName, rowList[1].toString(), rowList[2].toString(), rowList[3].toInt());
            else
                break;
        }
        for (qint32 j = 1; j < row; j ++) //导入标注
        {
            QVariantList rowList = cellList[j].toList();
            QString markId = rowList[5].toString();
            if (markId != "")
                db.insertOldMark(rowList[5].toString(), uc.getFormalUser()->getUserId(), rowList[6].toString(), rowList[7].toInt(), rowList[8].toInt(), rowList[9].toString(), rowList[10].toString());
            else
                break;
        }
        for (qint32 j = 1; j < row; j ++) //导入审阅
        {
            QVariantList rowList = cellList[j].toList();
            QString correctId = rowList[12].toString();
            if (correctId != "")
                db.insertOldCorrect(correctId, rowList[13].toString(), rowList[14].toInt(), rowList[15].toInt(), rowList[16].toString());
        }
    }
}

void FileController::appendSheet(const QString sheetName)
{
    int cnt = 1;
    QAxObject *qLastSheet = qSheets->querySubObject("Item(int)", cnt);
    qSheets->querySubObject("Add(QVariant)", qLastSheet->asVariant());
    qSheet = qSheets->querySubObject("Item(int)", cnt);
    qLastSheet->dynamicCall("Move(QVariant)", qSheet->asVariant());
    qSheet->setProperty("Name", sheetName);
}

void FileController::setCellValue(int row, int column, const QString value)
{
    QAxObject *qRange = qSheet->querySubObject("Cells(int,int)", row, column);
    qRange->dynamicCall("Value", value);
    //内容居中
    qRange->setProperty("HorizontalAlignment", -4108);
    qRange->setProperty("VerticalAlignment", -4108);
    if(row == 1){
    //加粗
        QAxObject *font = qRange->querySubObject("Font"); //获取单元格字体
        font->setProperty("Bold",true); //设置单元格字体加粗
    }
}

void FileController::saveExcel(const QString fileName)
{
    qWorkBook->dynamicCall("SaveAs(const QString &)",
    QDir::toNativeSeparators(fileName));
}

void FileController::freeExcel()
{
    if (qApplication != NULL){
        qApplication->dynamicCall("Quit()");
        delete qApplication;
        qApplication = NULL;
    }
}
