#ifndef CONE_H
#define CONE_H
#include <vector>
#include <QMatrix4x4>
#include "CubeModel.h"

const float R       =   0.5;
const float HEIGHT  =   0.5;
const float STEP_ANGLE  =   1.0;

class ConeModel : public Model
{
public:
    ConeModel();
    ~ConeModel();   
public: // Model interface
    virtual void init() override;
    virtual void update() override;
    virtual void paint() override;
public:
    std::vector<float> vertices;    // 没有纹理坐标！最终的顶点数据（位置1：3x 顶点数据；位置2：3x 法线数据）
private:
    float _r=R;       // 半径
    float _height=HEIGHT;  // 高度
    float _step_angle=STEP_ANGLE;  // 底的角度间隔
};

#endif // CONE_H
