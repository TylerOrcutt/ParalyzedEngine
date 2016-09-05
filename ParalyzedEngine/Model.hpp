#ifndef PE_MODEL_H_
#define PE_MODEL_H_
 
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <stdio.h>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
class PEModel{

private:
std::vector<glm::vec3> verts;

public:
PEModel(std::string mfile){
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
         }
    }


}
};



#endif