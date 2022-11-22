#include "ballshader.h"

// 1. 编译，链接着色器
// 2. 生成球面顶点，放入m_points
// 3. 将m_points中的点传入vbo
void BallShader::initialize(float r)
{
    m_program.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,"shapes.vert");
    m_program.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,"shapes.frag");
    m_program.link();

    m_r = r;
    int angleSpan = 10; //弧度 = 角度 * PI / 180
    for(int vAngle = -90; vAngle < 90; vAngle = vAngle + angleSpan){ //生成球面顶点
        for(int hAngle = 0; hAngle <= 360; hAngle = hAngle + angleSpan){
            float x0 = r * ::cos(vAngle * PI / 180) * ::cos(hAngle * PI / 180);
            float y0 = r * ::cos(vAngle * PI / 180) * ::sin(hAngle * PI / 180);
            float z0 = r * ::sin(vAngle * PI / 180);

            float x1 = r * ::cos(vAngle * PI / 180) * ::cos((hAngle + angleSpan) * PI / 180);
            float y1 = r * ::cos(vAngle * PI / 180) * ::sin((hAngle + angleSpan) * PI / 180);
            float z1 = r * ::sin(vAngle * PI / 180);

            float x2 = r * ::cos((vAngle + angleSpan) * PI / 180) * ::cos((hAngle + angleSpan) * PI / 180);
            float y2 = r * ::cos((vAngle + angleSpan) * PI / 180) * ::sin((hAngle + angleSpan) * PI / 180);
            float z2 = r * ::sin((vAngle + angleSpan) * PI / 180);

            float x3 = r * ::cos((vAngle + angleSpan) * PI / 180) * ::cos(hAngle * PI / 180);
            float y3 = r * ::cos((vAngle + angleSpan) * PI / 180) * ::sin(hAngle * PI / 180);
            float z3 = r * ::sin((vAngle + angleSpan) * PI / 180);

            m_points << x1 << y1 << z1 << x3 << y3 << z3
                   << x0 << y0 << z0 << x1 << y1 << z1
                   << x2 << y2 << z2 << x3 << y3 << z3;
        }
    }
    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(m_points.constData(),m_points.count() * sizeof (GLfloat));
}

// #TODO: 这个f是拿来干嘛的？

void BallShader::render(QOpenGLExtraFunctions *f, QMatrix4x4 &projM, QMatrix4x4 &camera, QMatrix4x4 &model)
{
    f->glEnable(GL_DEPTH_TEST);
    f->glEnable(GL_CULL_FACE);
    m_program.bind();
    m_vbo.bind();
    m_program.setUniformValue("uPMatrix",projM);
    m_program.setUniformValue("camMatrix",camera);
    m_program.setUniformValue("uMMatrix",model);
    m_program.setUniformValue("uR",m_r);
    m_program.enableAttributeArray(0);

    m_program.setAttributeBuffer(0,GL_FLOAT,0,3,0);

    f->glDrawArrays(GL_TRIANGLES,0,m_points.count() / 3);

    m_program.disableAttributeArray(0);
    m_vbo.release();
    m_program.release();
    f->glDisable(GL_DEPTH_TEST);
    f->glDisable(GL_CULL_FACE);
}
