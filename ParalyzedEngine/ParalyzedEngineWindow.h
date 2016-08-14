#ifndef __PARALYZED_ENGINE_WINDOW_H_
#define __PARALYZED_ENGINE_WINDOW_H_
#include<X11/X.h>
#include<X11/Xlib.h>
#include <GL/glew.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
#ifdef __cplusplus
 extern "C"{
#endif
typedef struct PEWindow {
    Window  win;
    Display *  dpy;   
    XWindowAttributes gwa;
    GLXContext              glc;
    GC gc;
}PEWindow;
 
extern PEWindow* createPEWindow(int,int, const char*);
extern  void getNextEvent(PEWindow *,XEvent*);

#ifdef __cplusplus
 }
#endif
#endif 