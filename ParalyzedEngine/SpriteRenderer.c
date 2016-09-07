#include "SpriteRenderer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
 
void  PE_init_sprite_renderer(PEShaderProgram * program){
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
      tScaleX = glGetUniformLocation(program->programID,"tScaleX");
      tScaleY = glGetUniformLocation(program->programID,"tScaleY");
      useTexture = glGetUniformLocation(program->programID,"useTexture");
         isText = glGetUniformLocation(program->programID,"isTexxxt");
       mSamplerLoc =glGetUniformLocation(program->programID,"s_texture");
 //     lightColor = glGetUniformLocation(program->programID,"light_color");
         lightPosition = glGetUniformLocation(program->programID,"light_Position");
   
     vPosition = glGetAttribLocation(program->programID,"vPosition");
     mTexLoc = glGetAttribLocation(program->programID,"a_texCoord");
    // printf("vposx: %i\nvposy: %i\nvPostion:%i\n vScalex: %i\nvScaley: %i\ntScaleX: %i\ntScaley: %i\nmTexLoc: %i\n",vposx,vposy,vPosition,vScaleX,vScaleY,tScaleX,tScaleY,mTexLoc);

   

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
      glUniform1i(isText,0);
    glUniform2f(lightPosition,400,300);
 
 glDepthFunc(GL_LEQUAL);   
			     glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  
			     glShadeModel(GL_SMOOTH); 
			     glClearDepth(1.0f);  
 //free (verts);
}
void PE_draw_sprite(PETexture * texture,float x,float y,float width,float height,int tx,int ty,float tw,float th){
glEnable(GL_TEXTURE_2D);
 

            glBindTexture(GL_TEXTURE_2D,texture->textureID);

 tw+=1;
th+=1;
glEnableVertexAttribArray(vPosition); 
glEnableVertexAttribArray(mTexLoc); 
    glUniform1f(vposx,x);
      glUniform1f(vposy,y);
      
      glUniform1f(vScaleX,width);
      glUniform1f(vScaleY,height); 


 //   glUniform1i(mSamplerLoc,0);

    GLfloat sx = (1.f/texture->width)*tw*tx;
    GLfloat sy=(1.f/texture->height)*th*ty;
   // printf("sx: %f\n",sx);
  //  printf("sy: %f\n",sy);
glUniform1f(tposx,sx);
glUniform1f(tposy,sy);
tw-=3;
th-=2;
float sw =((1.f/texture->width)*tw) ;
//printf("sp width: %f\n",sw);
 double sh =(1.f/texture->height)*th  ;
//printf("sp Height: %f\n",sh);
 glUniform1f(tScaleX,sw);
      glUniform1f(tScaleY,sh); 

 glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glDisableVertexAttribArray(mTexLoc);
 glDisableVertexAttribArray(vPosition);

 
}

void PE_draw_rect(float x,float y,float width, float height){
      glUniform1i(useTexture,0);

      glEnableVertexAttribArray(vPosition); 
 
      glUniform1f(vposx,x);
      glUniform1f(vposy,y);
      
      glUniform1f(vScaleX,width);
      glUniform1f(vScaleY,height); 
      
      glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
      glDisableVertexAttribArray(vPosition);
    
      glUniform1i(useTexture,1);
 }