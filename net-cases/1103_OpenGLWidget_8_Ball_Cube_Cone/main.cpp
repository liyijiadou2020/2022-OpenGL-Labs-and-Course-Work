#include <QtWidgets/QApplication>
#include "MyOpenGLWidget03.h"
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    OpenGLWidget w;
    MainWindow w;
    w.show();

    return a.exec();
}
