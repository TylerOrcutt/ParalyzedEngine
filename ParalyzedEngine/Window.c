#include "Window.h"
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
int s =  DefaultScreen(dpy);
 if(vi == NULL) {
	printf("\n\tno appropriate visual found\n\n");
        exit(0);
 } 
 else {
	//printf("\n\tvisual %p selected\n", (void *)vi->visualid); /* %p creates hexadecimal output like in glxinfo */
 }


 cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);

 swa.colormap = cmap;
 swa.event_mask = ExposureMask | KeyPressMask|KeyReleaseMask| ButtonReleaseMask | ButtonPressMask;
 
win = XCreateWindow(dpy, root, 0, 0, height,width, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
//  win = XCreateSimpleWindow(dpy,root,0,0,height,width,1, BlackPixel(dpy, s), WhitePixel(dpy, s));
 XMapWindow(dpy, win);
 XStoreName(dpy, win, title);
 XSelectInput(dpy,win,KeyPressMask | KeyReleaseMask | ButtonReleaseMask | ButtonPressMask|  PointerMotionMask);
 


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
XFlush(dpy);
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
 
 
         
       //  if(XCheckMaskEvent(pe->dpy, -1,e) ){

    while(XPending(pe->dpy) > 0) {
        XNextEvent(pe->dpy, e);
 
  // XFlush(pe->dpy);

   if(e->type == ButtonPress){
       //printf("Mouse Button Press: %i\n  X:%i Y:%i ", e->xbutton.button,e->xbutton.x,e->xbutton.y);
       if(pe->onMouseButtonPress!=NULL){
           pe->onMouseButtonPress(e->xbutton.button,e->xbutton.x,e->xbutton.y);
       }
   }

   if(e->type == ButtonRelease){
       //printf("Mouse Button Release: %i\n ", e->xbutton.button);
       if(pe->onMouseButtonRelease!=NULL){
           pe->onMouseButtonRelease(e->xbutton.button,e->xbutton.x,e->xbutton.y);
       }
   }
   if(e->type== MotionNotify){
          //   printf("Mouse Motion Notify\n");
            if(pe->onMouseMotionEvent!=NULL){
           pe->onMouseMotionEvent(e->xbutton.x,e->xbutton.y);
       }
   }
if (e->type == KeyRelease )
{
  XEvent nev;
if( XPending(pe->dpy) > 0){
  XPeekEvent(pe->dpy, &nev); 

   
   //printf("cheaking keyRelease\n");
  if (nev.type == KeyPress && nev.xkey.time == e->xkey.time &&
      nev.xkey.keycode == e->xkey.keycode   )
  {
    
            // XNextEvent(pe->dpy, e);
    /* Key wasn’t actually released */

  }else{
      // XFlush(pe->dpy);
    // printf("KeyRelease: %c     %i\n",XLookupKeysym(&e->xkey,0),e->xkey.keycode);
           if(pe->onKeyRelease!=NULL){
      pe->onKeyRelease(e->xkey.keycode);
  }
 }

}else{
        if(pe->onKeyRelease!=NULL){
      pe->onKeyRelease(e->xkey.keycode);
  }
  //   printf("KeyRelease: %c     %i\n",XLookupKeysym(&e->xkey,0),e->xkey.keycode); 
}
}      



 if(e->type==KeyPress){
      //    XNextEvent(pe->dpy, e);
   // XFlush(pe->dpy);
 XEvent nev;
if( XPending(pe->dpy) > 0){
  XPeekEvent(pe->dpy, &nev); 

   
   //printf("cheaking keyRelease\n");
  if (nev.type == KeyPress && nev.xkey.time == e->xkey.time &&
      nev.xkey.keycode == e->xkey.keycode   )
  {
    
            // XNextEvent(pe->dpy, e);
    /* Key wasn’t actually released */
        // printf("KeyRelease: %c     %i\n",XLookupKeysym(&e->xkey,0),e->xkey.keycode);
  }else{
      // XFlush(pe->dpy);
  // printf("KeyPress: %c     %i\n",XLookupKeysym(&e->xkey,0),e->xkey.keycode);
  if(pe->onKeyPress!=NULL){
   //   pe->onKeyPress(e->xkey.keycode);
     pe->onKeyPress(XLookupKeysym(&e->xkey,0));
  }
 }

}else{
   //  printf("KeyPress: %c     %i\n",XLookupKeysym(&e->xkey,0),e->xkey.keycode); 
     if(pe->onKeyPress!=NULL){
      pe->onKeyPress(XLookupKeysym(&e->xkey,0));
  }
}
}
    }     
        



 
       
 
}

 void PE_window_set_onMouseButtonPress(PEWindow *pe, void (*func)(int,int,int)){
 pe->onMouseButtonPress=func;

}
 void PE_window_set_onMouseButtonRelease(PEWindow *pe, void (*func)(int,int,int)){
 pe->onMouseButtonRelease=func;

}
 void PE_window_set_onMouseMotionEvent(PEWindow *pe, void (*func)(int,int)){
 pe->onMouseMotionEvent=func;

}
 void PE_window_set_onKeyPress(PEWindow *pe, void (*func)(int)){
 pe->onKeyPress=func;

}
 void PE_window_set_onKeyRelease(PEWindow *pe, void (*func)(int)){
 pe->onKeyRelease=func;

}
 void PE_window_cleaUp(PEWindow * pe){

 }