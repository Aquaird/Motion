#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <GL/glu.h>
#include <GL/glut.h>

//struct stu
//{
//    unsigned int item_num = 122;
//    unsigned int row_num = 1;
//    double _data[item_num];
//    unsigned int _index[row_num];
//};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    glutInit(&argc,argv);
    MainWindow w;
    w.resize(w.sizeHint());

    int desktopArea = QApplication::desktop()->width() * QApplication::desktop()->height();
    int widgetArea = w.width() * w.height();
    w.setWindowTitle("OpenGL Motion");

    if(((float)widgetArea / (float)desktopArea) < 0.75f)
        w.show();
    else
        w.showMaximized();

    return a.exec();
}
