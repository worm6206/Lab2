#include <stdio.h>
#include <stdlib.h>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#endif

typedef struct
{
 float LL[4];
 float color[4];
} Vertex;
Vertex verts[6]; // triangle vertices
GLubyte tindices[6]; // triangle vertex indices
GLuint vboHandle; // a VBO that contains interleaved positions and colors
GLuint indexVBO;

int press_x, press_y; 
int release_x, release_y; 
float x_angle = 0.0; 
float y_angle = 0.0; 
float scale_size = 1; 

int xform_mode = 0; 

#define XFORM_NONE    0 
#define XFORM_ROTATE  1
#define XFORM_SCALE 2 

void InitGeometry()
{
 verts[0].LL[0] = -0.5; verts[0].LL[1] = -0.5; verts[0].LL[2] = 0; verts[0].LL[3] = 1;
 verts[1].LL[0] = -0.5; verts[1].LL[1] =  0.5; verts[1].LL[2] = 0; verts[1].LL[3] = 1;
 verts[2].LL[0] =  0.5; verts[2].LL[1] =  0.5; verts[2].LL[2] = 0; verts[2].LL[3] = 1;
 verts[3].LL[0] =  0.5; verts[3].LL[1] =  0.5; verts[3].LL[2] = 0; verts[3].LL[3] = 1;
 verts[4].LL[0] =  0.5; verts[4].LL[1] = -0.5; verts[4].LL[2] = 0; verts[4].LL[3] = 1;
 verts[5].LL[0] = -0.5; verts[5].LL[1] = -0.5; verts[5].LL[2] = 0; verts[5].LL[3] = 1;

 verts[0].color[0] = 1; verts[0].color[1] = 1; verts[0].color[2] = 0; verts[0].color[3] = 1;
 verts[1].color[0] = 1; verts[1].color[1] = 1; verts[1].color[2] = 0; verts[1].color[3] = 1;
 verts[2].color[0] = 1; verts[2].color[1] = 1; verts[2].color[2] = 0; verts[2].color[3] = 1;
 verts[3].color[0] = 1; verts[3].color[1] = 0; verts[3].color[2] = 0; verts[3].color[3] = 1;
 verts[4].color[0] = 1; verts[4].color[1] = 0; verts[4].color[2] = 0; verts[4].color[3] = 1;
 verts[5].color[0] = 1; verts[5].color[1] = 0; verts[5].color[2] = 0; verts[5].color[3] = 1;
 // create triangle vertex indices.
 tindices[0] = 0; tindices[1] = 1; tindices[2] = 2;
 tindices[3] = 3; tindices[4] = 4; tindices[5] = 5;
}

void InitVBO()
{
 glGenBuffers(1, &vboHandle); // create two VBO handles, one position, one color handle
 glBindBuffer(GL_ARRAY_BUFFER, vboHandle); // bind the first handle
 glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*6, verts, GL_STATIC_DRAW); // allocate space and copy the
 // position data over
 glBindBuffer(GL_ARRAY_BUFFER, 0); // clean up
 glGenBuffers(1, &indexVBO);
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
 glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*6, tindices, GL_STATIC_DRAW); // load the
 // index data
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0); // clean up
 // by now, we moved the position and color data over to the graphics card. There will be no redundant data
 // copy at drawing time
} 

void display()
{
  glEnable(GL_DEPTH_TEST); 
  glClearColor(0,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity(); 
  gluPerspective(60, 1, .1, 100); 

  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity(); 
  gluLookAt(0,0,3, 0,0,0, 0,1,0); 

  glRotatef(x_angle, 0, 1,0);   
  glRotatef(y_angle, 1,0,0); 
  glScalef(scale_size, scale_size, scale_size); 
  glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
  glEnableClientState(GL_VERTEX_ARRAY); // enable the vertex array on the client side
  glEnableClientState(GL_COLOR_ARRAY); // enable the color array on the client side
  // number of coordinates per vertex (4 here), type of the coordinates,
  // stride between consecutive vertices, and pointers to the first coordinate
  glColorPointer(4, GL_FLOAT, sizeof(Vertex), (char*) NULL+ sizeof(float)*4);
  glVertexPointer(4,GL_FLOAT, sizeof(Vertex), (char*) NULL+ 0);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*) NULL+0);
  glDisableClientState(GL_VERTEX_ARRAY); glDisableClientState(GL_COLOR_ARRAY);
  glutSwapBuffers();
} 

void mymouse(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN) {
    press_x = x; press_y = y; 
    if (button == GLUT_LEFT_BUTTON)
      xform_mode = XFORM_ROTATE; 
   else if (button == GLUT_RIGHT_BUTTON) 
      xform_mode = XFORM_SCALE; 
  }
  else if (state == GLUT_UP) {
    xform_mode = XFORM_NONE; 
  }
}

/////////////////////////////////////////////////////////

void mymotion(int x, int y)
{
    if (xform_mode==XFORM_ROTATE) {
      x_angle += (x - press_x)/5.0; 
      if (x_angle > 180) x_angle -= 360; 
      else if (x_angle <-180) x_angle += 360; 
      press_x = x; 
     
      y_angle += (y - press_y)/5.0; 
      if (y_angle > 180) y_angle -= 360; 
      else if (y_angle <-180) y_angle += 360; 
      press_y = y; 
    }
  else if (xform_mode == XFORM_SCALE){
      float old_size = scale_size;
      scale_size *= (1+ (y - press_y)/60.0); 
      if (scale_size <0) scale_size = old_size; 
      press_y = y; 
    }
  glutPostRedisplay(); 
}

///////////////////////////////////////////////////////////////

void mykey(unsigned char key, int x, int y)
{
        switch(key) {
    case 'q': exit(1);
      break; 
    }
}
///////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
  InitGeometry();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
  glutInitWindowSize(500,500);
  glutCreateWindow("Lab2");
  glutDisplayFunc(display);
  glutMouseFunc(mymouse); 
  glutMotionFunc(mymotion);
  glutKeyboardFunc(mykey); 
  #ifdef __APPLE__
  #else
    glewInit(); 
  #endif
  InitVBO(); 
  glutMainLoop();

}

