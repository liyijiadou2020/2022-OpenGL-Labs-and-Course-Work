#ifndef FOXOPENGLWIDGET_H
#define FOXOPENGLWIDGET_H
#include <QOpenGLWidget>  // 相当于GLFW
#include <QOpenGLFunctions_4_5_Core>  // 相当于 GLAD
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QTime>
#include <QOpenGLTexture>
#include "camera.hpp"
#include "sphere.hpp"
#include "cone.hpp"
#include "cube.hpp"

class FoxOpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_4_5_Core
{
    Q_OBJECT

public:
    bool is_draw_sphere;
    bool is_move_sphere;
    bool is_draw_cone;
    bool is_move_cone;
    bool is_draw_cube;
    bool is_move_cube;

public:
    explicit FoxOpenGLWidget(QWidget* parent = nullptr);
    ~FoxOpenGLWidget();
    void setWirefame(bool wirefame);  /* 设置线框模式是否开启 */
    void move3DShape(QVector3D step); /* 移动图形 */
protected:    
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    /* 处理键盘、鼠标事件 */
    void keyPressEvent(QKeyEvent* event);
    void mouseMoveEvent(QMouseEvent* event);    // 鼠标移动
    void wheelEvent(QWheelEvent* event);        // 鼠标滚轮

signals:

public slots:
    void updateGL();

private:    
    Sphere _sphere;
    QOpenGLShaderProgram _sp_sphere;
    Cone _cone;
    QOpenGLShaderProgram _sp_cone;
    Cube _cube;
    QOpenGLShaderProgram _sp_cube;

    QTimer timer_;  // 【重点】 这里是 Timer - 计时器类
    QTime time_; /* 时钟及计时器 */

    Camera camera_; /* 封装的摄像机类 */
};

#endif // FOXOPENGLWIDGET_H
