#ifndef DICE_H
#define DICE_H

#include "Model.h"

class Dice : public Model
{
public:
    Dice();
    ~Dice();

public:
    virtual void init() override;
    virtual void update() override;
    virtual void paint(const QMatrix4x4 &projection, const QMatrix4x4 &view) override;
private:
    float *m_vertexBuffer = nullptr; //
    int m_vertexCount = 0; // 顶点的个数
};

#endif // DICE_H
