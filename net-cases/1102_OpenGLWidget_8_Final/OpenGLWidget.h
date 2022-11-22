#pragma once

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include "Camera.h"
#include "Dice.h"

class MyOpenGLWidget03 : public QOpenGLWidget, public QOpenGLExtraFunctions
{
	Q_OBJECT

public:
    MyOpenGLWidget03(QWidget *parent = nullptr);
    ~MyOpenGLWidget03();
protected:
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;

	virtual void timerEvent(QTimerEvent *event);    

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



};
