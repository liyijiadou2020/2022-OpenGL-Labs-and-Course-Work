#include "camera.h"


void Camera::update()
{
    auto _move = m_move.normalized() * m_moveSpeed;
    move(_move.x(), _move.y(), _move.z());

    m_view.setToIdentity();
    m_view.lookAt(m_pos, m_pos + m_front, m_up);
}

Camera::Camera(QObject *parent)
{

}

Camera::~Camera()
{

}

void Camera::look(float yaw, float pitch, float roll)
{
    m_yaw += yaw;
    while (m_yaw >= 360)
        m_yaw -= 360;
    while (m_yaw < 0)
        m_yaw += 360;
    m_pitch += pitch;
    if (m_pitch > 89)
        m_pitch = 89;
    if (m_pitch < -89)
        m_pitch = -89;
    {
        QVector3D _front{ 0,0,-1 };
        QMatrix4x4 _mat;
        _mat.setToIdentity();
        _mat.rotate(m_pitch, 1, 0, 0);
        _mat.rotate(m_yaw, 0, 1, 0);
        m_front = _front * _mat;
    }
}

void Camera::move(float x, float y, float z)
{
    auto _right = QVector3D::crossProduct(m_front, m_up).normalized();
    auto _front = QVector3D::crossProduct(m_up, _right).normalized();
    m_pos += _front * x;
    m_pos += _right * y;
    m_pos += m_up * z;
}
/*
 * WASD：摄像机前后左右移动方向
 * C：摄像机沿着Z轴向下
 * Space：摄像机沿着Z轴向上
 * 鼠标：摄像机移动视角
 * Esc：窗口不再追踪鼠标
 */
bool Camera::eventFilter(QObject *obj, QEvent *ev)
{
    auto _widget = qobject_cast<QOpenGLWidget *>(obj);
    if (_widget)
    {
        if (ev->type() == QEvent::KeyPress)
        { // 没办法检测键盘
            auto event = static_cast<QKeyEvent *>(ev);
            if (event->key() == Qt::Key_Escape)
            {
                _widget->setMouseTracking(false);
                _widget->setCursor(Qt::ArrowCursor);
            }
            else if (event->key() == Qt::Key_W)
            {
                m_move.setX(1);
            }
            else if (event->key() == Qt::Key_S)
            {
                m_move.setX(-1);
            }
            else if (event->key() == Qt::Key_A)
            {
                m_move.setY(-1);
            }
            else if (event->key() == Qt::Key_D)
            {
                m_move.setY(1);
            }
            else if (event->key() == Qt::Key_Space)
            {
                m_move.setZ(1);
            }
            else if (event->key() == Qt::Key_C)
            {
                m_move.setZ(-1);
            }
        }
        else if (ev->type() == QEvent::KeyRelease)
        { //不再按键盘的时候就改变位置的值
            auto event = static_cast<QKeyEvent *>(ev);
            if (event->key() == Qt::Key_W)
            {
                m_move.setX(0);
            }
            else if (event->key() == Qt::Key_S)
            {
                m_move.setX(0);
            }
            else if (event->key() == Qt::Key_A)
            {
                m_move.setY(0);
            }
            else if (event->key() == Qt::Key_D)
            {
                m_move.setY(0);
            }
            else if (event->key() == Qt::Key_Space)
            {
                m_move.setZ(0);
            }
            else if (event->key() == Qt::Key_C)
            {
                m_move.setZ(0);
            }
        }
        else if (ev->type() == QEvent::MouseButtonPress)
        { // 检测鼠标。记得添加widget的聚焦，这样才能使用键盘
            _widget->setFocus();

            auto _lastPos = _widget->mapToGlobal(_widget->rect().center());
            QCursor::setPos(_lastPos);

            _widget->setMouseTracking(true);
            _widget->setCursor(Qt::BlankCursor);
        }
        else if (ev->type() == QEvent::MouseMove)
        {
            auto event = static_cast<QMouseEvent *>(ev);
            auto _lastPos = _widget->mapToGlobal(_widget->rect().center());
            QCursor::setPos(_lastPos);

            auto _move = event->globalPos() - _lastPos;
            look(_move.x() * m_lookSpeed, _move.y() * m_lookSpeed, 0);
        }
        else if (ev->type() == QEvent::Leave)
        {
            _widget->setMouseTracking(false); //Esc键表示不再捕获鼠标，对应到Qt中就是窗口不再追踪鼠标
            _widget->setCursor(Qt::ArrowCursor);
        }
    }
    return false;
}

