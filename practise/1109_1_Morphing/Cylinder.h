#ifndef CYLINDER_H
#define CYLINDER_H

#include <vector>
#include <QMatrix4x4>
#include "Model.h"

const float cy_r       =   0.2;
const float cy_R       =   0.5;
const float cy_HEIGHT  =   1.0;
const float cy_STEP_ANGLE  =   1.0;


class Cylinder : public Model
{
public:
    Cylinder();
    ~Cylinder();
public: // Model interface
    virtual void init() override;
    virtual void update() override;
    virtual void paint() override;
public:
    std::vector<float> vertices;    // 没有纹理坐标！最终的顶点数据（位置1：3x 顶点数据；位置2：3x 法线数据）
private:
    float _r=cy_r;       // 半径
    float _R=cy_R;       // 半径
    float _height=cy_HEIGHT;  // 高度
    float _step_angle=cy_STEP_ANGLE;  // 底的角度间隔

};
#endif // CYLINDER_H
