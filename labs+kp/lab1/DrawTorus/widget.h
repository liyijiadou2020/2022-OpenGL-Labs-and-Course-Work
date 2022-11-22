#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include "torusrender.h"


class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
public:
    bool is_change_scale=false;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    QTimer tm_;
    TorusRender render_;
    QMatrix4x4 pMatrix_;
    qreal angleX_ = 0,angleY_ = 0,angleZ_ = 0;
    QVector3D camera_;

private slots:
    void slotTimeout();
};

#endif // WIDGET_H
