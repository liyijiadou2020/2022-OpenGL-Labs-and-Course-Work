#pragma once
#include <QObject>
#include <QMatrix4x4>
#include <QVector3D>
#include <QOpenGLWidget>
#include <QEvent>
#include <QKeyEvent>


class Camera : public QObject
{
    Q_OBJECT
public:
    Camera(QObject *parent = nullptr);
    ~Camera();
public:
    void look(float yaw, float pitch, float roll);
    void move(float x, float y, float z);
public:
    void update(); // 计算最终的运动距离和最终的视图矩阵
    QMatrix4x4 view() { return m_view; }
protected:
    // eventFilter表示本类可以用于监控在其它类中发生的事件
    // 这里用来监控窗口类中的鼠标和键盘事件
    bool eventFilter(QObject *obj, QEvent *ev) override;
private:
    QMatrix4x4 m_view;
    QVector3D m_pos{ 0,0,0 };
    QVector3D m_front{ 0,0,-1 };
    QVector3D m_up{ 0,1,0 };
    float m_yaw = 0;
    float m_pitch = 0;
    float m_roll = 0;

    QVector3D m_move;
    float m_moveSpeed=0.1 ;
    float m_lookSpeed=0.1 ;


};
