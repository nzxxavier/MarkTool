#include "View/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/img/start.jpg");
    QSplashScreen screen(pixmap);
    int delayTime = 2;
    QElapsedTimer timer;
    timer.start();
    screen.show();
    while(timer.elapsed() < (delayTime * 1000))
    {
         a.processEvents();
    }
    MainWindow w;
    w.showMaximized();
    screen.finish(&w);
    return a.exec();
}
