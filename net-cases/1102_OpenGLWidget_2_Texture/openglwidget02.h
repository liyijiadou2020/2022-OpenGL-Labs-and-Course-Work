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

private:
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;

    QOpenGLShaderProgram m_program;

    QOpenGLTexture *m_texture = nullptr;

};

#endif // OPENGLWIDGET02_H
