#ifndef CYLINDER_1_H
#define CYLINDER_1_H



#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLExtraFunctions>
#include "Model.h"



class Cylinder_1 : public Model
{
public:
    Cylinder_1();
    ~Cylinder_1() {};
public: // Model interface
    virtual void init() override;
    virtual void update() override;
    virtual void paint() override;

    QVector<GLfloat> bytesVec;

private:
    QOpenGLShaderProgram program_;
    QOpenGLBuffer vbo_;
    QVector<GLfloat> vertVec_, normalVec_; // #TODO textVec_不需要
    QVector<GLfloat> ceVec, ceNorVec,topVec, topNorVec,bottomVec, bottomNorVec;
//    QOpenGLTexture *ceTexture_{nullptr},*topTexture_{nullptr},*bottomTexture_{nullptr};
    float r = 0.2f;
    float h = 0.5f;
};

#endif // CYLINDER_1_H
