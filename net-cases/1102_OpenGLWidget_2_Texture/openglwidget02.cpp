#include "openglwidget02.h"

OpenGLWidget02::OpenGLWidget02(QWidget* parent)
    : QOpenGLWidget(parent)
{

}

OpenGLWidget02::~OpenGLWidget02()
{

}

void OpenGLWidget02::initializeGL()
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
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /* 2.创建缓存和着色器 */
    m_vao.create();
    m_vbo.create();

    m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader.vert");
    m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader.frag");
    m_program.link();

    m_texture = new QOpenGLTexture(QImage(":/pic/20210928.jpg").mirrored());

    /* 3.使用缓存和着色器 */    
    float _vertex[] = { // 顶点缓存中前三个是顶点坐标, 后两个是纹理坐标, 一个顶点由5个float值组成
    //  顶点			纹理
        -0.5,  0.5, 0,	0, 1, // 左上
        -0.5, -0.5, 0,	0, 0, // 左下
         0.5, -0.5, 0,	1, 0, // 右下
         0.5,  0.5, 0,	1, 1 // 右上
    };


    m_vao.bind();
    m_vbo.bind();

    m_vbo.allocate(_vertex, 20 * sizeof(float));
    // m_vbo.allocate(_vertex, sizeof(_vertex));

    m_program.bind();
    // 参数1：shader中的输入参数的名字，
    // 参数2：顶点缓存中的数据类型，
    // 参数3：顶点缓存中从第几个点开始才是有用的数据，
    // 参数4：步长，表示下一个数据需要偏移多少个字节
    // 绑定顶点坐标信息
    m_program.setAttributeBuffer("vPos", GL_FLOAT, 0 * sizeof(float), 3, 5 * sizeof(float));
    m_program.enableAttributeArray("vPos");
    // 绑定纹理坐标信息
    m_program.setAttributeBuffer("vTexture", GL_FLOAT, 3 * sizeof(float), 2, 5 * sizeof(float));
    m_program.enableAttributeArray("vTexture");


    /* 4. 清理工作：释放VAO和shader*/
    m_program.release();
    m_vao.release();

}

void OpenGLWidget02::paintGL()
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
    m_texture->bind();
    m_vao.bind();
    m_program.bind();

    //  GL_TRIANGLE_FAN就是之前提到的另一种绘制三角形的方法，它允许我们逆时针定义四个顶点，然后绘制出来两个三角形组成一个矩形。
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    m_program.release();
    m_vao.release();
    m_texture->release();
}

void OpenGLWidget02::resizeGL(int w, int h)
{
    Q_UNUSED(w);Q_UNUSED(h);
}
