#ifndef __PARALYZED_ENGINE_TEXTURE_H_
#define __PARALYZED_ENGINE_TEXTURE_H_

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include<SOIL/SOIL.h>
#ifdef __cplusplus
 extern "C"{
#endif
typedef struct PETexture{
    int width;
    int height;
    GLuint textureID;
}PETexture;
 
 extern PETexture *PE_load_texture(const char * );
 

#ifdef __cplusplus
 }
#endif
#endif 