#include<GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
// Main.cpp
#define UNIT 960
#define ESC 27
#define SPACE 32
#define f 102
#define PI 3.14159

#define w 119
#define a 97
#define s 115
#define d 100

int w_width = 1920;
int w_height = 1080;
double aspectRatio = (double) w_width / (double) w_height;

int frame = 0;		// Default: 0
int window3D = 0;	// if 0 then Ortho else 1 then Perspective

// animate_textZoom.h
double scale = 0.1;
double speed = 1;


// animate_walk.h
double angle = 0;
double angle1 = 0;
int direction = 1;		// 1 : forward | 0 : backward
double moveY = 0.5;
double moveX = 0;

// Passer by
double moveX1 = UNIT * 2;
double angle2 = 0;

// Ambulance
double moveX_Amb = 0;

int flag_fall = 0;

// Character S
double moveX_charS = 0;
double angle_charS = 0;
int flag_fallS = 0;
double anglefall_charS = 0;

// Colors
double red = 0;
double green = 0;
double blue = 0;

void myInit();
void myReshape(int width, int height);
void myDisplay();
void myKeyboard(unsigned char key, int x, int y); 
void timer(int);
void control();

bool animate_ambulance()
{

	moveX_Amb += speed * 7;

	return true;
}

bool animate_textZoom()
{
	if (scale > 1)
	{
		scale = 0.1;
		return false;
	}
	scale += speed;

	return true;
}

void drawText(char *text)
{
	char *letter;

	for (letter = text; *letter != '\0'; letter++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *letter);
	}
}


void square(float x)
{
	glColor3d(0.8, 0, 0);

	glBegin(GL_POLYGON);
	glVertex3f(1 * x, 1 * x, 0);
	glVertex3f(-1 * x, x, 0);
	glVertex3f(-1 * x, -1 * x, 0);
	glVertex3f(x, -1 * x, 0);
	glEnd();
}

void square0()
{
	glColor3d(0.8, 0.0, 0.0);

	glBegin(GL_POLYGON);
	glVertex3f(1, 1, 0);
	glVertex3f(-1, 1, 0);
	glVertex3f(-1, -1, 0);
	glVertex3f(1, -1, 0);
	glEnd();
}

void circleD(double radius, double depth)
{
	glBegin(GL_POLYGON);
	for (double theta = 0; theta < 2 * PI; theta += 0.1)
	{
		glVertex3d(radius * cos(theta), radius * sin(theta), depth);
	}
	glEnd();
}

void rectangleD(double x1, double y1, double x2, double y2, double z)
{
	glBegin(GL_POLYGON);
	glVertex3d(x1, y1, z);
	glVertex3d(x2, y1, z);
	glVertex3d(x2, y2, z);
	glVertex3d(x1, y2, z);
	glEnd();
}

void ambulance()
{
	char stringO_1[] = "AMBULANCE";

	// Display Text
	glPushMatrix();
	glTranslatef(-90, -100, 3);
	glScaled(0.5, 0.5, 0);
	glColor3f(1, 0, 0);
	drawText(stringO_1);
	glPopMatrix();

	// Ambulance Body
	glColor3d(1, 1, 1);
	rectangleD(-350, -200, 350, 200, 2);
	
	// Ambulance Engine
	glBegin(GL_POLYGON);
	glColor3d(1, 1, 1);
	glVertex3d(355, -200, 2);
	glVertex3d(650, -200, 2);
	glVertex3d(650, -65, 2);
	glVertex3d(635, -50, 2);
	glVertex3d(550, -50, 2);
	glVertex3d(500, 100, 2);
	glVertex3d(355, 100, 2);
	glEnd();
	

	// Back Tire
	glPushMatrix();
	glTranslated(-150, -210, 0);
	glColor3d(0, 0, 0);		// Tire
	circleD(75, 3);
	glColor3d(0.8, 0, 0);	// Rim
	circleD(50, 4);
	glPopMatrix();

	//Front Tire
	glPushMatrix();
	glTranslated(500, -210, 0);
	glColor3d(0, 0, 0);		// Tire
	circleD(75, 3);
	glColor3d(0.8, 0, 0);	// Rim
	circleD(50, 4);
	glPopMatrix();

	// Window Front
	glBegin(GL_POLYGON);
	glVertex3d(375, -50, 3);
	glVertex3d(520, -50, 3);
	glVertex3d(480, 75, 3);
	glVertex3d(375, 75, 3);
	glEnd();
	// glBegin(GL_POLYGON);                // start drawing a polygon
  	// glColor3d(1.0f,0.0f,0.0f);            // Set The Color To Red
  	// glVertex3d(-1.0f, 1.0f, 0.0f);        // Top left
  	// glVertex3d(0.4f, 1.0f, 0.0f);
	
  	// glVertex3d(1.0f, 0.4f, 0.0f);
  
  	// glColor3d(0.0f,1.0f,0.0f);            // Set The Color To Green
  	// glVertex3d( 1.0f,0.0f, 0.0f);        // Bottom Right
  	// glColor3d(0.0f,0.0f,1.0f);            // Set The Color To Blue
  	// glVertex3d(-1.0f,0.0f, 0.0f);// Bottom Left    

  //glVertex3f();
  glEnd(); 
}


void leaf(double x, double z)
{
	glBegin(GL_POLYGON);
	glVertex3d(-x, -x / 3, z);
	glVertex3d(x, -x / 3, z);
	glVertex3d(0, x * 0.65, z);
	glEnd();
}

void tree(double h, double z)
{
	green = 1;

	glPushMatrix();
	glTranslated(0, h * 170, 0);
	glPushMatrix();
	glColor3d(0.2, green, 0.2);
	glTranslated(0, -h * 120 / h, 0);
		leaf(400, z);
		glPopMatrix();

		green -= 0.1;
	glPopMatrix();

	glColor3d(0.3, 0.1, 0.1);
	rectangleD(-40, -100, 40, 100, z);

}

// Welcome screen
void frame0() {

	char string0_1[] = "Electric car";
	char string0_2[] = "Animated AD.";
	char string0_3[] = "Press 'Spacebar' to Play...";


	// Display "GO Smart Watch"
	glPushMatrix();
	glTranslatef(-500, 400, 0);
	glColor3f(1, 0, 0);
	drawText(string0_1);
	glPopMatrix();

	// Display  "Animated AD."
	glPushMatrix();
	glTranslatef(100, 250, 0);
	glScaled(0.7, 0.7, 0);
	drawText(string0_2);
	glPopMatrix();

	// Display "Press Spacebar to Play...".
	glPushMatrix();
	glTranslatef(500, -500, 0);
	glScaled(0.4, 0.4, 0);
	glColor3f(1, 1, 0);
	drawText(string0_3);
	glPopMatrix();
	
	glFlush();
}

void frame1() {
	
	glClearColor(0, 0, 0, 0);
		// Tree 1
	glPushMatrix();
	glTranslated(UNIT / 2, -UNIT / 2.5, 0);
	tree(7, -9);
	glPopMatrix();

	// Tree 2
	glPushMatrix();
	glTranslated(UNIT * aspectRatio, -UNIT / 2.5, 0);
	tree(3, -9);
	glPopMatrix();

	// Tree 3
	glPushMatrix();
	glTranslated(-UNIT, -UNIT / 2.5, 0);
	tree(4, -9);
	glPopMatrix();

	
	// Road
	glBegin(GL_POLYGON);
	glColor3d(0, 0, 0);
	glVertex3d(-UNIT * aspectRatio, -UNIT, -9);
	glVertex3d(UNIT * aspectRatio, -UNIT, -9);
	glVertex3d(UNIT * aspectRatio, -UNIT / 2, -9);
	glVertex3d(-UNIT * aspectRatio, -UNIT / 2, -9);
	glEnd();

	// Sky and bushes
	glBegin(GL_POLYGON);
	glColor3d(0.1, 0.6, 0.1);
	glVertex3d(-UNIT * aspectRatio, -UNIT / 2, -9);
	glVertex3d(UNIT * aspectRatio, -UNIT / 2, -9);
	glColor3d(0.1, 0.1, 0.7);
	glVertex3d(UNIT * aspectRatio, UNIT, -9);
	glVertex3d(-UNIT * aspectRatio, UNIT, -9);
	glEnd();
	glFlush();

	glPushMatrix();
	glTranslated(moveX_Amb, 0, 0);
	glTranslated(-UNIT * aspectRatio - 400, -400, 0);
	ambulance();
	glPopMatrix();

	glFlush();
	
	// char string0_1[] = "Electric car 2";
	// char string0_2[] = "Animated AD.";
	// char string0_3[] = "Press 'Spacebar' to Play...";


	// Display "GO Smart Watch"
	// glPushMatrix();
	// glTranslatef(-500, 400, 0);
	// glColor3f(1, 0, 0);
	// drawText(string0_1);
	// glPopMatrix();

	// // Display  "Animated AD."
	// glPushMatrix();
	// glTranslatef(100, 250, 0);
	// glScaled(0.7, 0.7, 0);
	// drawText(string0_2);
	// glPopMatrix();

	// // Display "Press Spacebar to Play...".
	// glPushMatrix();
	// glTranslatef(500, -500, 0);
	// glScaled(0.4, 0.4, 0);
	// glColor3f(1, 1, 0);
	// drawText(string0_3);
	// glPopMatrix();
	
	// glFlush();
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition(0, 0);	// Window location
	glutInitWindowSize(w_width, w_height);
	glutCreateWindow("Electric car");

	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(myKeyboard);

	glutTimerFunc(0, timer, 0);

	myInit();

	glutMainLoop();
	return 0;
}

void myInit()
{
	if (!window3D)
	{
		glEnable(GL_DEPTH_TEST);

		glViewport(0, 0, w_width, w_height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-UNIT * aspectRatio, UNIT * aspectRatio, -UNIT, UNIT, -UNIT, UNIT);
		glMatrixMode(GL_MATRIX_MODE);
	}
	else
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
		glClearDepth(1.0f);                   // Set background depth to farthest
		glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
		glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
		glShadeModel(GL_SMOOTH);   // Enable smooth shading
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
	}
	
}

void myReshape(int width, int height)
{
	aspectRatio = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset

	if (!window3D)
	{
		if (width > height)
			glOrtho(-UNIT * aspectRatio, UNIT * aspectRatio, -UNIT, UNIT, -UNIT, UNIT);
		else
			glOrtho(-UNIT, UNIT, -UNIT / aspectRatio, UNIT / aspectRatio, -UNIT, UNIT);
		glMatrixMode(GL_MODELVIEW);
	}
	else
	{
		// Enable perspective projection with fovy, aspect, zNear and zFar
		gluPerspective(45.0f, aspectRatio, 0.1f, 100000);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0, 0, -2000);
	}
	
	// Update the window width and height.
	w_width = width;
	w_height = height;
}

void myKeyboard(unsigned char key, int x, int y)
{
	int speed3d = 5;

	switch ((int)key)
	{
	case ESC: exit(0);		break;
	case SPACE: frame++;	break;

	case f: flag_fall++;	break;	// for Debug

	// 3D camera moment

	case d:		// Y axis +
		glRotated(speed3d, 0, 1, 0);
		break;
	case a:		// Y axis -
		glRotated(-speed3d, 0, 1, 0);
		break;

	case w:		// X axis +
		glRotated(speed3d, 1, 0, 0);
		break;
	case s:		// X axis -
		glRotated(-speed3d, 1, 0, 0);
		break;

	}
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);

	switch (frame)
	{
	case 0:	frame0();	break;
	case 1:	frame1();	break;

	default:	
//		frameEnd();
		break;
	}

	glutSwapBuffers();
}

void timer(int)		
{	// Function runs throughtout the code every 1/60 th of a min (FPS = 60)
	control();	// Check which frame to animate
	glutPostRedisplay();	// Trigger myDisplay()
	glutTimerFunc(1000 / 60, timer, 0);		// 60 FPS animation
}

void control()
{
	// Iterate through the frames and animate them
	switch (frame)
	{
	case 0:		// Frame 0
		break;

	case 1:		// Frame 1
		if (!animate_ambulance())
		{
			speed = 0.006;
			frame++;
		}
		
		break;

	// case 2:		// Frame 2
	// 	if (!animate_textZoom())
	// 	{
	// 		speed = 0.01;
	// 		frame++;
	// 	}
	// 	break;

	// case 3:		// Frame 3
	// 	if (!animate_textZoom())
	// 	{
	// 		speed = 2;
	// 		frame++;
	// 	}
	// 	break;

	// case 4:		// Frame 4
	// 	switch (flag_fall)
	// 	{
	// 	case 0: animate_walk();		break;
	// 	case 1:	animate_fall();		break;
	// 	case 2:
	// 		if (!animate_walk1())
	// 		{
	// 			speed = 0.01;
	// 			scale = 0.1;
	// 			frame++;
	// 		}
	// 		break;
	// 	}
	// 	break;

	// case 5:		// Frame 5
	// 	if (!animate_textZoom())
	// 	{
	// 		speed = 1;
	// 		frame++;
	// 	}
	// 	break;

	// case 6:		// Frame 6
	// 	if (!animate_ambulance())
	// 	{
	// 		speed = 0.006;
	// 		frame++;
	// 	}
	// 	break;

	// case 7:		// Frame 7
	// 	if (!animate_textZoom())
	// 	{
	// 		speed = 0.006;
	// 		frame++;
	// 	}
	// 	break;

	// case 8:
	// 	if (!animate_textZoom())
	// 	{
	// 		speed = 0.006;
	// 		frame++;
	// 	}
	// 	break;

	// case 9:
	// 	if (!animate_textZoom())
	// 	{
	// 		speed = 0.006;
	// 		frame++;
	// 	}
	// 	break;
	
	// case 10:
	// 	if (!animate_textZoom())
	// 	{
	// 		speed = 2;
	// 		frame++;
	// 	}
	// 	break;

	// case 11:
	// 	switch (flag_fallS)
	// 	{
	// 	case 0: animate_walkCharS();		break;
	// 	case 1:	
	// 		if (!animate_fallCharS())
	// 		{
	// 			speed = 0.006;
	// 			scale = 0.1;
	// 			frame++;
	// 		}
	// 		break;
	// 	}
	// 	break;

	// case 12:
	// 	if (!animate_textZoom())
	// 	{
	// 		speed = 0.006;
	// 		frame++;
	// 	}
	// 	break;

	// case 13:
	// 	if (!animate_textZoom())
	// 	{
	// 		speed = 0.006;
	// 		frame++;
	// 	}
	// 	break;
	
	// case 14:
	// 	if (!animate_textZoom())
	// 	{
	// 		speed = 2;
	// 		moveX_Amb = 0;
	// 		frame++;
	// 	}
	// 	break;
	
	// case 15:
	// 	if (!animate_ambulance())
	// 	{
	// 		speed = 0.006;
	// 		frame++;
	// 	}
	// 	break;

	// case 16:
	// 	if (!animate_textZoom())
	// 	{
	// 		speed = 0.006;
	// 		window3D = 1;
	// 	}
	// 	break;

	// case 17:
	// 	break;

	// case 18: 
	// 	window3D = 0;
	// 	break;

	default:
		break;
	}
}


