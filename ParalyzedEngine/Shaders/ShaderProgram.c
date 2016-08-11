#include "ShaderProgram.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
 
 
void PE_init_shaderProgram(PEShaderProgram * program){
    program->programID=-1;
}

int PE_load_shaderProgram(PEShaderProgram * program, const char * vertexShaderSource, const char * fragmentShaderSource){
      printf("Loading Shader programs\n");

     GLuint programID = glCreateProgram();
 GLenum err;
err = glGetError();
printf(" err return: %d \n", err); 
            program->programID = glCreateProgram();
            printf("programID: %i\n",programID);
      if(program->programID<=0){
            printf("Failed to create shader program\n");

        return -1;
      }      

      GLuint vertexShader,fragmentShader; 
      vertexShader = glCreateShader(GL_VERTEX_SHADER);
      fragmentShader=  glCreateShader(GL_FRAGMENT_SHADER);

      glShaderSource(vertexShader,1,vertexShaderSource,strlen(vertexShaderSource));
      glShaderSource(fragmentShader,1,fragmentShaderSource,strlen(fragmentShaderSource));

      glCompileShader(vertexShader);
      glCompileShader(fragmentShader);
    
    GLuint compiled;
       compiled=GL_FALSE;
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&compiled);
    if(compiled==GL_FALSE){
        printf("Failed to compile vertex shader\n");
        return -1;
    }
       compiled=GL_FALSE;
     glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&compiled);
    if(compiled==GL_FALSE){
        printf("Failed to compile fragmentShader shader\n");
        return -1;
    }

    glAttachShader(program->programID,vertexShader);
    glAttachShader(program->programID,fragmentShader);

    glLinkProgram(program->programID);

   compiled=GL_FALSE;
    glValidateProgram(program->programID);
    glGetProgramiv(program->programID,GL_VALIDATE_STATUS,&compiled);
    if(compiled==GL_FALSE){
        printf("failed to link shader program\n");
     return -1;
    }
    printf("ShaderProgram linked\n");
}
 char * load_shaderSource(const char * shaderFile){
     return "";

 }

 const char * PE_default_vertexShader(){
    char * source = malloc(sizeof(char)*1024);

     strcat(source,"attribute  vec4  vPosition;\n");
    strcat(source,"uniform float vposx;\n");
    strcat(source,"uniform float vposy;\n");
    strcat(source,"uniform float vScaleX;\n");
    strcat(source,"uniform float vScaleY;\n");
    strcat(source,"uniform float tposx;\n");
    strcat(source,"uniform float tposy;\n");
    strcat(source,"uniform float tScaleX;\n");
    strcat(source,"uniform float tScaleY;\n");
    strcat(source,"attribute vec2 a_texCoord;\n");
    strcat(source,"varying vec2 v_texCoord;\n");
    strcat(source,"void main() {\n");
    strcat(source,"vec4 position = vPosition;\n");
    strcat(source,"position.x=position.x*vScaleX + vposx;\n");
    strcat(source,"position.y=position.y*vScaleY+ vposy;\n");
    strcat(source,"gl_Position =  gl_ModelViewProjectionMatrix*position;\n");
    strcat(source,"vec2 txtpos = a_texCoord;\n");
    strcat(source,"txtpos.x=txtpos.x*tScaleX+tposx;\n");
    strcat(source,"txtpos.y=txtpos.y*tScaleY+tposy;\n");
    strcat(source,"v_texCoord = txtpos;\n");
     strcat(source,"gl_FrontColor = gl_Color;\n");
      strcat(source,"}");
      return source;
 }

 const char * PE_default_fragmentShader(){
    char * source = malloc(sizeof(char)*512);

     strcat(source,"varying vec2 v_texCoord;\n");
    strcat(source,"uniform sampler2D s_texture;\n");
    strcat(source,"uniform int useTexture;\n");
 
    strcat(source,"void main() {\n");
    strcat(source,"if(useTexture==1){\n");
    strcat(source,"gl_FragColor = texture2D( s_texture, v_texCoord);\n");

    strcat(source,"}else{\n");
    strcat(source,"gl_FragColor=gl_Color;\n");
    strcat(source,"}\n");
 
      return source;
 }

 
 
 