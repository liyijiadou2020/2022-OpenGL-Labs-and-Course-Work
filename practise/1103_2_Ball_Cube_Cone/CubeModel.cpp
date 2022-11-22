#include "CubeModel.h"

CubeModel::CubeModel()
	: Model()
{
	setVertices({
		//   顶点           纹理	          法线
		// 1
            {{-m_length,  m_length,  m_length,}, {0.50, 0.25}, {0, 0, m_length}},	// 左上
            {{-m_length, -m_length,  m_length,}, {0.50, 0.50}, {0, 0, m_length}},	// 左下
            {{ m_length, -m_length,  m_length,}, {0.75, 0.50}, {0, 0, m_length}},	// 右下
            {{ m_length,  m_length,  m_length,}, {0.75, 0.25}, {0, 0, m_length}},	// 右上
		// 6							
            {{ m_length,  m_length, -m_length,}, {0.00, 0.25}, {0, 0, -m_length}},	// 左上
            {{ m_length, -m_length, -m_length,}, {0.00, 0.50}, {0, 0, -m_length}},	// 左下
            {{-m_length, -m_length, -m_length,}, {0.25, 0.50}, {0, 0, -m_length}},	// 右下
            {{-m_length,  m_length, -m_length,}, {0.25, 0.25}, {0, 0, -m_length}},	// 右上
		// 2							
            {{ m_length,  m_length,  m_length,}, {0.75, 0.25}, {m_length, 0, 0}},	// 左上
            {{ m_length, -m_length,  m_length,}, {0.75, 0.50}, {m_length, 0, 0}},	// 左下
            {{ m_length, -m_length, -m_length,}, {1.00, 0.50}, {m_length, 0, 0}},	// 右下
            {{ m_length,  m_length, -m_length,}, {1.00, 0.25}, {m_length, 0, 0}},	// 右上
		// 5							
            {{-m_length,  m_length, -m_length,}, {0.25, 0.25}, {-m_length, 0, 0}},	// 左上
            {{-m_length, -m_length, -m_length,}, {0.25, 0.50}, {-m_length, 0, 0}},	// 左下
            {{-m_length, -m_length,  m_length,}, {0.50, 0.50}, {-m_length, 0, 0}},	// 右下
            {{-m_length,  m_length,  m_length,}, {0.50, 0.25}, {-m_length, 0, 0}},	// 右上
		// 3							
            {{-m_length,  m_length, -m_length,}, {0.00, 0.00}, {0, m_length, 0}},	// 左上
            {{-m_length,  m_length,  m_length,}, {0.00, 0.25}, {0, m_length, 0}},	// 左下
            {{ m_length,  m_length,  m_length,}, {0.25, 0.25}, {0, m_length, 0}},	// 右下
            {{ m_length,  m_length, -m_length,}, {0.25, 0.00}, {0, m_length, 0}},	// 右上
		// 4							
            {{-m_length, -m_length,  m_length,}, {0.00, 0.50}, {0, -m_length, 0}},	// 左上
            {{-m_length, -m_length, -m_length,}, {0.00, 0.75}, {0, -m_length, 0}},	// 左下
            {{ m_length, -m_length, -m_length,}, {0.25, 0.75}, {0, -m_length, 0}},	// 右下
            {{ m_length, -m_length,  m_length,}, {0.25, 0.50}, {0, -m_length, 0}},	// 右上
		});

    auto _texture = new QOpenGLTexture(QImage(":/pic/02.png"));
	_texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	_texture->setMagnificationFilter(QOpenGLTexture::Linear);
	setTexture(_texture);

    Material m;
    m.ambient=0;
    m.diffuse=1;
    m.specular=0.2;
    m.shininess=16;
    setMaterial(m);

	auto _program = new QOpenGLShaderProgram();
    _program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":shader/vertex.shader");
    _program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":shader/fragment.shader");
	setShaderProgram(_program);
}

CubeModel::~CubeModel()
{
}

void CubeModel::init()
{
	initializeOpenGLFunctions();
    if (!m_vao.isCreated()) m_vao.create();
    if (!m_vbo.isCreated()) m_vbo.create();
    if (!m_program->isLinked()) m_program->link();

	if (m_vertexCount < m_vertices.count())
	{
        if (m_vertexBuffer) delete[] m_vertexBuffer;
		m_vertexBuffer = new float[m_vertices.count() * VertexFloatCount];
		m_vertexCount = m_vertices.count();
		int _offset = 0;
		for (auto &vertex : m_vertices)
		{
			m_vertexBuffer[_offset] = vertex.pos.x(); _offset++;
			m_vertexBuffer[_offset] = vertex.pos.y(); _offset++;
			m_vertexBuffer[_offset] = vertex.pos.z(); _offset++;
			m_vertexBuffer[_offset] = vertex.texture.x(); _offset++;
			m_vertexBuffer[_offset] = vertex.texture.y(); _offset++;
			m_vertexBuffer[_offset] = vertex.normal.x(); _offset++;
			m_vertexBuffer[_offset] = vertex.normal.y(); _offset++;
			m_vertexBuffer[_offset] = vertex.normal.z(); _offset++;
		}
	}

	m_vao.bind();
	m_vbo.bind();
	m_vbo.allocate(m_vertexBuffer, sizeof(float) * m_vertices.count() * VertexFloatCount);

	m_program->bind();
	// 绑定顶点坐标信息, 从0 * sizeof(float)字节开始读取3个float, 因为一个顶点有8个float数据, 所以下一个数据需要偏移8 * sizeof(float)个字节
	m_program->setAttributeBuffer("vPos", GL_FLOAT, 0 * sizeof(float), 3, VertexFloatCount * sizeof(float));
	m_program->enableAttributeArray("vPos");
	// 绑定纹理坐标信息, 从3 * sizeof(float)字节开始读取2个float, 因为一个顶点有8个float数据, 所以下一个数据需要偏移8 * sizeof(float)个字节
	m_program->setAttributeBuffer("vTexture", GL_FLOAT, 3 * sizeof(float), 2, VertexFloatCount * sizeof(float));
	m_program->enableAttributeArray("vTexture");
	// 绑定法线坐标信息, 从5 * sizeof(float)字节开始读取3个float, 因为一个顶点有8个float数据, 所以下一个数据需要偏移8 * sizeof(float)个字节
	m_program->setAttributeBuffer("vNormal", GL_FLOAT, 5 * sizeof(float), 3, VertexFloatCount * sizeof(float));
	m_program->enableAttributeArray("vNormal");
	m_program->release();

	m_vbo.release();
	m_vao.release();
}

void CubeModel::update()
{
}
// 绘制的时候，我们需要额外的传入视角信息，光源的信息和材质的信息
// 这里有一个m_projection变量和m_camera对象以及m_light对象。它们都是通过外部传递进来的。
void CubeModel::paint()
{
    // 开启纹理
    for (auto index : m_textures.keys())
	{
		m_textures[index]->bind(index);
	}
	m_vao.bind();
	m_program->bind();

	// 绑定变换矩阵
	m_program->setUniformValue("projection", m_projection);
	m_program->setUniformValue("view", m_camera->view());
	m_program->setUniformValue("viewPos", m_camera->pos());
    m_program->setUniformValue("model", model()); // #TODO 这里让色子动起来，所以要改变model的值
	// 设定灯光位置与颜色
	m_program->setUniformValue("light.position", m_light->pos());
	m_program->setUniformValue("light.color", m_light->color().redF(), m_light->color().greenF(), m_light->color().blueF());
	auto &_material = m_materials.value(0);
	// 设定材质
	m_program->setUniformValue("material.ambient", _material.ambient);
	m_program->setUniformValue("material.diffuse", _material.diffuse);
	m_program->setUniformValue("material.specular", _material.specular);
	m_program->setUniformValue("material.shininess", _material.shininess);
    // 绘制6个面
	for (int i = 0; i < 6; ++i)
	{
		glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
	}
	m_program->release();
	m_vao.release();
	for (auto texture : m_textures)
	{
		texture->release();
	}
}

