#ifndef PROGRAM_P2_C4_H
#define PROGRAM_P2_C4_H

#include "../tool/programid.h"

class PROGRAM_P2_C4 : public ProgramId
{
public:
    typedef int attribute;
    typedef int uniform;
public:
    attribute   _lifetimeLoc;
    attribute   _startPositionLoc;
    attribute   _endPositionLoc;
    /**
    *   uniform
    */
    uniform     _timeLoc;
    uniform     _centerPositionLoc;
    uniform     _colorLoc;
    uniform     _samplerLoc;

    float       _timer;
public:
    PROGRAM_P2_C4();
    /// 初始化函数
    virtual bool    initialize();

    /**
    *   使用程序
    */
    virtual void    begin();
    /**
    *   使用完成
    */
    virtual void    end();
};

#endif // PROGRAM_P2_C4_H
