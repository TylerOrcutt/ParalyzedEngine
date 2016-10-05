#include "ShaderProgram.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
 
 
void PE_init_shaderProgram(PEShaderProgram * program){
    program->programID=-1;
}

int PE_load_shaderProgram(PEShaderProgram * program, const char * vertexShaderSource, const char * fragmentShaderSource){
      printf("Loading Shader programs\n");

 
            program->programID = glCreateProgram();
            printf("programID: %i\n",program->programID);
      if(program->programID<=0){
            printf("Failed to create shader program\n");

        return -1;
      }      

      GLuint vertexShader,fragmentShader; 
      vertexShader = glCreateShader(GL_VERTEX_SHADER);
      fragmentShader=  glCreateShader(GL_FRAGMENT_SHADER);

     GLuint vlength = strlen(vertexShaderSource);
      glShaderSource(vertexShader,1,&vertexShaderSource,&vlength);
      vlength = strlen(fragmentShaderSource);
      glShaderSource(fragmentShader,1,&fragmentShaderSource,&vlength);


  printf("Building shader program\n");
     glCompileShader(vertexShader);
      glCompileShader(fragmentShader);
    
    GLuint compiled;
       compiled=GL_FALSE;
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&compiled);
    if(compiled==GL_FALSE){
        int len=1024;
        char * err = malloc(sizeof(char)*len);
        glGetShaderInfoLog(vertexShader,1024,&len,err);

        printf("Failed to compile vertex shader\n %s \n",err);
      return -1;
    }
       compiled=GL_FALSE;
     glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&compiled);
    if(compiled==GL_FALSE){
          int len=1024;
        char * err = malloc(sizeof(char)*len);
        glGetShaderInfoLog(fragmentShader,1024,&len,err);

        printf("Failed to compile fragmentShader shader\n %s \n",err);
        return -1;
    }
   printf("Linking shader program\n"); 

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
    printf("ShaderProgram build successful\n"); 
    return 1;
}
 char * load_shaderSource(const char * shaderFile){
     return "";

 }

 const char * PE_default_vertexShader2D(){
    char * source = malloc(sizeof(char)*1024);

           sprintf( source, "%s", "attribute  vec4  vPosition;\n" );

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
 //strcat(source,"uniform vec3 attenuation;\n");
 //strcat(source,"uniform float intensity;\n");
     strcat(source,"uniform  vec2 light_Position;");
     strcat(source,"uniform vec4 light_color;");
     //   strcat(source,"varying vec4 out_light_color;");
    strcat(source,"void main() {\n");
    strcat(source,"vec4 position = vPosition;\n");  
    strcat(source,"position.x=position.x*vScaleX + vposx;\n");
    strcat(source,"position.y=position.y*vScaleY+ vposy;\n");
     strcat(source,"gl_Position =  gl_ModelViewProjectionMatrix*position;\n");
      strcat(source,"light_Position = vec2(400,300);");
          strcat(source,"light_color = vec4(0,1,0,1);");
     // strcat(source,"light_Position=gl_ModelViewProjectionMatrix.*light_Position;");
   //       strcat(source,"light_Position = vec2(400,300);");

     
/*
    strcat(source,"float dist =distance(light_Position,position.xy);\n");
    strcat(source,"intensity=1.0;");
     strcat(source,"attenuation= vec3(0.10,0.10,0.010);");
          strcat(source,"float att = 10.0/(attenuation.x+(attenuation.y*dist)+(attenuation.z*pow(dist,2)));");
 // strcat(source,"float att = 1.0/dist;");
 strcat(source,"light_color=vec4(1,1,1,1);");
  //strcat(source,"out_light_color= vec4(light_color.xyz,1.0)* vec4(att,att,att,1.0);");
 //   strcat(source,"out_light_color= vec4(light_color.xyz,1.0)* vec4(att,att,pow(att,3),1.0);");
  //  strcat(source,"out_light_color= vec4(1,1,1,1)* vec4(att,att,att,pow(att,3));");
  strcat(source,"out_light_color= vec4(light_color.xyz,1.0) * vec4(att,att,att,1.0);");*/
   //        strcat(source,"if(abs(dist)<=100.0){\n");
  //     strcat(source,"light_color= vec4(1,1,1,1);\n");
  //strcat(source,"}else{\n");
 //  strcat(source,"light_color= vec4(.085,.085,.085,1);\n");
  //strcat(source,"}\n");
   
    
    
    strcat(source,"vec2 txtpos;\n");
     strcat(source,"txtpos.x=( a_texCoord.x*tScaleX)+tposx;\n");
    strcat(source,"txtpos.y=( a_texCoord.y*tScaleY)+tposy;\n");
    strcat(source,"v_texCoord = txtpos;\n");
     strcat(source,"gl_FrontColor = gl_Color;\n");
      strcat(source,"}");

      return source;
 }

 const char * PE_default_fragmentShader2D(){
    char * source = malloc(sizeof(char)*1024);
           sprintf( source, "%s", "varying vec2 v_texCoord;" );

    strcat(source,"uniform sampler2D s_texture;");
    strcat(source,"uniform int useTexture;");
     strcat(source,"uniform int isTexxxt;");
        strcat(source,"uniform int numLights;");
   strcat(source,"uniform vec2 light_Position[2];");
     strcat(source,"uniform vec4 light_color[2];");
       //  strcat(source,"varying vec4 out_light_color;");

    strcat(source,"void main() {");


   strcat(source,"if(useTexture==1 && isTexxxt==1 ){");
     strcat(source,"if(texture2D( s_texture, v_texCoord).a<0.5){");
     
    strcat(source,"gl_FragColor =  vec4(0,0,0,0);");
     strcat(source,"}else{"); 
         strcat(source,"gl_FragColor=gl_Color;");
       strcat(source,"}");


    strcat(source,"} else if(useTexture==1){");
    //     strcat(source,"light_Position = vec2(0,0);");
              
              strcat(source,"vec4 pixel_color = texture2D( s_texture, v_texCoord);");
                    strcat(source,"vec3 finalLightColor ;");
              strcat(source,"for(int i=0;i<2;i++){");
              strcat(source,"light_Position[i]=vec2(200+(i*200),100+(i*200));");
              strcat(source,"float dist =length(light_Position[i]-gl_FragCoord.xy);\n");
              strcat(source,"float att = 1.0 / ( 0.5515 + (0.001*dist) + (0.000170*dist*dist) );");
              strcat(source,"light_color[i] = vec4(0.25+(i*0.80),0.25-(i-1)*.85,0.25,1);");
              strcat(source,"finalLightColor=finalLightColor+((vec4(att,att,att,1.0)*light_color[i]));");
               strcat(source,"}");
             // strcat(source,"if(finalLightColor.x<=0.05 || finalLightColor.y<=0.05 || finalLightColor.z<=0.05){ finalLightColor = vec3(finalLightColor.x+0.05,finalLightColor.y+0.05,finalLightColor.z+0.05);}");   
strcat(source,"finalLightColor = vec3(finalLightColor.x+0.05,finalLightColor.y+0.05,finalLightColor.z+0.05);");   

 
  //strcat(source,"if(att<=0.5){ att=0.5;}");
   //strcat(source,"gl_FragColor = (pixel_color)*(vec4(att,att,att,1.0)*light_color);");
 strcat(source,"gl_FragColor = (pixel_color)*vec4(finalLightColor,1.0);");
        strcat(source,"}else{"); 
    strcat(source,"gl_FragColor=gl_Color;");
     strcat(source,"}");
        strcat(source,"}");
 
      return source;
 }

 
 
 
  const char * PE_default_vertexShader3D(){
    char * source = malloc(sizeof(char)*1024);

              sprintf( source, "%s", "#version 400 core\n" );
           strcat(source,"in vec3 position;");
          strcat(source,"uniform mat4 tmatrix;");

 
    strcat(source,"void main() {");
   // strcat(source,"gl_Position = tmatrix * vec4(position,1.0);");

        strcat(source,"}");

      return source;
 }

 const char * PE_default_fragmentShader3D(){
    char * source = malloc(sizeof(char)*512);
           sprintf( source, "%s", "#version 400 core\n" );
       //    strcat(source,"in vec3 position;");
           strcat(source,"");

 
    strcat(source,"void main() {");
   

        strcat(source,"}");
 
      return source;
 }
