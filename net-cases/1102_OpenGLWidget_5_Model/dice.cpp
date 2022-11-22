#include "dice.h"

Dice::~Dice()
{
}

void Dice::update()
{
}


Dice::Dice()
    : Model()
{
    setVertices({
        // 顶点				纹理
        // 1
            {{-1,  1,  1,}, {0.50, 0.25}},	// 左上
            {{-1, -1,  1,}, {0.50, 0.50}},	// 左下
            {{ 1, -1,  1,}, {0.75, 0.50}},	// 右下
            {{ 1,  1,  1,}, {0.75, 0.25}},	// 右上
        // 6
            {{ 1,  1, -1,}, {0.00, 0.25}},	// 左上
            {{ 1, -1, -1,}, {0.00, 0.50}},	// 左下
            {{-1, -1, -1,}, {0.25, 0.50}},	// 右下
            {{-1,  1, -1,}, {0.25, 0.25}},	// 右上
        // 2
            {{ 1,  1,  1,}, {0.75, 0.25}},	// 左上
            {{ 1, -1,  1,}, {0.75, 0.50}},	// 左下
            {{ 1, -1, -1,}, {1.00, 0.50}},	// 右下
            {{ 1,  1, -1,}, {1.00, 0.25}},	// 右上
        // 5
            {{-1,  1, -1,}, {0.25, 0.25}},	// 左上
            {{-1, -1, -1,}, {0.25, 0.50}},	// 左下
            {{-1, -1,  1,}, {0.50, 0.50}},	// 右下
            {{-1,  1,  1,}, {0.50, 0.25}},	// 右上
        // 3
            {{-1,  1, -1,}, {0.00, 0.00}},	// 左上
            {{-1,  1,  1,}, {0.00, 0.25}},	// 左下
            {{ 1,  1,  1,}, {0.25, 0.25}},	// 右下
            {{ 1,  1, -1,}, {0.25, 0.00}},	// 右上
        // 4
            {{ 1, -1,  1,}, {0.00, 0.50}},	// 左上
            {{ 1, -1, -1,}, {0.00, 0.75}},	// 左下
            {{-1, -1, -1,}, {0.25, 0.75}},	// 右下
            {{-1, -1,  1,}, {0.25, 0.50}},	// 右上
        });

    setTexture(new QOpenGLTexture(QImage(":/pic/02.png")));

    // 注意，这里_program并没有链接！
    auto _program = new QOpenGLShaderProgram();
    _program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader.vert");
    _program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader.frag");
    setShaderProgram(_program);
}

// 创建各种缓存
// 以后放在initeGL()中使用
void Dice::init()
{
    initializeOpenGLFunctions();
    if (!m_vao.isCreated()) m_vao.create();
    if (!m_vbo.isCreated()) m_vbo.create();
    if (!m_program->isLinked()) m_program->link();

    // m_vertexCount：类private成员，在类里面定义，表示顶点的个数
    // m_vertices：继承自父类Model，表示顶点的个数。在构造函数中已经被定义
    if (m_vertexCount < m_vertices.count())
    {
        if (m_vertexBuffer)
            delete[] m_vertexBuffer;
        m_vertexBuffer = new float[m_vertices.count() * VertexFloatCount];
        m_vertexCount = m_vertices.count();
        int _offset = 0;
        for (auto &vertex : m_vertices)
        { // 将类中保存的顶点信息转化为了OpenGL需要的顶点缓存的格式：(x, y, z, texX, texY)
            m_vertexBuffer[_offset] = vertex.pos.x(); _offset++;
            m_vertexBuffer[_offset] = vertex.pos.y(); _offset++;
            m_vertexBuffer[_offset] = vertex.pos.z(); _offset++;
            m_vertexBuffer[_offset] = vertex.texture.x(); _offset++;
            m_vertexBuffer[_offset] = vertex.texture.y(); _offset++;
        }
    }

    m_vao.bind();
    m_vbo.bind();
    m_vbo.allocate(m_vertexBuffer, sizeof(float) * m_vertices.count() * VertexFloatCount);

    m_program->bind();
    // 绑定顶点坐标信息, 从0 * sizeof(float)字节开始读取3个float, 因为一个顶点有5个float数据, 所以下一个数据需要偏移5 * sizeof(float)个字节
    m_program->setAttributeBuffer("vPos", GL_FLOAT, 0 * sizeof(float), 3, 5 * sizeof(float));
    m_program->enableAttributeArray("vPos");
    // 绑定纹理坐标信息, 从3 * sizeof(float)字节开始读取2个float, 因为一个顶点有5个float数据, 所以下一个数据需要偏移5 * sizeof(float)个字节
    m_program->setAttributeBuffer("vTexture", GL_FLOAT, 3 * sizeof(float), 2, 5 * sizeof(float));
    m_program->enableAttributeArray("vTexture");
    m_program->release();

    m_vbo.release();
    m_vao.release();
}

// 绘制我们的色子
void Dice::paint(const QMatrix4x4 &projection, const QMatrix4x4 &view)
{
    // 绑定纹理，绑定vao，绑定着色器程序
    for (auto index : m_textures.keys())
    {
        m_textures[index]->bind(index);
    }
    m_vao.bind();
    m_program->bind();
    // 绑定变换矩阵
    m_program->setUniformValue("projection", projection);
    m_program->setUniformValue("view", view);
    m_program->setUniformValue("model", model());
    // 绘制6个面
    for (int i = 0; i < 6; ++i)
    {
        glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
    }
    // 释放着色器，释放vao，纹理解绑
    m_program->release();
    m_vao.release();
    for (auto texture : m_textures)
    {
        texture->release();
    }
}

