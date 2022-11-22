#pragma once
#include <QTime>
#include "Model.h"

class CubeModel_G : public Model
{
public:
    CubeModel_G();
    ~CubeModel_G();
public:
	virtual void init() override;
	virtual void update() override;
	virtual void paint() override;
private:
	float *m_vertexBuffer = nullptr;
	int m_vertexCount = 0;
    float m_length = 0.5;

};
