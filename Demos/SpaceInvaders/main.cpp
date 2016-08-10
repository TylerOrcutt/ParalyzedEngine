#include <iostream>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
#include <time.h>
#include <string>
#include <ParalyzedEngine.h>
#include <ParalyzedEngineWindow.h>
#include <vector>
#include "projectile.hpp"
#define resWidth 800
#define resHeight 600



int main(){
    float x=resWidth/2 - 32,y=568;
    ParalyzedEngineTest();
   PEWindow *pe= createPEWindow(800,600,"test");
XEvent                  xev;
int frames=0;
time_t curtime, lastupdate;
time(&lastupdate);
std::vector <Projectile*> proj;
 while(1) {

     frames++ ;
     if(frames>=750){
         time(&curtime);
         double s = difftime(curtime,lastupdate);
         lastupdate=curtime;
         std::cout<<"FPS: "<<frames/s<<std::endl;
         frames = 0;
     }
     
    
 	        getNextEvent(pe, &xev);
              	XGetWindowAttributes(pe->dpy, pe->win, &pe->gwa);
                glViewport(0, 0, pe->gwa.width, pe->gwa.height);
                  glClearColor(0.0, 0.0, 0.0, 1.0);
                   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //	DrawQuad(0,0,32,32); 
          for(int i=0;i<proj.size();i++){
              if(proj[i]->y<0){
                 proj.erase(proj.begin()+i);
                 i--;
                 continue;                 
              }
          proj[i]->y-=10;
              DrawQuad(proj[i]->x,proj[i]->y,proj[i]->width,proj[i]->height);
              
          }
            DrawStrips(x,y);
                glXSwapBuffers(pe->dpy, pe->win);
    // std::cout<<xev.type<<std::endl;
     
      if(xev.type == Expose) {
        	XGetWindowAttributes(pe->dpy, pe->win, &pe->gwa);
                glViewport(0, 0, pe->gwa.width, pe->gwa.height);
        	
                glXSwapBuffers(pe->dpy, pe->win);
        }
                
                
	else if(xev.type == KeyPress) {
      std::cout<<xev.xkey.keycode<<std::endl;
             if(xev.xkey.keycode==39){
             //    y+=10;
               
             }
             if(xev.xkey.keycode==25){
                    
              //   y-=10;
             }
               if(xev.xkey.keycode==40){
                    
                 x+=10;
             }
               if(xev.xkey.keycode==38){
                    
                 x-=10;
             }
           
        }	else if(xev.type == KeyRelease ){
                if(xev.xkey.keycode==65){
                    
                //shoot
                Projectile*prj = new Projectile();
                prj->x=x+48;
                prj->y=y;
                proj.push_back(prj);
                
             }
    }
 } /* this closes while(1) { */
      	glXMakeCurrent(pe->dpy, None, NULL);
 		glXDestroyContext(pe->dpy, pe->glc);
 		XDestroyWindow(pe->dpy, pe->win);
 		XCloseDisplay(pe->dpy);
 		exit(0);

    return 0;
}