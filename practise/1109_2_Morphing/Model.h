#pragma once

#include <QMatrix4x4>
#include <QOpenGLExtraFunctions>
#include <QOpenGLVertexArrayObject> 
#include <QOpenGLBuffer> 
#include <QOpenGLShaderProgram> 
#include <QOpenGLTexture>
#include "Camera.h"
#include "Light.h"

struct Vertex
{
	QVector3D pos;
	QVector2D texture;
	QVector3D normal;
};

struct Material
{
    float ambient = 0.5; // 环境光，范围[0, 1]。如果为0表示环境中没有任何环境光，比如宇宙中
    float diffuse = 1; // 漫反射，范围[0, 1]。1表示只要接受到了光照就可以完全看得见。
    float specular = 0.6; // 镜面反射，范围[0,1]。0.2表示色子基本上不怎么有镜面反射。
    float shininess = 20; // 最终计算出来的镜面反射的效果。值越大，光斑越明显。16表示光斑不是那么明显。
};

static const int VertexFloatCount = 8;

class Model : public QOpenGLExtraFunctions
{
public:
	Model();
	~Model();
public:
	void setScale(float val) { m_scale = val; }
	void setRotate(const QVector3D &rotate) { m_rotate = rotate; }
	void setPos(const QVector3D &pos) { m_pos = pos; }
	float scale() { return m_scale; }
	QVector3D rotate() { return m_rotate; }
	QVector3D pos() { return m_pos; }
    // 11-04 移动
    void move(const QVector3D &step) { m_pos += step; }

public:
	void setVertices(const QVector<Vertex> &vertices) { m_vertices = vertices; }
	void setTexture(QOpenGLTexture *texture, int index = -1);
	void setShaderProgram(QOpenGLShaderProgram *program) { m_program = program; }
	void setMaterial(const Material &material, int index  = -1);
public:
    // 在绘制的时候需要知道这3个信息，才能计算光照和材质
	void setCamera(Camera *camera) { m_camera = camera; }
	void setProjection(const QMatrix4x4 &projection) { m_projection = projection; }
	void setLight(Light *light) { m_light = light; }
public:
	QMatrix4x4 model();
public:
	virtual void init();
	virtual void update();
	virtual void paint();
protected:
	QVector3D m_pos{ 0,0,0 };
	QVector3D m_rotate{ 0,0,0 };
	float m_scale = 1;

	QVector<Vertex> m_vertices;
	QMap<int, QOpenGLTexture *> m_textures;
    QMap<int, Material> m_materials; // 材质ID-材质

	QOpenGLVertexArrayObject m_vao;
	QOpenGLBuffer m_vbo;
	QOpenGLShaderProgram *m_program = nullptr;

    // 在绘制的时候需要知道这3个信息，才能计算光照和材质
	QMatrix4x4 m_projection;
	Camera *m_camera = nullptr;
	Light *m_light = nullptr;
};
