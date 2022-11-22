#ifndef BALLSHADER_H
#define BALLSHADER_H

#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>


#define PI 3.14159265f

class BallShader
{
public:
    BallShader() = default;
    void initialize(float r);
    void render(QOpenGLExtraFunctions *f,QMatrix4x4 &projM,QMatrix4x4 & camera,QMatrix4x4 &model);

private:
    QOpenGLShaderProgram m_program;
    QOpenGLBuffer m_vbo;
    QVector<GLfloat> m_points;

    float m_r;
};

#endif // BALLSHADER_H
