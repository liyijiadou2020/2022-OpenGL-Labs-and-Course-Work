#include "OpenGLTest.h"
#include <QtWidgets/QApplication>
#include "OpenGLWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OpenGLWidget w;
    w.show();
    return a.exec();
}
