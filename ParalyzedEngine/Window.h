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
    int WINDOW_CLOSING;
    void (*onKeyPress)(int);
    void (*onKeyRelease)(int);
     void (*onMouseButtonPress)(int,int,int);
       void (*onMouseButtonRelease)(int,int,int);
       void (*onMouseMotionEvent)(int,int);
    GC gc;
}PEWindow;
 
extern PEWindow* createPEWindow(int,int, const char*);
extern  void getNextEvent(PEWindow *,XEvent*);
extern void PE_window_set_onKeyPress(PEWindow *,void (*func)(int));
extern void PE_window_set_onKeyRelease(PEWindow *,void (*func)(int));
extern void PE_window_set_onMouseButtonPress(PEWindow *,void (*func)(int,int,int));
extern void PE_window_set_onMouseButtonRelease(PEWindow *,void (*func)(int,int,int));
extern void PE_window_set_onMouseMotionEvent(PEWindow *,void (*func)(int,int));
extern void PE_window_cleaUp(PEWindow * pe);

#ifdef __cplusplus
 }
#endif
#endif 