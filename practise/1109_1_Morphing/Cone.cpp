#include "Cone.h"
#include "foxmath.h"

#define PI 3.1415926

Cone::Cone()
    : Model()
{
    /* 锥体顶点 */
    float top_x = 0.0f;
    float top_y = _height;
    float top_z = 0.0f;

    /* 生成锥体底部的顶点数据 (EBO 索引从2开始)*/
    std::vector<float> tmp_vetices;
    float current_angle = 0.0f;
    for (int i = 0; i < 360/_step_angle + 1; i++)
    {
        tmp_vetices.push_back(_r*cos(current_angle*M_PI/180)); // x，【重点】sin() 默认是弧度！！，不是角度！！
        tmp_vetices.push_back(0.0f);                           // y
        tmp_vetices.push_back(_r*sin(current_angle*M_PI/180)); // z

        current_angle += _step_angle;
    }


    /* 推入侧边的顶点数据（位置 1：顶点坐标；位置 2：法线） */
    for (int i = 0; i < tmp_vetices.size() - 3; i += 3)
    {
        float current_x = tmp_vetices[i + 0];
        float current_y = tmp_vetices[i + 1];
        float current_z = tmp_vetices[i + 2];

        float next_x = tmp_vetices[i + 3];
        float next_y = tmp_vetices[i + 4];
        float next_z = tmp_vetices[i + 5];

        QVector3D current_normal = -getNormalVector(QVector3D(top_x,     top_y,      top_z),
                                                    QVector3D(current_x, current_y,  current_z),
                                                    QVector3D(next_x,    next_y,     next_z));
        vertices.push_back(top_x);
        vertices.push_back(top_y);
        vertices.push_back(top_z);
        vertices.push_back(current_normal.x());
        vertices.push_back(current_normal.y());
        vertices.push_back(current_normal.z());

        vertices.push_back(tmp_vetices[i + 0]);
        vertices.push_back(tmp_vetices[i + 1]);
        vertices.push_back(tmp_vetices[i + 2]);
        vertices.push_back(current_normal.x());
        vertices.push_back(current_normal.y());
        vertices.push_back(current_normal.z());

        vertices.push_back(tmp_vetices[i + 3]);
        vertices.push_back(tmp_vetices[i + 4]);
        vertices.push_back(tmp_vetices[i + 5]);
        vertices.push_back(current_normal.x());
        vertices.push_back(current_normal.y());
        vertices.push_back(current_normal.z());
    }

    /* 推入锥体地面的顶点数据（位置 1：顶点坐标；位置 2：法线） */
    float bottom_x = 0.0f;
    float bottom_y = 0.0f;
    float bottom_z = 0.0f;

    for (int i = 0; i < tmp_vetices.size() - 3; i += 3)
    {
        float current_x = tmp_vetices[i + 0];
        float current_y = tmp_vetices[i + 1];
        float current_z = tmp_vetices[i + 2];

        float next_x = tmp_vetices[i + 3];
        float next_y = tmp_vetices[i + 4];
        float next_z = tmp_vetices[i + 5];

        QVector3D current_normal = getNormalVector(QVector3D(bottom_x,  bottom_y,   bottom_z),
                                                   QVector3D(current_x, current_y,  current_z),
                                                   QVector3D(next_x,    next_y,     next_z));
        vertices.push_back(bottom_x);
        vertices.push_back(bottom_y);
        vertices.push_back(bottom_z);
        vertices.push_back(current_normal.x());
        vertices.push_back(current_normal.y());
        vertices.push_back(current_normal.z());

        vertices.push_back(tmp_vetices[i + 0]);
        vertices.push_back(tmp_vetices[i + 1]);
        vertices.push_back(tmp_vetices[i + 2]);
        vertices.push_back(current_normal.x());
        vertices.push_back(current_normal.y());
        vertices.push_back(current_normal.z());

        vertices.push_back(tmp_vetices[i + 3]);
        vertices.push_back(tmp_vetices[i + 4]);
        vertices.push_back(tmp_vetices[i + 5]);
        vertices.push_back(current_normal.x());
        vertices.push_back(current_normal.y());
        vertices.push_back(current_normal.z());
    }

    Material m;
    m.ambient=0.3;
    m.diffuse=0.6;
    m.specular=0.9;
    m.shininess=128;
    setMaterial(m);

    auto _program = new QOpenGLShaderProgram();
    _program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader/cone.vert");
    _program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader/cone.frag");
    setShaderProgram(_program);

}

Cone::~Cone()
{
}


void Cone::init()
{
    initializeOpenGLFunctions();
    if (!m_vao.isCreated())
        m_vao.create();
    if (!m_vbo.isCreated())
        m_vbo.create();
    if (!m_program->isLinked()) {
        auto suc = m_program->link();
        if (!suc)
            qDebug() << m_program->log();
    }

    m_vao.bind();
    m_vbo.bind();

    float* pass_vertexBuffer = new float[vertices.size()];
    int pass_vertexCount = vertices.size(); // 12960
    qDebug() << "vertices.size() = " << vertices.size(); // 12960个float
    // 2160个顶点 = 720个三角形 = 侧面360个 + 底面360个
    for(int i=0; i<vertices.size(); ++i) {
        pass_vertexBuffer[i] = vertices[i];
    }

    m_vbo.allocate(pass_vertexBuffer, sizeof(float) * pass_vertexCount);

    m_program->bind();


    glVertexAttribPointer(0,     3,  GL_FLOAT,   GL_FALSE,    6 * sizeof(float),     (void*)0);  // 手动传入第几个属性
    glEnableVertexAttribArray(0); // 开始 VAO 管理的第一个属性值
    glVertexAttribPointer(1,  3,  GL_FLOAT,   GL_FALSE,   6 * sizeof(float),      (void*)(3 * sizeof(float)));  // 手动传入第几个属性
    glEnableVertexAttribArray(1);

    m_program->release();
    m_vbo.release();
    m_vao.release();
}

void Cone::update()
{
}

void Cone::paint()
{

    m_vao.bind();
    m_program->bind();

    m_program->setUniformValue("view", m_camera->view());
    m_program->setUniformValue("projection", m_projection);
    m_program->setUniformValue("model", model());

    /* #TODO 材质颜色 */
    auto &_material = m_materials.value(0);
//    m_program->setUniformValue("material.texture",   0);
    m_program->setUniformValue("material.ambient",   _material.ambient);
    m_program->setUniformValue("material.diffuse",   _material.diffuse);
    m_program->setUniformValue("material.specular",  _material.specular);
    m_program->setUniformValue("material.shininess", _material.shininess);

    /* # TODO 灯光的位置和颜色 */
    m_program->setUniformValue("light.position", m_light->pos());
    m_program->setUniformValue("light.color", m_light->color().redF(), m_light->color().greenF(), m_light->color().blueF());
    m_program->setUniformValue("viewPos", m_camera->pos());

    glDrawArrays(GL_TRIANGLES, 0, vertices.size()/6);
//    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    m_program->release();
    m_vao.release();

}
