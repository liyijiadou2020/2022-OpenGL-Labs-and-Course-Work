#include "widget.h"


// 初始视点和目标位置
Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent),
      m_eye(-2,-2,1), //初始视点位置
      m_target(0,0,-1) //初始观察目标位置
{

}

Widget::~Widget()
{

}

void Widget::initializeGL()
{
    m_shader.initialize(0.8); //初始化半径为0.8的球体数据    
}

void Widget::paintGL()
{
    // 线框模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();
    f->glClearColor(0.0, 0.0, 0.0, 0.0);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_modelMatrix.rotate(30,0,1,0); //每次刷新绕y轴旋转30度

    QMatrix4x4 camera;
    camera.lookAt(m_eye,m_target,QVector3D{0,1,0}); //生成摄像机矩阵
    m_shader.render(f,m_pMatrix,camera,m_modelMatrix); //渲染
}

void Widget::resizeGL(int w, int h)
{
    m_pMatrix.setToIdentity(); //重置为单位矩阵
    m_pMatrix.perspective(60.0f,GLfloat(w)/h,0.01f,100.0f); //设置投影
}

void Widget::wheelEvent(QWheelEvent *event)
{
    if (! event->pixelDelta().isNull()) {
        m_eye.setZ(m_eye.z() + event->pixelDelta().y()); //重置视点z值
    } else if (!event->angleDelta().isNull()) {
        m_eye.setZ(m_eye.z() + (event->angleDelta() / 120).y()); //重置视点z值
    }

    event->accept();
    update();
}
