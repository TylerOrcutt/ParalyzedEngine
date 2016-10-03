#ifndef __PE_SHADER_PROGRAM_H__
#define __PE_SHADER_PROGRAM_H__
#include <GL/glew.h>
#include<GL/gl.h>
#ifdef __cplusplus
extern "C"{
#endif
typedef struct PEShaderProgram{
    GLuint programID;
    
}PEShaderProgram;
extern  void PE_init_shaderProgram(PEShaderProgram *);
extern int PE_load_shaderProgram(PEShaderProgram * program,const char * vertexShaderSource, const char * fragmentShaderSource);
extern char * load_shaderSource(const char * shaderFile);

extern const char * PE_default_vertexShader2D();
extern const char * PE_default_fragmentShader2D();
extern const char * PE_default_vertexShader3D();
extern const char * PE_default_fragmentShader3D();

 #ifdef __cplusplus
}
#endif
#endif