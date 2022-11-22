#include "model.h"

// 保存纹理
Model::Model()
{

}

Model::~Model()
{

}

void Model::setTexture(QOpenGLTexture *texture, int index)
{
    if (index == -1)
    {
        if (m_textures.isEmpty())
        {
            index = 0;
        }
        else
        {
            index = m_textures.keys().last() + 1;
        }
    }
    m_textures.insert(index, texture);
}
// 如何生成模型矩阵：移动到指定位置，围绕哪个轴旋转
QMatrix4x4 Model::model()
{
    QMatrix4x4 _mat;
    _mat.setToIdentity();
    _mat.translate(m_pos);
    _mat.rotate(m_rotate.x(), 1, 0, 0);
    _mat.rotate(m_rotate.y(), 0, 1, 0);
    _mat.rotate(m_rotate.z(), 0, 0, 1);
    _mat.scale(m_scale);
    return _mat;
}
