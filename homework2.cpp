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

void backgroundGradient() {
	glBegin(GL_QUADS);
	glColor3f(0.4, 0.5, 0.9);
	glVertex2f(-400, 300);
	glVertex2f(400, 300);
	glColor3f(1.0, 0.4, 0.1);
	glVertex2f(400, -100);
	glVertex2f(-400, -100);
	glEnd();
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

void decorate() {
	// Put up some awesome flags
	drawZuerichFlag(-380, 180, 100);
	drawSwissFlag(280, 180, 100);
	// And a title explaining what the picture is of
	char text[] = "ZUERICH SWITZERLAND";
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2i(-100, 250);
	for (int i = 0; i < strlen(text); i++)
		// The font Helvetica is from Switzerland, a.k.a. Confoederatio Helvetica
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
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

void mountainRange(void) {
	// Furthest away
	drawMountain(120, 160, 400, 270, 0.5);
	drawMountain(-320, 160, 380, 300, 0.52);
	// A little closer
	drawMountain(300, 130, 370, 300, 0.55);
	drawMountain(-100, 140, 380, 300, 0.6);
	// Pretty close now
	drawMountain(-220, 120, 350, 300, 0.63);
	drawMountain(380, 100, 330, 300, 0.66);
	// Closest
	drawMountain(200, 120, 320, 300, 0.7);
	drawMountain(-20, 100, 340, 300, 0.75);
}

void drawLake() {
	glBegin(GL_QUADS);
	glColor3f(0.1, 0.6, 1.0);
	glVertex2f(-400, -100);
	glVertex2f(400, -100);
	glColor3f(0.0, 0.2, 0.5);
	glVertex2f(400, -210);
	glVertex2f(-400, -210);
	glEnd();
}

void drawBuilding(int left_x, int top_y, int width, int height) {
	glRecti(left_x, top_y, left_x + width, top_y - height);
}

void drawTower(int top_x, int top_y, int width, int height, int tower_height, int spire_height) {
	GLuint tower;

	// Base
	drawBuilding(top_x - width/2, top_y - tower_height, width, height - tower_height);

	// Tower
	glNewList(tower, GL_COMPILE);
	glBegin(GL_POLYGON);
	glVertex2i(top_x - width/2, top_y - tower_height);
	glVertex2i(top_x, top_y);
	glVertex2i(top_x + width/2, top_y - tower_height);
	glEnd();
	glEndList();
	glCallList(tower);

	// Spire
	glBegin(GL_LINES);
	glVertex2i(top_x, top_y);
	glVertex2i(top_x, top_y + spire_height);
	glEnd();
}

void drawDome(int top_x, int top_y, int width, int height, int dome_height, int spire_height) {
	// Base
	drawBuilding(top_x - width/2, top_y - dome_height, width, height - dome_height);

	// Tower
	int center_y = top_y - dome_height;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(top_x, center_y);
	for (int i = 0; i < 360; i++) {
		float radians = i * M_PI / 360;
		glVertex2f(top_x + cos(radians) * width / 2, center_y + sin(radians) * dome_height);
	}
	glEnd();

	// Spire
	glBegin(GL_LINES);
	glVertex2i(top_x, top_y);
	glVertex2i(top_x, top_y + spire_height);
	glEnd();
}

void skyline() {
	// Background
	int baseline = -210;
	glColor3f(0.2, 0.2, 0.2);

	// Background buildings
	drawBuilding(-200, baseline + 50, 30, 50);
	drawBuilding(-155, baseline + 40, 10, 40);
	drawBuilding(-135, baseline + 10, 30, 10);
	drawBuilding(-100, baseline + 20, 40, 20);
	drawBuilding(-45, baseline + 45, 30, 45);
	drawBuilding(30, baseline + 15, 60, 15);
	drawBuilding(120, baseline + 35, 20, 35);
	drawBuilding(140, baseline + 25, 40, 25);
	drawBuilding(190, baseline + 50, 20, 50);
	drawBuilding(200, baseline + 20, 50, 20);

	// Foreground
	glColor3f(0.0, 0.0, 0.0);

	// Baseline
	glRecti(-400, -300, 400, baseline);

	// Higher areas
	drawBuilding(-400, baseline + 60, 140, 60);
	drawBuilding(-260, baseline + 40, 60, 40);
	drawBuilding(240, baseline + 60, 160, 60);

	// Buildings on higher areas
	drawTower(-290, baseline + 190, 60, 190, 60, 20);
	drawTower(-220, baseline + 155, 40, 155, 50, 20);
	drawDome(260, baseline + 165, 40, 165, 30, 15);
	drawDome(320, baseline + 165, 40, 165, 30, 15);

	// Buildings in middle area
	drawBuilding(-180, baseline + 30, 20, 30);
	drawBuilding(-160, baseline + 20, 20, 20);
	drawTower(-130, baseline + 50, 20, 50, 20, 0);
	drawBuilding(-110, baseline + 40, 30, 40);
	drawBuilding(-65, baseline + 25, 40, 25);
	drawBuilding(-10, baseline + 30, 50, 30);
	drawBuilding(70, baseline + 20, 60, 20);
	drawDome(95, baseline + 40, 30, 40, 15, 0);
	drawTower(170, baseline + 80, 20, 80, 30, 10);
	drawBuilding(200, baseline + 40, 30, 40);
}

// Generate the Graphics
void displayFcn(void)
{
	// Clear display window.
	glClear(GL_COLOR_BUFFER_BIT);

	backgroundGradient();
	mountainRange();
	drawLake();
	skyline();
	decorate();

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
