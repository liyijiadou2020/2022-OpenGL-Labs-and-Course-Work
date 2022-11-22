#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QVector>
/* 2D 3D向量*/
#include <QVector2D>
#include <QVector3D>
/* 模型继承QOpenGLExtraFunctions，为了方便使用OpenGL的函数*/
#include <QOpenGLExtraFunctions>
/* 纹理 */
#include <QOpenGLTexture>
/* 着色器程序 */
#include <QOpenGLShaderProgram>
/* VAO */
#include <QOpenGLVertexArrayObject>
/* VBO */
#include <QOpenGLBuffer>

//顶点信息应包含两个：位置坐标和纹理坐标
struct Vertex
{
    QVector3D pos;
    QVector2D texture;
};

static const int VertexFloatCount = 5; // 意思是Vertex中有多少个float，在子类中要用到

class Model : public QOpenGLExtraFunctions
{
public:
    Model();
    ~Model();
public:
    void setScale(float val) { m_scale = val; }
    void setRotate(const QVector3D &rotate) { m_rotate = rotate; }
    void setPos(const QVector3D &pos) { m_pos = pos; }
public:
    void setVertices(const QVector<Vertex> &vertices) { m_vertices = vertices; }
    void setShaderProgram(QOpenGLShaderProgram *program) { m_program = program; }
    void setTexture(QOpenGLTexture *texture, int index = -1); // 保存纹理
public:
    QMatrix4x4 model(); // 返回模型矩阵：移动到指定位置m_pos，围绕轴m_rotate旋转
public:
    //    三个虚函数，需要子类各自去实现
    virtual void init();
    virtual void update();
    virtual void paint(const QMatrix4x4 &projection, const QMatrix4x4 &view);
protected:
    QVector3D m_pos{ 0,0,0 };       // 位置
    QVector3D m_rotate{ 0,0,0 };    // 旋转轴
    float m_scale = 1;              // 缩放比例
    QVector<Vertex> m_vertices;     // 顶点
    QMap<int, QOpenGLTexture *> m_textures; //纹理坐标映射<纹理id，纹理指针>
    QOpenGLVertexArrayObject m_vao; // 模型自己的vao
    QOpenGLBuffer m_vbo;            // 模型自己的vbo
    QOpenGLShaderProgram *m_program = nullptr;  // 着色器程序
};

#endif // MODEL_H
