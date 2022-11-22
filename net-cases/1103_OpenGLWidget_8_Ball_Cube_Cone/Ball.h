#pragma once

#include "Dice.h"

class Ball : public Model
{
public:
    Ball(); // #TODO：要添加球的法线坐标，算法参考https://dhbloo.github.io/2020/03/12/Sphere/#%E7%90%83%E5%9D%90%E6%A0%87%E8%BD%AC%E6%8D%A2
    ~Ball();
public:
	virtual void init() override;
	virtual void update() override;
	virtual void paint() override;
private:
	float *m_vertexBuffer = nullptr;
	int m_vertexCount = 0;
	int m_row = 0;
	int m_col = 0;
};

