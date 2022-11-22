#include "openglwidget02.h"

OpenGLWidget02::OpenGLWidget02(QWidget* parent)
    : QOpenGLWidget(parent)
{
    startTimer(1000 / 60);

    //    初始化摄像机
    m_camera.move(-6, 0, 3);
    m_camera.look(0, 30, 0);
    m_camera.update();
    //    安装事件过滤器以便可以监控用户的操作
    installEventFilter(&m_camera);
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

//    m_texture = new QOpenGLTexture(QImage(":/pic/1.jpg").mirrored());
    m_texture = new QOpenGLTexture(QImage(":/pic/02.png")); // 注意，因为纹理坐标修改了，所以我们这次加载图像的时候不需要镜像了。

    /* 3.使用缓存和着色器 */    
    /* 3.1 顶点和纹理 */
    // 顶点缓存中前三个是顶点坐标, 后两个是纹理坐标, 一个顶点由5个float值组成
    float _vertex[] = { // 24 * 5 = 120
        //顶点						纹理
        // 1
            -1,  1,  1,		0.50, 0.25,	// 左上
            -1, -1,  1,		0.50, 0.50,	// 左下
             1, -1,  1,		0.75, 0.50,	// 右下
             1,  1,  1,		0.75, 0.25,  // 右上
        // 6
             1,  1, -1,		0.00, 0.25,	// 左上
             1, -1, -1,		0.00, 0.50,	// 左下
            -1, -1, -1,		0.25, 0.50,	// 右下
            -1,  1, -1,		0.25, 0.25,	// 右上
        // 2
             1,	 1,  1,		0.75, 0.25,  // 左上
             1,	-1,  1,		0.75, 0.50,	// 左下
             1,	-1, -1,		1.00, 0.50,	// 右下
             1,	 1, -1,		1.00, 0.25,	// 右上
        // 5
            -1,  1, -1,		0.25, 0.25,	// 左上
            -1, -1, -1,		0.25, 0.50,	// 左下
            -1, -1,  1,		0.50, 0.50,	// 右下
            -1,  1,  1,		0.50, 0.25,	// 右上
        // 3
            -1,  1, -1,		0.00, 0.00,	// 左上
            -1,  1,  1,		0.00, 0.25,	// 左下
             1,  1,  1,		0.25, 0.25,  // 右下
             1,  1, -1,		0.25, 0.00,	// 右上
        // 4
            -1, -1,  1,		0.00, 0.50,  // 左上
            -1, -1, -1,		0.00, 0.75,	// 左下
             1, -1, -1,		0.25, 0.75,	// 右下
             1, -1,  1,		0.25, 0.50,	// 右上
    };

    m_vao.bind();
    m_vbo.bind();

    m_vbo.allocate(_vertex, 120 * sizeof(float));
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

    /* 3.2 视图矩阵：用于模拟摄像机 */
    m_view.setToIdentity();
    m_view.lookAt(QVector3D(3, 3, 3), QVector3D(0, 0, 0), QVector3D(0, 1, 0));


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
    // 绑定变换矩阵
    m_program.setUniformValue("projection", m_projection);
    m_program.setUniformValue("view", m_camera.view());
    m_program.setUniformValue("model", m_model);

    //  GL_TRIANGLE_FAN就是之前提到的另一种绘制三角形的方法，它允许我们逆时针定义四个顶点，然后绘制出来两个三角形组成一个矩形。
    for (int i = 0; i < 6; ++i) {
       glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
    }

    m_program.release();
    m_vao.release();
    m_texture->release();
}

void OpenGLWidget02::resizeGL(int w, int h)
{
    m_projection.setToIdentity();
    m_projection.perspective(60, (float)w / h, 0.001, 1000);
}

void OpenGLWidget02::timerEvent(QTimerEvent *event)
{
    m_camera.update(); // 调用摄像机的update函数，以便定时计算运动位置和视图矩阵。

    m_angle += 1;
    if (m_angle >= 360)
        m_angle = 0;
    m_model.setToIdentity();
    m_model.rotate(m_angle, 0, 1, 0);

    repaint();
}
