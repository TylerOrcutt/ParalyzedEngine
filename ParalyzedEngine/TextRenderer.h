#ifndef _PE_TEXT_RENDERER_H_
#define _PE_TEXT_RENDERER_H_
#include <ft2build.h>
 #include "Texture.h"
 #include <GL/glew.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
#include "SpriteRenderer.h"
#include FT_FREETYPE_H
#ifdef __cpluscplus
extern "C"{
#endif

typedef struct PEFont{
FT_Library ft;
FT_Face face;
GLuint textureID;
}PEFont;
 
PEFont*  PE_TextRenderer_init(){
    PEFont *font = (PEFont*) malloc(sizeof( PEFont));
 


if(FT_Init_FreeType(&font->ft)) {
  fprintf(stderr, "Could not init freetype library\n");
  return NULL;
}

if(FT_New_Face(font->ft, "fonts/DejaVuSans.ttf", 0, &font->face)) {
  fprintf(stderr, "Could not open font\n");
  return NULL;
}
FT_Set_Pixel_Sizes(font->face, 0, 18);
if(FT_Load_Char(font->face, 'X', FT_LOAD_RENDER)) {
  fprintf(stderr, "Could not load character 'X'\n");
  return NULL;
}
glActiveTexture(GL_TEXTURE0);
glGenTextures(1,&font->textureID);
glBindTexture(GL_TEXTURE_2D,font->textureID);


glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


return font;
}
void PE_Render_Text(PEFont * font,const char *text,float x,float y,float width,float height){
FT_GlyphSlot g = font->face->glyph;
const char *p;

GLuint tex;

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	/* We require 1 byte alignment when uploading texture data */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	/* Clamping to edges is important to prevent artifacts when scaling */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	/* Linear filtering usually looks best for text */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



glEnableVertexAttribArray(vPosition); 
glEnableVertexAttribArray(mTexLoc); 
        glUniform1i(isText,1);
  for(p = text; *p; p++) {
    if(FT_Load_Char(font->face, *p, FT_LOAD_RENDER)){
        continue;
    }
    if(strcmp(p,"\n")==0){
     y+=32;
      continue;
    }
   // printf("texture id %i\n",font->textureID);
 

glTexImage2D(GL_TEXTURE_2D, 
0, 
GL_ALPHA,
 g->bitmap.width,
  g->bitmap.rows, 
  0, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);
  float x2=x;
     x = x + g->bitmap_left;
    float y2 = y;
    y = y - g->bitmap_top ;
  //  y=-y;
    float w = g->bitmap.width ;
    float h = g->bitmap.rows ;
    /*if(h<32){
      y+=32-h;
    }
    if(h>32){
      y-=h-32;
    }*/


    glUniform1f(vposx,x);
      glUniform1f(vposy,y);
            glUniform1f(vScaleX,w);
      glUniform1f(vScaleY,h); 
      glUniform1f(tposx,0);
glUniform1f(tposy,0);
 glUniform1f(tScaleX,1);
    glUniform1f(tScaleY,1); 
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
y=y2;
 x=x2;
x += (g->advance.x >> 6)  ;
 y += (g->advance.y >> 6);
   // y += 32;
}
  glDisableVertexAttribArray(mTexLoc);
 glDisableVertexAttribArray(vPosition);
       glUniform1i(isText,0);
//glActiveTexture(GL_TEXTURE0);
}

#ifdef __cpluscplus
}
#endif
#endif