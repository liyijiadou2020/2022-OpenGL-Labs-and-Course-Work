#pragma once

#include "Model.h"

class CubeModel : public Model
{
public:
    CubeModel();
    ~CubeModel();
public:
	virtual void init() override;
	virtual void update() override;
	virtual void paint() override;
private:
	float *m_vertexBuffer = nullptr;
	int m_vertexCount = 0;
    float m_length = 1.0;
};
