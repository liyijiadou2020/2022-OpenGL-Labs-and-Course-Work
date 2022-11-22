//#include "stdafx.h"
#include "myopenglwidget.h"

#define PI 3.14159265f

MyOpenglWedgit::MyOpenglWedgit(QWidget*parent)
    : QOpenGLWidget(parent)
{

}

MyOpenglWedgit::~MyOpenglWedgit()
{

}
void MyOpenglWedgit::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);//设置深度缓存
    glDepthFunc(GL_LEQUAL);
    glClearColor(0.2, 0.3, 0.3, 0.5);//改变窗口的背景颜色
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);//进行透视校正
    cameraX = 0.0f; cameraY = 1.0f; cameraZ = 10.0f;

    // Cube
    this->isDrawCube = true;
    if (isDrawCube) {
        cubeLocX = 0.0f; cubeLocY = -2.0f; cubeLocZ = -2.0f;
        setupVerticesCube();

        mvMatrixLocation = programCube_.uniformLocation("mv_matrix");
        projMatrixLocation = programCube_.uniformLocation("proj_matrix");//获取程序的统一变量mv，投影矩阵
        //构建透视矩阵
        pMat.perspective(45, (float)width() / (float)height(), 0.1f, 1000.f);
        //构建视图矩阵
        vMat.translate(-cameraX, -cameraY, -cameraZ);
        mMat.translate(cubeLocX, cubeLocY, cubeLocZ);
        mvMat = vMat * mMat;
        //将mv矩阵发送给对应的统一变量
        programCube_.setUniformValue(mvMatrixLocation, mvMat);
        programCube_.setUniformValue(projMatrixLocation, pMat);
    }


    // Cube
    this->isDrawBall = true;
    if (isDrawBall) {
        ballLocX = 0.0f; ballLocY = 2.0f; ballLocZ = 2.0f;
        setupVerticesBall();

        mvMatrixLocation = programBall_.uniformLocation("mv_matrix");
        projMatrixLocation = programBall_.uniformLocation("proj_matrix");//获取程序的统一变量mv，投影矩阵
        //构建透视矩阵
        pMat.perspective(45, (float)width() / (float)height(), 0.1f, 1000.f);
        //构建视图矩阵
        vMat.translate(-cameraX, -cameraY, -cameraZ);
        mMat.translate(isDrawBall, ballLocY, ballLocZ);
        mvMat = vMat * mMat;
        //将mv矩阵发送给对应的统一变量
        programBall_.setUniformValue(mvMatrixLocation, mvMat);
        programBall_.setUniformValue(projMatrixLocation, pMat);
    }


}

void MyOpenglWedgit::resizeGL()
{
    glViewport(0, 0, width(), height());
}

void MyOpenglWedgit::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (this->isDrawCube) {
        // 绘制Cube
        GLuint vPosition = programCube_.attributeLocation("vPosition");
        programCube_.setAttributeBuffer(vPosition, GL_FLOAT,0,3,0);
        glEnableVertexAttribArray(vPosition);
        //调整OpenGL设置，绘制模型
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);//线框模式
        glDrawArrays(GL_TRIANGLES,0,36);
        // ----------
    }

    if (this->isDrawBall) {
        // 绘制Ball
        GLuint vPosition = programCube_.attributeLocation("vPosition");
        programCube_.setAttributeBuffer(vPosition, GL_FLOAT,0,3,0);
        glEnableVertexAttribArray(vPosition);
        //调整OpenGL设置，绘制模型
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);//线框模式
        QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();
        QMatrix4x4 camera;
        QVector3D m_eye = {0, 0, 1};
        QVector3D m_target = {0, 0, -1};
        camera.lookAt(m_eye, m_target, QVector3D{0,1,0}); //生成摄像机矩阵
        renderBall(f, pMat, camera, mMat);
        // ----------
    }

    MyOpenglWedgit::update();
}

void MyOpenglWedgit::setupVerticesCube() {
    // 着色器编译
    if (!programCube_.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader.vs")) {     //添加并编译顶点着色器
        qDebug() << "编译ERROR:" << programCube_.log();    //如果编译出错,打印报错信息
    }
    if (!programCube_.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader.fs")) {   //添加并编译片段着色器
        qDebug() << "编译ERROR:" << programCube_.log();    //如果编译出错,打印报错信息
    }
    if (!programCube_.link()) {                      //链接着色器
        qDebug() << "链接ERROR:" << programCube_.log();    //如果链接出错,打印报错信息
    }
    programCube_.bind();

    float vertexPositions[108] = {
        // 顶点,108个
        -1.0f,1.0f,-1.0f,   -1.0f,-1.0f,-1.0f,  1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,   1.0f,1.0f,-1.0f,    -1.0f,1.0f,-1.0f,
       1.0f,-1.0f,-1.0f,1.0f,-1.0f,1.0f,1.0f,1.0f,-1.0f,
        1.0f,-1.0f,1.0f,1.0f, 1.0f, 1.0f,1.0f,1.0f,-1.0f,
         1.0f,-1.0f,1.0f,-1.0f,-1.0f,1.0f,1.0f,1.0f,1.0f,
         -1.0f,-1.0f,1.0f,-1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,
        -1.0f,-1.0f,1.0f,-1.0f,-1.0f,-1.0f,-1.0f,1.0f,1.0f,
        -1.0f,-1.0f,-1.0f,-1.0f,1.0f,-1.0f,-1.0f,1.0f,1.0f,
        -1.0f,-1.0f,1.0f,1.0f,-1.0f,1.0f,1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,1.0f,
        -1.0f,1.0f,-1.0f,1.0f,1.0f,-1.0f,1.0f,1.0f,1.0f,
        1.0f,1.0f,1.0f,-1.0f,1.0f,1.0f,-1.0f,1.0f,-1.0f
    };
    // 放入pointsCube_
    foreach (auto i, vertexPositions) {
        pointsCube_.append(i);
    }
    vaoCube_.create();
    vaoCube_.bind();
    vaoCube_.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vaoCube_.allocate(vertexPositions, sizeof(vertexPositions));
}

void MyOpenglWedgit::setupVerticesBall(float r)
{
    // 着色器编译
    if (!programBall_.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader.vs")) {     //添加并编译顶点着色器
        qDebug() << "编译ERROR:" << programBall_.log();    //如果编译出错,打印报错信息
    }
    if (!programBall_.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader.fs")) {   //添加并编译片段着色器
        qDebug() << "编译ERROR:" << programBall_.log();    //如果编译出错,打印报错信息
    }
    if (!programBall_.link()) {                      //链接着色器
        qDebug() << "链接ERROR:" << programBall_.log();    //如果链接出错,打印报错信息
    }
//    programBall_.bind();

    int angleSpan = 10; //弧度 = 角度 * PI / 180
    for(int vAngle = -90; vAngle < 90; vAngle = vAngle + angleSpan) { //生成球面顶点
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

            pointsBall_ << x1 << y1 << z1 << x3 << y3 << z3
                   << x0 << y0 << z0 << x1 << y1 << z1
                   << x2 << y2 << z2 << x3 << y3 << z3;
        }
    }
    vboBall_.create();
    vboBall_.bind();
    vboBall_.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboBall_.allocate(pointsBall_.constData(),pointsBall_.count() * sizeof (GLfloat));
}

void MyOpenglWedgit::renderBall(QOpenGLExtraFunctions *f, QMatrix4x4 &projM, QMatrix4x4 &camera, QMatrix4x4 &model)
{

    programBall_.bind();
    vboBall_.bind();
    programBall_.setUniformValue("uPMatrix",projM);
    programBall_.setUniformValue("camMatrix",camera);
    programBall_.setUniformValue("uMMatrix",model);
    programBall_.setUniformValue("uR", radius_);
    programBall_.enableAttributeArray(0);

    programBall_.setAttributeBuffer(0,GL_FLOAT,0,3,0);
    glDrawArrays(GL_TRIANGLES,0,pointsBall_.count() / 3);

    programBall_.disableAttributeArray(0);
    vboBall_.release();
    programBall_.release();
}
