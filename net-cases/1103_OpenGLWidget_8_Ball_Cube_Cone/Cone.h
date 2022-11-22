#ifndef CONE_H
#define CONE_H
#include "Dice.h"

const float R       =   0.5;
const float HEIGHT  =   1.0;
const float STEP_ANGLE  =   1.0;

class Cone : public Model
{
public:
    Cone(); // #TODO：要添加圆锥的法线坐标，算法参考孟068_Light_Texture_Map
    ~Cone();
    // Model interface
public:
    virtual void init() override;
    virtual void update() override;
    virtual void paint() override;
private:
    float _r=R;                     // 半径
    float _height=HEIGHT;           // 高度
    float _step_angle=STEP_ANGLE;   // 底的角度间隔

    float *m_vertexBuffer = nullptr;
    int m_vertexCount = 0;
};

#endif // CONE_H
