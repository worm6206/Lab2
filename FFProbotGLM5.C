
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stack> 
#include <math.h> 

using namespace std; 

#ifdef __APPLE__
#include <GLUT/glut.h> 
#include <OpenGL/gl.h> 
#else 
#include <GL/glut.h> 
#include <GL/gl.h> 
#endif

#include<glm/glm.hpp> 
#include<glm/gtx/transform.hpp> 

float vertices[] = {-0.05, -0.05, 0.0,  // first triangle
				     0.05, -0.05, 0.0, 
				     0.05,  0.05, 0.0, 
				    -0.05,  0.05, 0.0, }; 

GLubyte tindices[6];  

GLuint vboHandle[1];   // a VBO that contains interleaved positions and colors 
GLuint indexVBO; 

float angle1=0, angle2=0, angle3=0, angle4=0, angle0=0;

glm::mat4 modelM = glm::mat4(1.0f); 

vector<glm::mat4> mat_list;
stack<glm::mat4> mat_stack; 


//////////////////////////////////////////////////////////////////////////////////
//
// create VBO objects and send the triangle vertices/colors to the graphics card
// 
void InitVBO() 
{
  glGenBuffers(1, vboHandle);   // create an interleaved VBO object
  glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);   // bind the first handle 

  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*12, vertices, GL_STATIC_DRAW); // allocate space and copy the position data over
  glBindBuffer(GL_ARRAY_BUFFER, 0);   // clean up 

  tindices[0] = 0;   tindices[1] = 1;   tindices[2] = 2; 
  tindices[3] = 0;   tindices[4] = 2;   tindices[5] = 3; 

  glGenBuffers(1, &indexVBO); 
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO); 
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*6, tindices, GL_STATIC_DRAW);  // load the index data 

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);  // clean up 

} 



//////////////////////////////////////////////////////////////////////////////////////////

void draw_square(glm::mat4 m, float color[3]) {

  float v_in[4]; 
  float *v_out; 

  glLoadMatrixf(&m[0][0]); 

  glPointSize(10); 
  glColor3f(color[0],color[1],color[2]); 

  printf("hello\n"); 

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*)NULL+0); 
  //  glDrawElements(GL_POINTS, 6, GL_UNSIGNED_BYTE, (char*)NULL+0); 

} 

/////////////////////////////////////////////////////////////
void display() 
{ 
  glClearColor(0,0,0,1); 
  glClear(GL_COLOR_BUFFER_BIT); 

  glEnableClientState(GL_VERTEX_ARRAY); // enable the vertex array 
  glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]); 
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO); 

  // the following code tells OpenGL how to walk through the vertex array 
  glVertexPointer(3,GL_FLOAT, 0,0); //number of coordinates per vertex (3 here), type of the coordinates, 
                                    // stride between consecutive vertices, and pointers to the first coordinate


  vector <glm::mat4>::const_iterator mi;

  float color[3]; 

  color[0] = 0; color[1] = 0; color[2] = 1;
  mat_stack.push(modelM); // 0
  modelM = glm::rotate(modelM, angle0, glm::vec3(0.0f, 0.0f, 1.0f)); // 0+
  

  mat_stack.push(modelM); // 0+


  mat_stack.push(modelM); 
  modelM = glm::scale(modelM, glm::vec3(4.0f, 3.0f, 1.0f));   
  draw_square(modelM, color); 
  modelM = mat_stack.top();
  mat_stack.pop();
  
  // mat_stack.push(modelM);

  //////////////////////////////
  //    Right Arm 
  //////////////////////////////
  
  color[0] = 1; color[1] = 0; color[2] = 0; 
  // 0 in stack, 1 in modelM
  modelM = glm::translate(modelM, glm::vec3(0.2f, 0.0f, 0.0f));
  modelM = glm::rotate(modelM, angle1, glm::vec3(0.0f, 0.0f, 1.0f));
  modelM = glm::translate(modelM, glm::vec3(0.05f, 0.0f, 0.0f));  // rotation center
  
  mat_stack.push(modelM);  // 1*, stack is now 0|1*
  modelM = glm::scale(modelM, glm::vec3(2.0f, 2.0f, 1.0f)); 
  draw_square(modelM, color);
  modelM = mat_stack.top();  
  mat_stack.pop(); 





  color[0] = 0; color[1] = 1; color[2] = 0; 
  modelM = glm::translate(modelM, glm::vec3(0.1f, 0.0f, 0.0f));
  modelM = glm::rotate(modelM, angle2, glm::vec3(0.0f, 0.0f, 1.0f));
  modelM = glm::translate(modelM, glm::vec3(0.05f, 0.0f, 0.0f));  

  mat_stack.push(modelM); 
  modelM = glm::scale(modelM, glm::vec3(2.0f, .6f, 1.0f)); 
  draw_square(modelM, color); 
  modelM = mat_stack.top();  
  mat_stack.pop();



  modelM = mat_stack.top();  
  mat_stack.pop();
  // mat_stack.push(modelM);

  //////////////////////////////
  //    Left Arm
  //////////////////////////////

  color[0] = 1; color[1] = 0; color[2] = 0; 
  modelM = glm::translate(modelM, glm::vec3(-0.2f, 0.0f, 0.0f));
  modelM = glm::rotate(modelM, angle3, glm::vec3(0.0f, 0.0f, 1.0f));
  modelM = glm::translate(modelM, glm::vec3(-0.05f, 0.0f, 0.0f));  // rotation center
  
  mat_stack.push(modelM);  
  modelM = glm::scale(modelM, glm::vec3(2.0f, 2.0f, 1.0f)); 
  draw_square(modelM, color);
  modelM = mat_stack.top();  
  mat_stack.pop(); 





  color[0] = 0; color[1] = 1; color[2] = 0; 
  modelM = glm::translate(modelM, glm::vec3(-0.1f, 0.0f, 0.0f));
  modelM = glm::rotate(modelM, angle4, glm::vec3(0.0f, 0.0f, 1.0f));
  modelM = glm::translate(modelM, glm::vec3(-0.05f, 0.0f, 0.0f));  


  mat_stack.push(modelM); 
  modelM = glm::scale(modelM, glm::vec3(2.0f, .6f, 1.0f)); 
  draw_square(modelM, color);
  modelM = mat_stack.top();  
  mat_stack.pop(); 

  modelM = mat_stack.top();  
  mat_stack.pop();


  
  color[0] = 0; color[1] = 1; color[2] = 0; 

  printf(" ****\n"); 
  for (mi=mat_list.begin(); mi!=mat_list.end(); mi++) {
    printf(" hello!\n"); 
    draw_square((*mi), color); 
  } 

  glDisableClientState(GL_VERTEX_ARRAY); 

  glutSwapBuffers(); 

} 
void mymouse(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN)
    printf(" click on [%d, %d]!\n", x,y); 
  else if (state == GLUT_UP) 
    printf(" mouse button up! \n"); 

  glutPostRedisplay(); 
}
///////////////////////////////////////////////////////////////

void mykey(unsigned char key, int x, int y)
{
        float d_angle = 10; 
	if (key == 'q') exit(1); 
	if (key == 'R') 
	  modelM = glm::rotate(modelM, d_angle, glm::vec3(0.0f, 0.0f, 1.0f)); 
	//  modelM =  rotatez(modelM, d_angle);
	if (key == 'r') 
	  modelM = glm::translate(modelM, glm::vec3(0.1f, 0.0f, 0.0f)); 
	//  modelM =  translate(modelM, .1,0,0);
	if (key == 'l') 
	  modelM = glm::translate(modelM, glm::vec3(-0.1f, 0.0f, 0.0f)); 
	//modelM =  translate(modelM, -.1,0,0);
	if (key == 'f') 
	  modelM = glm::translate(modelM, glm::vec3(0.0f, 0.1f, 0.0f)); 
	//modelM =  translate(modelM, 0,.1,0);
	if (key == 'b') 
	  modelM = glm::translate(modelM, glm::vec3(0.0f, -0.1f, 0.0f)); 
	//modelM =  translate(modelM, 0,-.1,0);
	if (key == 'c') {
	  modelM =  glm::mat4(1.0f);
	  angle1 = angle2 = angle3 = angle4 = angle0 = 0; 
	}

	if (key == '1') angle1 += 1; 
    if (key == '2') angle2 += 1;
    if (key == '3') angle3 += 1;
    if (key == '4') angle4 += 1;
    if (key == '0') angle0 += 1;

	
	if (key == 'p')  {
	  glm::mat4 pm = glm::scale(modelM, glm::vec3(0.5f, 0.5f, 1.0f)); 
	  mat_list.push_back(pm); 
	} 

	glutPostRedisplay(); 
}

int main(int argc, char** argv) 
{ 

  glutInit(&argc, argv); 
  glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH); 
  glutInitWindowSize(600,600); 

  glutCreateWindow("fixed function pipeline: simple"); 
  glutDisplayFunc(display); 
  glutMouseFunc(mymouse); 
  glutKeyboardFunc(mykey); 

  mat_list.clear(); 

#ifdef __APPLE__
#else
  glewInit(); 
#endif


  InitVBO(); 

  glutMainLoop(); 

} 
