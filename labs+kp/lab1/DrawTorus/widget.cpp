#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    connect(&tm_,SIGNAL(timeout()),this,SLOT(slotTimeout()));
    tm_.start(60);
}

Widget::~Widget()
{

}

void Widget::initializeGL()
{
    render_.initsize(0.9, 0.7, 13, 30);
    camera_.setX(3);
    camera_.setY(0);
    camera_.setZ(3);
}

void Widget::resizeGL(int w, int h)
{
    pMatrix_.setToIdentity();
    pMatrix_.perspective(45,float(w)/h,0.01f,100.0f);
}

void Widget::paintGL()
{
    QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();
    f->glClearColor(0.2f,0.3f,0.3f,1.0f);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 vMatrix;
    vMatrix.lookAt(camera_, QVector3D(0.0,0.0,0.0), QVector3D(0.0,1.0,0.0));

    QMatrix4x4 mMatrix;
    mMatrix.rotate(angleX_,1,0,0);
    mMatrix.rotate(angleY_,0,1,0);
    mMatrix.rotate(angleZ_,0,0,1);
    if (is_change_scale) {
        mMatrix.scale(0.3);
    }
    render_.render(f,pMatrix_,vMatrix,mMatrix);
}

void Widget::slotTimeout()
{
    angleX_ += 1;
    angleY_ += 1;
    angleZ_ += 1;
    update();
}
