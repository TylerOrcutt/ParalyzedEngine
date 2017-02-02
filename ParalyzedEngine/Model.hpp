#ifndef PE_MODEL_H_
#define PE_MODEL_H_
 #include <GL/glew.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <stdio.h>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
class PEModel{

private:
std::vector<glm::vec3> verticies;
std::vector<unsigned int> vertexIndices;
std::vector<glm::vec3> normals;
std::vector<glm::vec3> uvs;
std::vector<glm::vec3> nverticies;
GLuint vbo;
GLuint vao;/*
float * verts;
GLuint *indicies;*/
public:
PEModel(std::string mfile){
    bool hastexture=false;
    glEnableClientState(GL_VERTEX_ARRAY);
    FILE * file = fopen(mfile.c_str(),"r");
    if(file ==NULL){
     printf("Failed to load model\n");
        return;
    }
    while(1){
        char header[128];
        int res = fscanf(file,"%s",header);
        if(res==EOF){
            break;
        }

         if(strcmp(header,"v")==0){
             glm::vec3 vert;
             fscanf(file,"%f %f %f\n",&vert.x,&vert.y,&vert.z);
             printf("vertex: %f %f %f\n",vert.x,vert.y,vert.z);
            verticies.push_back(vert);
         }else
         if(strcmp(header,"vt")==0){
             hastexture=true;
           /*  glm::vec3 vert;
             fscanf(file,"%f %f %f\n",&vert.x,&vert.y,&vert.z);
             printf("vertex normal: %f %f %f\n",vert.x,vert.y,vert.z);
               normals.push_back(vert);*/
         }else 
         if(strcmp(header,"vn")==0){
             glm::vec3 vert;
             fscanf(file,"%f %f %f\n",&vert.x,&vert.y,&vert.z);
             printf("vertex normal: %f %f %f\n",vert.x,vert.y,vert.z);
               normals.push_back(vert);
         }else 
           if(strcmp(header,"f")==0){
               printf("face\n");
               unsigned int vi[3],uvi[3],ni[3];
               if(hastexture){
               int mt = fscanf(file,"%d/%d/%d %d/%d/%d %d/%d/%d",&vi[0],&uvi[0], &ni[0]
               ,&vi[1],&uvi[1], &ni[1],&vi[2],&uvi[2], &ni[2]);
               if(mt !=9){
                   printf("error reading model file\n");
                   break;
               }
               }else{
                   int mt = fscanf(file,"%d//%d %d//%d %d//%d",&vi[0], &ni[0]
               ,&vi[1],&ni[1],&vi[2], &ni[2]);
               if(mt !=6){
                   printf("error reading model file\n");
                   break;
               }
               }
               vertexIndices.push_back(vi[0]);
        
               vertexIndices.push_back(vi[1]);
               vertexIndices.push_back(vi[2]);
                      printf("vi0 %i vi1 %i vi2 %i",vi[0],vi[1],vi[2]);
           
           }
    }
   
// indicies =  (GLuint*)malloc(sizeof(GLuint) * vertexIndices.size());
  for(int i=0;i<vertexIndices.size();i++){
  unsigned int vi = vertexIndices[i];
  //nverticies.push_back(verticies[vi-1]);
  //   indicies[]
//  indicies[i] = vertexIndices[i];
  }

 /*  verts =(float*) malloc(sizeof(float) *( verticies.size()*3));

  for(int i = 0;i<verticies.size();i++){
      int p = i*3;
      verts[p] = verticies[i].x;
      verts[(i*3) + 1] = verticies[i].y;
      verts[(i*3) + 2] = verticies[i].z;
  }*/
  
float verts []= { -0.5f, 0.5f, 0.f, 
-0.5f, -0.5f, 0.f,
 0.5f, -0.5f, 0.f,
  0.5f,  0.5f, 0.f};
    GLuint indicies [] = {0,1,3,3,1,2};
    
glGenVertexArrays(1,&vao);
glBindVertexArray(vao);
GLuint vboi;
 glGenBuffers(1,&vboi);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi);
 glBufferData(GL_ELEMENT_ARRAY_BUFFER,6* sizeof(GLuint),indicies,GL_STATIC_DRAW);
//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);


glGenBuffers(1,&vbo);
glBindBuffer(GL_ARRAY_BUFFER, vbo);
glBufferData(GL_ARRAY_BUFFER,12* sizeof(float),verts,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0); 



glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);



glBindBuffer(GL_ARRAY_BUFFER,0);



glBindVertexArray(0);


}

void Draw(){
  //  int puni =   glGetUniformLocation(program->programID,"light_Position");
    glColor4f(1,1,1,1);
   glEnableClientState(GL_VERTEX_ARRAY);
    glBindVertexArray(vao);
   // glBindBuffer(GL_ARRAY_BUFFER,vbo);
   glEnableVertexAttribArray(0); 
    glDrawElements(GL_TRIANGLES, 12,GL_UNSIGNED_INT,0);
  glDisableVertexAttribArray(0);
   // glBindBuffer(GL_ARRAY_BUFFER,0);
glBindVertexArray(0);
}
};



#endif