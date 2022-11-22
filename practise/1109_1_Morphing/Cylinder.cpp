#include "Cylinder.h"
#include "foxmath.h"

#define PI 3.1415926

Cylinder::Cylinder()
    : Model()
{

    std::vector<float> upFace_vetices;
    float c_angle = 0.0f;
    for (int i = 0; i < 360/_step_angle + 1; i++) // 上底面
    {
        upFace_vetices.push_back(_r*cos(c_angle*M_PI/180));
        upFace_vetices.push_back(_height);
        upFace_vetices.push_back(_r*sin(c_angle*M_PI/180));
        c_angle += _step_angle;
    }

    std::vector<float> downFace_vetices; // 下底面
    float current_angle = 0.0f;
    for (int i = 0; i < 360/_step_angle + 1; i++)
    {
        downFace_vetices.push_back(_R*cos(current_angle*M_PI/180)); // x，【重点】sin() 默认是弧度！！，不是角度！！
        downFace_vetices.push_back(0.0f);                           // y
        downFace_vetices.push_back(_R*sin(current_angle*M_PI/180)); // z

        current_angle += _step_angle;
    }


    /* 推入侧边的顶点数据（位置 1：顶点坐标；位置 2：法线） */
    for (int i = 0; i < downFace_vetices.size() - 3; i += 3)
    {
        float current_down_x = downFace_vetices[i + 0];
        float current_down_y = downFace_vetices[i + 1];
        float current_down_z = downFace_vetices[i + 2];

        float next_down_x = downFace_vetices[i + 3];
        float next_down_y = downFace_vetices[i + 4];
        float next_down_z = downFace_vetices[i + 5];

        float up_cur_x = upFace_vetices[i + 0];
        float up_cur_y = upFace_vetices[i + 1];
        float up_cur_z = upFace_vetices[i + 2];

        QVector3D current_normal = -getNormalVector(QVector3D(up_cur_x,     up_cur_y,      up_cur_z),
                                                    QVector3D(current_down_x, current_down_y,  current_down_z),
                                                    QVector3D(next_down_x,    next_down_y,     next_down_z));
        vertices.push_back(up_cur_x);
        vertices.push_back(up_cur_y);
        vertices.push_back(up_cur_z);
        vertices.push_back(current_normal.x());
        vertices.push_back(current_normal.y());
        vertices.push_back(current_normal.z());

        vertices.push_back(downFace_vetices[i + 0]);
        vertices.push_back(downFace_vetices[i + 1]);
        vertices.push_back(downFace_vetices[i + 2]);
        vertices.push_back(current_normal.x());
        vertices.push_back(current_normal.y());
        vertices.push_back(current_normal.z());

        vertices.push_back(downFace_vetices[i + 3]);
        vertices.push_back(downFace_vetices[i + 4]);
        vertices.push_back(downFace_vetices[i + 5]);
        vertices.push_back(current_normal.x());
        vertices.push_back(current_normal.y());
        vertices.push_back(current_normal.z());
    }

    // 上底面
    float up_x = 0.0f;
    float up_y = _height;
    float up_z = 0.0f;

    for (int i = 0; i < upFace_vetices.size() - 3; i += 3)
    {
        float current_x = upFace_vetices[i + 0];
        float current_y = upFace_vetices[i + 1];
        float current_z = upFace_vetices[i + 2];

        float next_x = upFace_vetices[i + 3];
        float next_y = upFace_vetices[i + 4];
        float next_z = upFace_vetices[i + 5];

        QVector3D current_normal = getNormalVector(QVector3D(up_x,  up_y,   up_z),
                                                   QVector3D(current_x, current_y,  current_z),
                                                   QVector3D(next_x,    next_y,     next_z));
        vertices.push_back(up_x);
        vertices.push_back(up_y);
        vertices.push_back(up_z);
        vertices.push_back(current_normal.x());
        vertices.push_back(current_normal.y());
        vertices.push_back(current_normal.z());

        vertices.push_back(upFace_vetices[i + 0]);
        vertices.push_back(upFace_vetices[i + 1]);
        vertices.push_back(upFace_vetices[i + 2]);
        vertices.push_back(current_normal.x());
        vertices.push_back(current_normal.y());
        vertices.push_back(current_normal.z());

        vertices.push_back(upFace_vetices[i + 3]);
        vertices.push_back(upFace_vetices[i + 4]);
        vertices.push_back(upFace_vetices[i + 5]);
        vertices.push_back(current_normal.x());
        vertices.push_back(current_normal.y());
        vertices.push_back(current_normal.z());
    }


    /* 下底面 - 推入锥体地面的顶点数据（位置 1：顶点坐标；位置 2：法线） */
    float bottom_x = 0.0f;
    float bottom_y = 0.0f;
    float bottom_z = 0.0f;

    for (int i = 0; i < downFace_vetices.size() - 3; i += 3)
    {
        float current_x = downFace_vetices[i + 0];
        float current_y = downFace_vetices[i + 1];
        float current_z = downFace_vetices[i + 2];

        float next_x = downFace_vetices[i + 3];
        float next_y = downFace_vetices[i + 4];
        float next_z = downFace_vetices[i + 5];

        QVector3D current_normal = getNormalVector(QVector3D(bottom_x,  bottom_y,   bottom_z),
                                                   QVector3D(current_x, current_y,  current_z),
                                                   QVector3D(next_x,    next_y,     next_z));
        vertices.push_back(bottom_x);
        vertices.push_back(bottom_y);
        vertices.push_back(bottom_z);
        vertices.push_back(current_normal.x());
        vertices.push_back(current_normal.y());
        vertices.push_back(current_normal.z());

        vertices.push_back(downFace_vetices[i + 0]);
        vertices.push_back(downFace_vetices[i + 1]);
        vertices.push_back(downFace_vetices[i + 2]);
        vertices.push_back(current_normal.x());
        vertices.push_back(current_normal.y());
        vertices.push_back(current_normal.z());

        vertices.push_back(downFace_vetices[i + 3]);
        vertices.push_back(downFace_vetices[i + 4]);
        vertices.push_back(downFace_vetices[i + 5]);
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
    _program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader/cylinder.vert");
    _program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader/cylinder.frag");
    setShaderProgram(_program);

}

Cylinder::~Cylinder()
{
}


void Cylinder::init()
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
    int pass_vertexCount = vertices.size();
    qDebug() << "cylinder.vertices.size() = " << vertices.size(); // 12960个float
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

void Cylinder::update()
{
}

void Cylinder::paint()
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

    m_program->release();
    m_vao.release();

}
