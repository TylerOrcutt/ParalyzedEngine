#ifndef __PARALYZED_ENGINE_H_
#define __PARALYZED_ENGINE_H_
#include "ParalyzedEngineWindow.h"

#ifdef __cplusplus
 extern "C"{
#endif
typedef struct PEVector2d{
    float x,y;
}PEVector2d;
 
extern void ParalyzedEngineTest();
    
extern void DrawQuad(float x,float y, float width,float height);
extern void DrawStrips(float,float);


#ifdef __cplusplus
 }
#endif
#endif 