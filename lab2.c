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
 glClearColor(0,0,0,1);
 glClear(GL_COLOR_BUFFER_BIT);
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

int main(int argc, char** argv) {
  InitGeometry();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
  glutInitWindowSize(500,500);
  glutCreateWindow("Lab2");
  glutDisplayFunc(display);
  #ifdef __APPLE__
  #else
    glewInit(); 
  #endif
  InitVBO(); 
  glutMainLoop();

}

