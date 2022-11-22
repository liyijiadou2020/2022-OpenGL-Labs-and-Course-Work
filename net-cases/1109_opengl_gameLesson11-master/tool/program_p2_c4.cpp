#include "../tool/program_p2_c4.h"
#include <QMatrix4x4>
#include <QOpenGLExtraFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>

PROGRAM_P2_C4::PROGRAM_P2_C4()
{
        _timer  =   1;
}

bool PROGRAM_P2_C4::initialize()
{
    const char* vs  =
    {
        "uniform float u_time;"
        "uniform    vec3    u_centerPosition;"
        "attribute  float   _lifetime;"
        "attribute  vec3    _startPosition;"
        "attribute  vec3    _endPosition;"
        "varying    float   v_lifetime;"
        "void main()"
        "{"
        "  if ( u_time <= _lifetime )"
        "  {"
        "    gl_Position.xyz    = _startPosition + (u_time * _endPosition);"
        "    gl_Position.xyz    += u_centerPosition;"
        "    gl_Position.w      = 1.0;"
        "  }"
        "  else"
        "     gl_Position = vec4( -1000, -1000, 0, 0 );"
        "  v_lifetime = 1.0 - ( u_time / _lifetime );"
        "  v_lifetime = clamp ( v_lifetime, 0.0, 1.0 );"
        "  gl_PointSize = ( v_lifetime * v_lifetime ) * 40.0;"
        "}"
    };
    const char* ps  =
    {
        "precision mediump float;"
        "uniform    vec4        _color;"
        "varying    float       v_lifetime;"
        "uniform    sampler2D   _texture;"
        "void main()"
        "{"
        "  vec4 texColor;"
        "  texColor         =   texture2D( _texture, gl_PointCoord );"
        "  gl_FragColor     =   vec4( _color ) * texColor;"
        "  gl_FragColor.a   *=  v_lifetime;"
        "}"
    };

    bool    res =   createProgram(vs,ps);
    if(res)
    {
        _lifetimeLoc         =   glGetAttribLocation ( _programId, "_lifetime" );
        _startPositionLoc    =   glGetAttribLocation ( _programId, "_startPosition" );
        _endPositionLoc      =   glGetAttribLocation ( _programId, "_endPosition" );

        // Get the uniform locations
        _timeLoc             =   glGetUniformLocation ( _programId, "u_time" );
        _centerPositionLoc   =   glGetUniformLocation ( _programId, "u_centerPosition" );
        _colorLoc            =   glGetUniformLocation ( _programId, "_color" );
        _samplerLoc          =   glGetUniformLocation ( _programId, "_texture" );
    }
    return  res;
}

void PROGRAM_P2_C4::begin()
{
    glUseProgram(_programId);
    glEnableVertexAttribArray ( _lifetimeLoc );
    glEnableVertexAttribArray ( _endPositionLoc );
    glEnableVertexAttribArray ( _startPositionLoc );
}

void PROGRAM_P2_C4::end()
{
    glDisableVertexAttribArray ( _lifetimeLoc );
    glDisableVertexAttribArray ( _endPositionLoc );
    glDisableVertexAttribArray ( _startPositionLoc );
    glUseProgram(0);
}
