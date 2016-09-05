#ifndef __PE_SPRITERENDERER_H_
#define __PE_SPRITERENDERER_H_
 #include "Shaders/ShaderProgram.h"
 #include "Texture.h"
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
extern void PE_init_sprite_renderer(PEShaderProgram * program);
extern void PE_draw_sprite(PETexture *,float x,float y,float width,float height,int tx,int ty,float tw,float th);
extern void PE_draw_rect(float x,float y,float width, float height);

 

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
 GLint lightColor;
 GLint lightPosition;
GLint mTexLoc; 

#ifdef __cplusplus
 }
#endif
#endif 