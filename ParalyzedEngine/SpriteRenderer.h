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

 

//extern PEShaderProgram * sprogram;

     extern float *Square_verts;
       extern  float *tex_verts;
extern GLint vPosition;
extern GLint vposx;
extern GLint vposy;
extern GLint vScaleX;
 extern GLint vScaleY;

extern GLint tposx;
extern GLint tposy;
extern GLint tScaleX;
extern GLint tScaleY;
extern GLint mSamplerLoc;
extern GLint useTexture;
extern GLint lightColor;
extern GLint lightPosition;
extern  GLint isText;
extern GLint mTexLoc; 

#ifdef __cplusplus
}
#endif

#endif 
