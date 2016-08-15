#ifndef __PE_SPRITERENDERER_H_
#define __PE_SPRITERENDERER_H_
 #include "Shaders/ShaderProgram.h"
 #include <GL/glew.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
#ifdef __cplusplus
 extern "C"{
#endif

typedef struct PE_ShaderVars{
 int vPosition;
 int vposx;
 int vposy;
} PE_ShaderVars;
extern void PE_Sprite_Renderer_init(PEShaderProgram * program);
extern void PE_Sprite_Draw(float x,float y,float width,float height);

 

 PEShaderProgram * sprogram;
      float *Square_verts;
        float *tex_verts;
 GLint vPosition;
 GLint vposx;
 GLint vposy;
 GLint vScaleX;
 GLint vScaleY;

 GLint tposx;
 GLint tposy;
 GLint tScaleX;
 GLint tScaleY;
 GLint mSamplerLoc;
 GLint useTexture;
GLint mTexLoc; 

#ifdef __cplusplus
 }
#endif
#endif 