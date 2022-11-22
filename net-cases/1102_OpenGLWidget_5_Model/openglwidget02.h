#ifndef OPENGLWIDGET02_H
#define OPENGLWIDGET02_H

/* 继承的父类 */
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
/* VAO和VBO */
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
/* 着色器 */
#include <QOpenGLShaderProgram>
/* 纹理 */
#include <QOpenGLTexture>
/* 自定义的摄像机类*/
#include "camera.h"


class OpenGLWidget02 : public QOpenGLWidget, public QOpenGLExtraFunctions
{
    Q_OBJECT

public:
    OpenGLWidget02(QWidget* parent);
    ~OpenGLWidget02();
protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void timerEvent(QTimerEvent *event);

private:
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;

    QOpenGLShaderProgram m_program;

    QOpenGLTexture *m_texture = nullptr;

    /* 变换矩阵 */
    QMatrix4x4 m_projection; //投影矩阵负责让你看到的画面，符合近大远小的透视规律，并且保证无论你的窗口的宽高比是多少，你看到的画面都不会再变形了。
    QMatrix4x4 m_view; //视图矩阵负责模拟一个摄像机的镜头，让你可以在3D空间中的某个位置去观察另一个位置。
    QMatrix4x4 m_model; //模型矩阵负责让你绘制模型的时候，可以顺便对它进行缩放，旋转，平移的操作。
    float m_angle=1; // 每帧旋转的角度

    /* 摄像机类 */
    /*
     * WASD：摄像机前后左右移动方向
     * C：摄像机沿着Z轴向下
     * Space：摄像机沿着Z轴向上
     * 鼠标：摄像机移动视角
     * Esc：窗口不再追踪鼠标
     */
    Camera m_camera;

};

#endif // OPENGLWIDGET02_H
