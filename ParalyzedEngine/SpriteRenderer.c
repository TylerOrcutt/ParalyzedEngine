#include "SpriteRenderer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
 
void  PE_Sprite_Renderer_init(PEShaderProgram * program){
sprogram=program;
       glUseProgram(1);
   // printf("init spriteRenderer\n");
     glUseProgram(program->programID);
    vposx = glGetUniformLocation(program->programID,"vposx");
     vposy = glGetUniformLocation(program->programID,"vposy");
      vScaleX = glGetUniformLocation(program->programID,"vScaleX");
      vScaleY = glGetUniformLocation(program->programID,"vScaleY");
      tposx = glGetUniformLocation(program->programID,"tposx");
      tposy = glGetUniformLocation(program->programID,"tposy");
      tScaleX = glGetUniformLocation(program->programID,"tScalex");
      tScaleY = glGetUniformLocation(program->programID,"tScaleY");
      useTexture = glGetUniformLocation(program->programID,"useTexture");
      mSamplerLoc =glGetUniformLocation(program->programID,"s_texture");

     vPosition = glGetAttribLocation(program->programID,"vPosition");
     mTexLoc = glGetAttribLocation(program->programID,"a_texCoord");
     printf("vposx: %i\nvposy: %i\nvPostion:%i\n vScalex: %i\nvScaley: %i\ntScaley: %i\nmTexLoc: %i\n",vposx,vposy,vPosition,vScaleX,vScaleY,tScaleY,mTexLoc);



     Square_verts=malloc(sizeof(float)*12);
     float verts[12] ={0,0,0,1,0,0,0,1,0,1,1,0};
     memcpy(Square_verts,verts,sizeof verts);


    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition,3,GL_FLOAT,GL_FALSE,12,Square_verts);
    glDisableVertexAttribArray(vPosition);

     tex_verts=malloc(sizeof(float)*8);
    float tverts[8] ={0,0,1,0,0,1,1,1};
     memcpy(tex_verts,tverts,sizeof tverts);

     glEnableVertexAttribArray(mTexLoc);
         glVertexAttribPointer(mTexLoc,2,GL_FLOAT,GL_FALSE,8,tex_verts);
    glDisableVertexAttribArray(mTexLoc);

    glUniform1i(mSamplerLoc,0);
    glUniform1i(useTexture,1);
 
 //free (verts);
}
void PE_Sprite_Draw(float x,float y,float width,float height){
glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,1);
     glUseProgram(1);
glColor4f(0.f,1.f,0.f,1.f);
    glUniform1f(vposx,x);
      glUniform1f(vposy,y);
      
      glUniform1f(vScaleX,width);
      glUniform1f(vScaleY,height); 


    glUniform1i(mSamplerLoc,0);
glUniform1f(tposx,1.f/320*320/10*3);
glUniform1f(tposy,1.f/320*320/10*0);
 glUniform1f(tScaleX,1.f/320*320/10);
      glUniform1f(tScaleY,1.f/320*320/10); 

glEnableVertexAttribArray(vPosition); 
glEnableVertexAttribArray(mTexLoc); 


 glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glDisableVertexAttribArray(mTexLoc);
 glDisableVertexAttribArray(vPosition);
 
 
}