#include "Cylinder1.h"

#define PI 3.14159265f


Cylinder_1::Cylinder_1()
{

    float angleSpan = 5;
    topVec << 0 << h/2 << 0;
    topNorVec << 0 << 1 << 0;
    bottomVec << 0 << -h/2 << 0;
    bottomNorVec << 0 << -1 << 0;
    for(float angle = 0; angle <= 360; angle += angleSpan){
        //侧面
        float curRad = angle * PI / 180;
        float x1 = r * ::cos(curRad);
        float y1 = - h/2;
        float z1 = r * ::sin(curRad);
        float nx1 = x1;
        float ny1 = 0;
        float nz1 = z1;

        float x2 = x1;
        float y2 = h/2;
        float z2 = z1;
        float nx2 = x2;
        float ny2 = 0;
        float nz2 = z2;

        float nextRad = angle + angleSpan;
        float x3 = r * ::cos(nextRad * PI / 180);
        float y3 = h/2;
        float z3 = r * ::sin(nextRad * PI / 180);
        float nx3 = x3;
        float ny3 = 0;
        float nz3 = z3;

        float x4 = x3;
        float y4 = -h/2;
        float z4 = z3;
        float nx4 = x4;
        float ny4 = 0;
        float nz4 = z4;
        ceVec << x1 << y1 << z1 << x2 << y2 << z2 << x3 << y3 << z3 << x4 << y4 << z4;
        ceNorVec << nx1 << ny1 << nz1 << nx2 << ny2 << nz2 << nx3 << ny3 << nz3 << nx4 << ny4 << nz4;
        //顶面
        x2 = r * ::cos(-curRad);
        z2 = r * ::sin(-curRad);
        topVec << x2 << y2 << z2;
//        float topTx1 = 0.5 - 0.5 * ::cos(curRad);
//        float topTy1 = 0.5 - 0.5 * ::sin(-curRad);
//        topTexVec << topTx1 << topTy1;
        topNorVec << 0 << 1 << 0;
        //底面
        bottomVec << x1 << y1 << z1;
//        bottomTexVec << topTx1 << topTy1;
        bottomNorVec << 0 << -1 << 0;
    }
    vertVec_ << ceVec  << topVec << bottomVec;
    normalVec_ << ceNorVec << topNorVec << bottomNorVec;

    if (!m_vao.isCreated())
        m_vao.create();
    if (!vbo_.isCreated())
        vbo_.create();
    m_vao.bind();
    m_vbo.bind();

    bytesVec << vertVec_ << normalVec_;
    m_vbo.allocate(bytesVec.data(),bytesVec.count() * sizeof(GLfloat));

    program_.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,":shader/cylinder.vert");
    program_.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,":shader/cylinder.frag");
    program_.link();

}

void Cylinder_1::init()
{
    initializeOpenGLFunctions();
    if (!m_vao.isCreated())
        m_vao.create();
    if (!vbo_.isCreated())
        vbo_.create();
    if (!program_.isLinked()) {
        auto suc = program_.link();
        if (!suc)
            qDebug() << program_.log();
    }

    m_vao.bind();
    m_vbo.bind();
    m_program->bind();


//    float* pass_vertexBuffer = new float[vertices.size()];
//    int pass_vertexCount = vertices.size(); // 12960
//    qDebug() << "vertices.size() = " << vertices.size(); // 12960个float
//    // 2160个顶点 = 720个三角形 = 侧面360个 + 底面360个
//    for(int i=0; i<vertices.size(); ++i) {
//        pass_vertexBuffer[i] = vertices[i];
//    }

//    m_vbo.allocate(pass_vertexBuffer, sizeof(float) * pass_vertexCount);


    glVertexAttribPointer(0,  3,  GL_FLOAT,   GL_FALSE,    6 * sizeof(float),     (void*)0);  // 手动传入第几个属性
    glEnableVertexAttribArray(0); // 开始 VAO 管理的第一个属性值
    glVertexAttribPointer(1,  3,  GL_FLOAT,   GL_FALSE,   6 * sizeof(float),      (void*)(3 * sizeof(float)));  // 手动传入第几个属性
    glEnableVertexAttribArray(1);

    m_program->release();
    m_vbo.release();
    m_vao.release();

}

void Cylinder_1::update()
{

}

void Cylinder_1::paint()
{
    m_vao.bind();
    m_program->bind();

    m_program->setUniformValue("view", m_camera->view());
    m_program->setUniformValue("projection", m_projection);
    m_program->setUniformValue("model", model());

    /* #TODO 材质颜色 */
    auto &_material = m_materials.value(0);
    m_program->setUniformValue("material.ambient",   _material.ambient);
    m_program->setUniformValue("material.diffuse",   _material.diffuse);
    m_program->setUniformValue("material.specular",  _material.specular);
    m_program->setUniformValue("material.shininess", _material.shininess);

    /* # TODO 灯光的位置和颜色 */
    m_program->setUniformValue("light.position", m_light->pos());
    m_program->setUniformValue("light.color", m_light->color().redF(), m_light->color().greenF(), m_light->color().blueF());
    m_program->setUniformValue("viewPos", m_camera->pos());

//    glDrawArrays(GL_TRIANGLES, 0, bytesVec.size());
//    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glDrawArrays(GL_QUADS, 0, ceVec.count()/3);


    m_program->release();
    m_vao.release();
}


