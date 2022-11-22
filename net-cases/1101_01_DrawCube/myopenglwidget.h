#pragma once
#include <QOpenGLWidget>
#include <qopenglfunctions_4_3_core.h>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QVector3D>

class MyOpenglWedgit : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core
{
    Q_OBJECT

public:
    float cameraX, cameraY, cameraZ;
    GLuint mvMatrixLocation, projMatrixLocation;
    float aspect;
    QMatrix4x4 pMat, vMat, mMat, mvMat;
    // shape
    bool isDrawCube;
    bool isMoveCube;

    bool isDrawBall;
    bool isMoveBall;

    // cube
    float cubeLocX, cubeLocY, cubeLocZ;
    QOpenGLShaderProgram programCube_;
    QOpenGLBuffer vaoCube_;
    QVector<GLfloat> pointsCube_;
    void setupVerticesCube();
    // ------

    // ball
    float ballLocX, ballLocY, ballLocZ;
    QOpenGLShaderProgram programBall_;
    QOpenGLBuffer vboBall_;
    QVector<GLfloat> pointsBall_;
    float radius_=2.0;
    void setupVerticesBall(float r=2.0);
    void renderBall(QOpenGLExtraFunctions *f, QMatrix4x4 &projM, QMatrix4x4 &camera, QMatrix4x4 &model);
    // ------



    MyOpenglWedgit(QWidget*parent);
    ~MyOpenglWedgit();

protected:

    void initializeGL();
    void resizeGL();
    void paintGL();
};
