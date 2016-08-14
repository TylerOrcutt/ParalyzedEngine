

#include "ParalyzedEngine.h"
#include <stdio.h>
#include <GL/glew.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
 

void DrawQuad(float x,float y, float width,float height){
   


 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(0., 800, 600, 0., 0., 1.);

 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 //gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);
   glColor3f(1., 0., 0.); 
 glFrontFace(GL_CW);
 glBegin(GL_QUADS);
  glColor3f(1., 0., 0.); 
  glVertex3f(x, y, 0.);
    glVertex3f(x+width, y, 0.);
  //glColor3f(0., 1., 0.);
   glVertex3f( x+width, y+height, 0.);
 // glColor3f(0., 0., 1.); 
  glVertex3f( x,  y+height, 0.);
  //glColor3f(1., 1., 0.);
  // glVertex3f(x,  y+32, 0.);
 glEnd();



}
 void DrawStrips(float x,float y){


 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(0., 800, 600, 0., 0., 1.);

 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 //gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);
   glColor3f(1., 0., 0.); 
/*
 glBegin(GL_QUADS);
  glColor3f(1., 0., 0.); 
  glVertex3f(x, y, 0.);
    glVertex3f(x+32, y-10, 0.);
  //glColor3f(0., 1., 0.);
   glVertex3f( x+64, y, 0.);
 // glColor3f(0., 0., 1.); 
  glVertex3f( x+64,  y+32, 0.);
  //glColor3f(1., 1., 0.);
   glVertex3f(x,  y+32, 0.);
 glEnd();
*/
 glFrontFace(GL_CW);
 glBegin(GL_TRIANGLE_STRIP);	
    glColor3f(0., 1., 0.); 
     glVertex3f( x, y, 0.0f ); //vertex 2
 glVertex3f( x, y+32, 0.0f ); //vertex 1
 glVertex3f( x+48, y-32, 0.0f ); //vertex 3
 
 glVertex3f( x+96, y+132, 0.0f ); //vertex 3
 glVertex3f( x+96, y, 0.0f ); //vertex 4
 glEnd();
     
 }
