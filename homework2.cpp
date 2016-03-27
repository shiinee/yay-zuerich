#include <cstdlib>
#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GL/glut.h>
#include <SDL.h>

// Global Variable Section
// List all of your global variables, stuctures and other definition here
// Window display size
GLsizei winWidth = 800, winHeight = 600;

// Initialize method
void init(void)
{
	// Get and display your OpenGL version
	const GLubyte *Vstr;
	Vstr = glGetString(GL_VERSION);
	fprintf(stderr, "Your OpenGL version is %s\n", Vstr);

	// White color window
	glClearColor(1.0, 1.0, 1.0, 1.0);
	// Projection on World Coordinates 
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-(GLdouble)winWidth / 2, (GLdouble)winWidth / 2, -(GLdouble)winHeight / 2, (GLdouble)winHeight / 2);
}

void drawSwissFlag(int from_x, int from_y, int size) {
	// Red rectangle
	// NOTE: The Swiss flag is square. So there's only one size measurement.
	glColor3f(1.0, 0.0, 0.0);
	glRecti(from_x, from_y, from_x + size, from_y + size);

	// White plus (intersection of two rectangles)
	int plus_weight = size/5;
	int plus_left = from_x + plus_weight;
	int plus_right = from_x + size - plus_weight;
	int plus_top = from_y + size - plus_weight;
	int plus_bottom = from_y + plus_weight;

	glColor3f(1.0, 1.0, 1.0);
	glRecti(plus_left, plus_bottom + plus_weight, plus_right, plus_top - plus_weight);
	glRecti(plus_left + plus_weight, plus_bottom, plus_right - plus_weight, plus_top);
}

void drawZuerichFlag(int from_x, int from_y, int size) {
	// White rectangle
	// NOTE: The flag of Zuerich city is also square. Squares rock.
	glColor3f(1.0, 1.0, 1.0);
	glRecti(from_x, from_y, from_x + size, from_y + size);

	// Blue triangle
	glColor3f(0.0, 0.0, 1.0);
	GLuint triangle;
	glNewList(triangle, GL_COMPILE);
	glBegin(GL_POLYGON);
	glVertex2i(from_x, from_y);
	glVertex2i(from_x + size, from_y);
	glVertex2i(from_x, from_y + size);
	glEnd();
	glEndList();
	glCallList(triangle);
}

void drawFlagpole(int from_x, int from_y, int width, int height) {
	// Skinny black rectangle
	glColor3f(0.0, 0.0, 0.0);
	glRecti(from_x, from_y, from_x + width, from_y + height);
}

void drawMountain(int peak_x, int peak_y, int width, int height, float lightness) {
	GLuint mountain, peak;

	// Set shade of grey based on lightness
	glColor3f(lightness, lightness, lightness);
	
	// Grey triangle
	glNewList(mountain, GL_COMPILE);
	glBegin(GL_POLYGON);
	glVertex2i(peak_x - width/2, peak_y - height);
	glVertex2i(peak_x, peak_y);
	glVertex2i(peak_x + width/2, peak_y - height);
	glEnd();
	glEndList();
	glCallList(mountain);

	// Snowy peak (white triangle)
	glColor3f(1.0, 1.0, 1.0);
	glNewList(peak, GL_COMPILE);
	glBegin(GL_POLYGON);
	glVertex2i(peak_x - width/6, peak_y - height/3);
	glVertex2i(peak_x, peak_y);
	glVertex2i(peak_x + width/6, peak_y - height/3);
	glEnd();
	glEndList();
	glCallList(peak);
}


// Generate the Graphics
void displayFcn(void)
{
	// Clear display window.
	glClear(GL_COLOR_BUFFER_BIT);

	drawMountain(0, 200, 200, 200, 0.6);

	drawZuerichFlag(-350, 50, 100);
	drawFlagpole(-355, -200, 5, 350);

	drawSwissFlag(250, 50, 100);
	drawFlagpole(350, -200, 5, 350);

	// Execute OpenGL functions
	glFlush();
}
// Windows redraw function
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-(GLdouble)winWidth / 2, (GLdouble)winWidth / 2, -(GLdouble)winHeight / 2, (GLdouble)winHeight / 2);
	glClear(GL_COLOR_BUFFER_BIT);
}
// Main function
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// Set initial Window position
	glutInitWindowPosition(100, 100);
	// Set Window Size
	glutInitWindowSize(winWidth, winHeight);
	// Set Window Title
	glutCreateWindow("Skyler Amador - Homework 2");
	// Initialize
	init();
	// Display function call
	glutDisplayFunc(displayFcn);
	// Window reshape call
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}
