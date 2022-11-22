#pragma warning(disable : 4996)
#define _USE_MATH_DEFINES
#include <cmath>
#include <list>
#include <array>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "common.hpp"

glm::vec3 cameraPosition(0, 1, 15);
glm::vec3 cameraDirection(0, 0, 0);
glm::vec3 cameraUp(0, 1, 0);
float pitch = 0.0f;
float roll = 0.0f;
float yaw = 0.0f;

float left = -1, right = 1, bottom = -1, top = 1, zNear = 0.1, zFar = 100.0;

int windowWidth = 1280;
int windowHeight = 720;

bool keyboardState[1024];

GLfloat light_position[] = { 5.0, 5.0, 0.0, 0.0 };
GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };

#define X .525731112119133606
#define Z .850650808352039932

GLfloat vdata[12][3] = {
	{ -X, 0.0, Z }, { X, 0.0, Z }, { -X, 0.0, -Z }, { X, 0.0, -Z },
	{ 0.0, Z, X }, { 0.0, Z, -X }, { 0.0, -Z, X }, { 0.0, -Z, -X },
	{ Z, X, 0.0 }, { -Z, X, 0.0 }, { Z, -X, 0.0 }, { -Z, -X, 0.0 }
};

static GLuint tindices[20][3] = {
	{1, 4, 0}, {4, 9, 0}, {4, 5, 9}, {8, 5, 4}, {1, 8, 4},
	{1, 10, 8}, {10, 3, 8}, {8, 3, 5}, {3, 2, 5}, {3, 7, 2},
	{3, 10, 7}, {10, 6, 7}, {6, 11, 7}, {6, 0, 11}, {6, 1, 0},
	{10, 1, 6}, {11, 0, 9}, {2, 11, 9}, {5, 2, 9}, {11, 2, 7}
};

GLfloat color[][3] = {
	{0, 0, 0},
	{0, 0, 1},
	{0, 1, 0},
	{0, 1, 1},
	{1, 0, 0},
	{1, 0, 1},
	{1, 1, 0},
	{1, 1, 1},
	{0.5, 0, 0},
	{0, 0.5, 0},
	{0, 0, 0.5},
	{0, 0.5, 0.5},
	{0.5, 0.5, 0},
	{0.5, 0, 0.5},
	{0.5, 0.5, 0.5},
	{1, 1, 0.5},
	{1, 0.5, 1},
	{0.5, 1, 1},
	{0, 0.5, 1},
	{0.5, 1, 0},
};

void mouse(int x, int y)
{
	yaw += 35 * (x - float(windowWidth) / 2.0) / windowWidth;
	yaw = glm::mod(yaw + 180.0f, 360.0f) - 180.0f;

	pitch += -35 * (y - float(windowHeight) / 2.0) / windowHeight;
	pitch = glm::clamp(pitch, -89.0f, 89.0f);

	glutWarpPointer(windowWidth / 2.0, windowHeight / 2.0);
	glutPostRedisplay();
}

void keyboardDown(unsigned char key, int x, int y)
{
	keyboardState[key] = true;
}
void keyboardDownSpecial(int key, int x, int y)
{
	keyboardState[key] = true;
}
void keyboardUp(unsigned char key, int x, int y)
{
	keyboardState[key] = false;
}
void keyboardUpSpecial(int key, int x, int y)
{
	keyboardState[key] = false;
}

float d = 0;
/*float j = 1.00585;*/ 
//float j = 0.125;
float j = 0.0625;

void move()
{
	if (keyboardState['W']) cameraPosition += 0.005f * cameraDirection;
	if (keyboardState['S']) cameraPosition -= 0.005f * cameraDirection;
	if (keyboardState['A']) cameraPosition -= 0.005f * glm::normalize(glm::cross(cameraDirection, cameraUp));
	if (keyboardState['D']) cameraPosition += 0.005f * glm::normalize(glm::cross(cameraDirection, cameraUp));
	if (keyboardState[GLUT_KEY_CTRL_L]) cameraPosition.y -= 0.05;
	if (keyboardState[' ']) cameraPosition.y += 0.05;
	if (keyboardState['C']) cameraPosition.y -= 0.05;
	if (keyboardState['Q']) exit(0);
	if (keyboardState['1']) {
		d = 0;
		/*j = 1.00585;*/
		j = 0.0625;

		vdata[0][0] = -X; vdata[0][1] = 0; vdata[0][2] = Z;
		vdata[1][0] = X; vdata[1][1] = 0; vdata[1][2] = Z;
		vdata[2][0] = -X; vdata[2][1] = 0; vdata[2][2] = -Z;
		vdata[3][0] = X; vdata[3][1] = 0; vdata[3][2] = -Z;
		vdata[4][0] = 0; vdata[4][1] = Z; vdata[4][2] = X;
		vdata[5][0] = 0; vdata[5][1] = Z; vdata[5][2] = -X;
		vdata[6][0] = 0; vdata[6][1] = -Z; vdata[6][2] = X;
		vdata[7][0] = 0; vdata[7][1] = -Z; vdata[7][2] = -X;
		vdata[8][0] = Z; vdata[8][1] = X; vdata[8][2] = 0;
		vdata[9][0] = -Z; vdata[9][1] = X; vdata[9][2] = 0;
		vdata[10][0] = Z; vdata[10][1] = -X; vdata[10][2] = 0;
		vdata[11][0] = -Z; vdata[11][1] = -X; vdata[11][2] = 0;
	}
	glutPostRedisplay();
}

void display()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-windowWidth * 0.1 / windowHeight, windowWidth * 0.1 / windowHeight, -0.1, 0.1, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	move();

	cameraDirection.x = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraDirection.y = sin(glm::radians(pitch));
	cameraDirection.z = -cos(glm::radians(pitch)) * cos(glm::radians(yaw));

	gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z, (cameraPosition + cameraDirection).x, (cameraPosition + cameraDirection).y, (cameraPosition + cameraDirection).z, 0.0, 1.0, 0.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glColor3d(0.2, 0.3, 0.3);
	glutSolidCylinder(50, 50, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glColor3d(0.5, 0.5, 0.5);
	glTranslatef(0, 2, 0);
	glutSolidSphere(2, 50, 50);
	glPopMatrix();

	d += j;
	glRotatef(-d, 0, 1, 0);
	glTranslatef(0, 0, 10);
	float minY = FLT_MAX;
	float minX = FLT_MAX;
	for (int i = 0; i < 12; ++i) {
		common::rotation(vdata[i], j * 5, 0, 0, 1);		
		if (vdata[i][1] < minY) {
			minY = vdata[i][1];
		}
		if (vdata[i][0] < minX) {
			minX = vdata[i][0];
		}
	}
	for (int i = 0; i < 12; ++i) {
		vdata[i][1] -= minY;
	}
	for (int i = 0; i < 12; ++i) {
		vdata[i][0] -= minX;
	}
	if (j > 0) {
		//j -= 0.000005;
		j -= 0.0000005;
	}

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 20; i++)
	{
		glColor3fv(color[i]);
		glVertex3fv(&vdata[tindices[i][0]][0]);
		glVertex3fv(&vdata[tindices[i][1]][0]);
		glVertex3fv(&vdata[tindices[i][2]][0]);
	}
	glEnd();

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("KP");

	glewInit();

	glClearColor(0.1, 0.1, 0.3, 1.0);

	glutPassiveMotionFunc(mouse);

	glutKeyboardFunc(keyboardDown);
	glutSpecialFunc(keyboardDownSpecial);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialUpFunc(keyboardUpSpecial);

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}
