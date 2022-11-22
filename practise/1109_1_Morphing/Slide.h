#ifndef SLIDE_H
#define SLIDE_H

#include "Model.h"

class Slide : public Model
{
public:
    Slide();
    ~Slide();
public:
    virtual void init() override;
    virtual void update() override;
    virtual void paint() override;
private:
    float *m_vertexBuffer = nullptr;
    int m_vertexCount = 0;
    float m_length = 1.0;


};

#endif // SLIDE_H
