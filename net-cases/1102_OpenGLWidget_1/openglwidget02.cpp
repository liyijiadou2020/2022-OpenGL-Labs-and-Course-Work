#include "openglwidget02.h"

QOpenGLWidget02::QOpenGLWidget02(QWidget* parent)
    : QOpenGLWidget(parent)
{

}

QOpenGLWidget02::~QOpenGLWidget02()
{

}

void QOpenGLWidget02::initializeGL()
{
    /*
        初始化OpenGL函数
        初始化各种flag
        创建各种缓存对象
        创建并链接shader
        启用shader
        启用缓存
        绑定缓存（加载不变的数据）
        绑定shader的缓存数据（告诉OpenGL如何从缓存中读取数据到shader中）
        释放缓存
        释放shader
    */

    /* 1.做一些基本的初始化：初始化OpenGL函数；设置一些OpenGL的特性，例如深度测试；设置一下刷新时的背景颜色 */
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0.5, 0.7, 1);

    /* 2.创建缓存和着色器 */
    m_vao.create();
    m_vbo.create();

    m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader.vert");
    m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader.frag");
    m_program.link();

    /* 3.使用缓存和着色器 */
    float _vertex[] = {
         0.0,  0.5, 0.0,
        -0.5, -0.5, 0.0,
         0.5, -0.5, 0.0,
    };

    m_vao.bind();
    m_vbo.bind();

    m_vbo.allocate(_vertex, 9 * sizeof(float));
    // m_vbo.allocate(_vertex, sizeof(_vertex));

    m_program.bind();
    // 参数1：shader中的输入参数的名字， 参数2：顶点缓存中的数据类型，
    // 参数3：顶点缓存中从第几个点开始才是有用的数据，
    // 参数4：点缓存中一个点需要用几个数据表示（既要和顶点缓存中的结构匹配，也要和shader中的输入变量的类型匹配，在本例子中为3）
    m_program.setAttributeBuffer("vPos", GL_FLOAT, 0, 3, 0);
    m_program.enableAttributeArray("vPos");

    /* 4. 清理工作：释放VAO和shader*/
    m_program.release();
    m_vao.release();

}

void QOpenGLWidget02::paintGL()
{
    /*
     *  清屏
     *  启用shader
     *  绑定shader的全局数据（例如摄像机变换矩阵，投影矩阵等）
     *  启用缓存
     *  绑定缓存（加载变化的数据）
     *  绑定shader的缓存数据（告诉OpenGL如何从缓存中读取数据到shader中）
     *  绘制（使用shader读取缓存中的内容，转换为顶点，然后按照命令基于顶点绘制3D数据）
     *  释放缓存
     *  释放shader
     */
    m_vao.bind();
    m_program.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);

    m_program.release();
    m_vao.release();
}

void QOpenGLWidget02::resizeGL(int w, int h)
{

}
