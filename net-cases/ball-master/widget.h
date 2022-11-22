#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QWheelEvent>
#include <QMainWindow>

#include "ballshader.h"
class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    BallShader m_shader; //球渲染器
    QMatrix4x4 m_pMatrix,m_modelMatrix; //投影矩阵、基本转换矩阵
    QVector3D m_eye, m_target; //视点,和目标
};

#endif // WIDGET_H
