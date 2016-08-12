#include "SpriteRenderer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
     vPosition = glGetAttribLocation(program->programID,"vPosition");
     printf("vposx: %i\nvposy: %i\nvPostion:%i\n vScalex: %i\nvScaley: %i\n",vposx,vposy,vPosition,vScaleX,vScaleY);



     Square_verts=malloc(sizeof(float)*12);
     float verts[12] ={0,0,0,1,0,0,0,1,0,1,1,0};
     memcpy(Square_verts,verts,sizeof verts);
    glEnableVertexAttribArray(vPosition);

  glVertexAttribPointer(vPosition,3,GL_FLOAT,GL_FALSE,12,Square_verts);
  glDisableVertexAttribArray(vPosition);
 
 //free (verts);
}
void PE_Sprite_Draw(float _x,float y,float width,float height){

     glUseProgram(1);
glColor4f(0.f,1.f,0.f,1.f);
        glUniform1f(vposx,200);
        printf("%i",glGetError());
      
           
glEnableVertexAttribArray(vPosition); 

     //glUniform1f(vScaleX,32.f);
   //  glUniform1f(vScaleY,32.f); 





 glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
 glDisableVertexAttribArray(vPosition);
 
}