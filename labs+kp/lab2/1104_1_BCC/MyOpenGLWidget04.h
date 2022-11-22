#pragma once

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QTime>

#include "Camera.h"
#include "CubeModel.h"

class MyOpenGLWidget04 : public QOpenGLWidget, public QOpenGLExtraFunctions
{
	Q_OBJECT

public:
    MyOpenGLWidget04(QWidget *parent = nullptr);
    ~MyOpenGLWidget04();
protected:
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;

    virtual void timerEvent(QTimerEvent *event);
    virtual void keyPressEvent(QKeyEvent* event);

private:
    // 在绘制的时候需要知道这3个信息，才能计算光照和材质
	QMatrix4x4 m_projection;
	Camera m_camera;
	Light m_light;

	QVector<Model *> m_models;
	Model *m_lightModel;
    // 用来绘制十字架
    void _generateCenterCross(QPainter&);
public:
    void move3DShape(QVector3D step); /* 移动图形 */
    void changeColorOfLight();
public: 
    bool is_move_ball=false;
    bool is_move_cone=false;
    bool is_move_dice=false;
    bool is_change_color=false;
signals:

public slots:
    void updateGL();

private:
    QTime m_time;



};
