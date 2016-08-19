#include "ParalyzedEngineWindow.h"
#include<stdio.h>
#include<stdlib.h>
#include<X11/X.h>
#include<X11/Xlib.h>
#include <GL/glew.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
int x11_fd;
fd_set in_fds;
struct timeval tv;
PEWindow* createPEWindow(int height,int width,const char *title){
  //  printf("creating window\n");
    Display                 *dpy;
Window                  root;
GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo             *vi;
Colormap                cmap;
XSetWindowAttributes    swa;
Window                  win;
GLXContext              glc;
XWindowAttributes       gwa;
XEvent                  xev;

     dpy = XOpenDisplay(NULL);
 
 if(dpy == NULL) {
 	printf("\n\tcannot connect to X server\n\n");
        exit(0);
 }
    
 root = DefaultRootWindow(dpy);
x11_fd = ConnectionNumber(dpy);
 vi = glXChooseVisual(dpy, 0, att);

 if(vi == NULL) {
	printf("\n\tno appropriate visual found\n\n");
        exit(0);
 } 
 else {
	//printf("\n\tvisual %p selected\n", (void *)vi->visualid); /* %p creates hexadecimal output like in glxinfo */
 }


 cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);

 swa.colormap = cmap;
 swa.event_mask = ExposureMask | KeyPressMask;
 
 win = XCreateWindow(dpy, root, 0, 0, height,width, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);

 XMapWindow(dpy, win);
 XStoreName(dpy, win, title);
 XSelectInput(dpy,win,InputOutput|KeyPressMask | KeyReleaseMask);
 
 glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
 glXMakeCurrent(dpy, win, glc);
 
 
 glEnable(GL_DEPTH_TEST); 
 PEWindow * pe = (PEWindow*)malloc(sizeof(PEWindow));
 (*pe).win = win;
 (*pe).dpy=dpy;
 (*pe).gwa =gwa;
  (*pe).glc =glc;
     if(glewInit()){
  printf("failed to init glew\n");

 
}
pe->WINDOW_CLOSING=0;
  return pe;
 /*
 while(1) {
 	XNextEvent(dpy, &xev);
        
        if(xev.type == Expose) {
        	XGetWindowAttributes(dpy, win, &gwa);
                glViewport(0, 0, gwa.width, gwa.height);
        //	DrawAQuad(); 
                glXSwapBuffers(dpy, win);
        }
                
	else if(xev.type == KeyPress) {
        	glXMakeCurrent(dpy, None, NULL);
 		glXDestroyContext(dpy, glc);
 		XDestroyWindow(dpy, win);
 		XCloseDisplay(dpy);
 		exit(0);
        }
    } /* this closes while(1) { */
}

void getNextEvent(PEWindow *pe,XEvent* e){
   int events;

 // if(XEventsQueued(pe->dpy, QueuedAfterFlush)){
    //   printf("events %i \n",events);
         
          if(XCheckMaskEvent(pe->dpy,-1,e) ){
                 XNextEvent(pe->dpy, e);

  if(e->type==ClientMessage){
    if(e->xclient.data.l[0]==WM_DELETE_WINDOW){
      printf("closeing");
    }
  }

 if(e->type==KeyRelease  && XEventsQueued(pe->dpy, QueuedAfterReading)){
      //    XNextEvent(pe->dpy, e);
          XEvent  *peak = malloc(sizeof(XEvent)); 
          XPeekEvent(pe->dpy,peak);
          if(peak==NULL){
       //  return;
          }
    if (peak->type == KeyPress && peak->xkey.time == e->xkey.time &&
      peak->xkey.keycode == e->xkey.keycode){
    printf("KeyRelease: %c     %i\n",XLookupKeysym(&e->xkey,0),e->xkey.keycode);
  XFlush(pe->dpy);
  /* if(pe->onKeyRelease!=NULL){
   (*pe->onKeyRelease)();
   }*/
      }
 }

         //  }
                  //   XFlush(pe->dpy);
                    //   break;
}
 
}
 void PE_window_set_onKeyPress(PEWindow *pe, void (*func)()){
 pe->onKeyPress=func;

}

 void PE_window_cleaUp(PEWindow * pe){

 }