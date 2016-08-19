#ifndef __PARALYZED_ENGINE_H_
#define __PARALYZED_ENGINE_H_
#define PE_ENGINE_VERSION "0.0.1"
#define GLEW_STATIC
#define PE_FALSE 0
#define PE_TRUE 1
 
#include "ParalyzedEngineWindow.h"

#ifdef __cplusplus
 extern "C"{
#endif
typedef struct PEVector2d{
    float x,y;
}PEVector2d;
 
    
extern void DrawQuad(float x,float y, float width,float height);
extern void DrawStrips(float,float);


#ifdef __cplusplus
 }
#endif
#endif 