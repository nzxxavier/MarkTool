QT       += core gui
QT       += sql
QT       += concurrent
QT       += charts

RC_ICONS = icon.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += qaxcontainer

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/databasecontroller.cpp \
    Controller/filecontroller.cpp \
    Controller/uuidcontroller.cpp \
    Model/app.cpp \
    Model/comment.cpp \
    Model/correction.cpp \
    Model/mark.cpp \
    Model/user.cpp \
    View/commentwidget.cpp \
    View/correctwidget.cpp \
    View/datawidget.cpp \
    View/historymarkwidget.cpp \
    View/mainwindow.cpp \
    View/addappdialog.cpp \
    View/dbconfigdialog.cpp \
    View/logindialog.cpp \
    View/markwidget.cpp \
    View/mymessagebox.cpp \
    View/myscrollwidget.cpp \
    View/tocorrectwidget.cpp \
    main.cpp

HEADERS += \
    Controller/databasecontroller.h \
    Controller/filecontroller.h \
    Controller/usercontroller.h \
    Controller/uuidcontroller.h \
    Model/app.h \
    Model/comment.h \
    Model/correction.h \
    Model/mark.h \
    Model/user.h \
    View/commentwidget.h \
    View/correctwidget.h \
    View/datawidget.h \
    View/historymarkwidget.h \
    View/mainwindow.h \
    View/mainwindow.h \
    View/addappdialog.h \
    View/dbconfigdialog.h \
    View/logindialog.h \
    View/markwidget.h \
    View/mymessagebox.h \
    View/myscrollwidget.h \
    View/tocorrectwidget.h

FORMS += \
    View/commentwidget.ui \
    View/correctwidget.ui \
    View/datawidget.ui \
    View/historymarkwidget.ui \
    View/mainwindow.ui \
    View/mainwindow.ui \
    View/addappdialog.ui \
    View/dbconfigdialog.ui \
    View/logindialog.ui \
    View/markwidget.ui \
    View/mymessagebox.ui \
    View/myscrollwidget.ui \
    View/tocorrectwidget.ui

RESOURCES += \
    Resource/image.qrc
