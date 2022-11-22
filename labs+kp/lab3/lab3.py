import time
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import sys
import math

STEP_TIME = 2


def init():
    global ambient_
    global lightpos_
    global increase
    global color_white
    global color_darkRed
    global color_black

    ambient_ = (1.0, 1.0, 1.0, 1)
    color_white = (0.0, 0.0, 0.0, 0.0)
    lightpos_ = (1.0, 1.0, 1.0)
    color_darkRed = (0.1, 0.0, 0.0, 0.0)
    color_black = (0.0, 0.0, 0.0, 0.0)

    glClearColor(0.2, 0.3, 0.3, 1.0)
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0)
    glRotatef(-90, 1.0, 0.0, 0.0)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_)
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos_)


def drawShape(R, r, h, num):
    num = float(num)
    c = []

    for i in range(int(num) + 1):
        angle = 2 * math.pi * (i / num)
        x = R * math.cos(angle)
        y = R * math.sin(angle)
        x2 = r * math.cos(angle)
        y2 = r * math.sin(angle)
        pt = ((x), (y), (x2), (y2))
        c.append(pt)

    glBegin(GL_TRIANGLE_FAN)
    glVertex(0, 0, h / 2.0)
    for (x, y, x2, y2) in c:
        z = h / 2.0
        glVertex(x2, y2, z)
    glEnd()
    glBegin(GL_TRIANGLE_FAN)
    for (x, y, x2, y2) in c:
        z = -h / 2.0
        glVertex(x, y, z)
    glEnd()
    glBegin(GL_TRIANGLE_STRIP)
    for (x, y, x2, y2) in c:
        for i in range(int(num)):
            z = h / 2.0
            glVertex(x, y, -z)
            glVertex(x2, y2, z)
    glEnd()


def timer(value):
    glutPostRedisplay()
    glutTimerFunc(150, timer, 0)


def draw():
    global lightpos_
    global color_white
    global increase
    global color_darkRed

    time.sleep(STEP_TIME)
    glClear(GL_COLOR_BUFFER_BIT)

    glPushMatrix()

    glLightfv(GL_LIGHT0, GL_POSITION, lightpos_)
    lpos = [0.8, 0.8, 0.8, 1.0]
    lc = [0.8, 1.0, 0.8, 1.0]
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_white)
    glLightfv(GL_LIGHT0, GL_POSITION, lpos)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lc)
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1)
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.01)
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_white)
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, color_white)
    glEnable(GL_LIGHT0)
    glTranslatef(-0.2, 0.0, -0.1)
    glRotatef(20, 1.0, 1.0, 1.0)
    color_green = (0.0, 0.1, 0.0, 0.0)

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, color_black)
    drawShape(0.3 - 0.2 * increase, 0.3 - 0.2 * increase, 0.2, 10)  # 6
    drawShape(0.3 - 0.2 * increase, 0.3 - 0.2 * increase, 0.4, 10)  # 5
    glTranslatef(0.0, 0.0, 0.2)
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_black)
    drawShape(0.3 - 0.2 * increase, 0.3 - 0.2 * increase, 0.2, 10)  # 4
    glTranslatef(0.0, 0.0, 0.2)
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_green)
    drawShape(0.3 + 0.2 * increase, 0.3 - 0.28 * increase, 0.2, 10)  # 3
    glTranslatef(0.0, 0.0, 0.2)
    color_blue = (0.0, 0.0, 0.1, 0.0)
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_blue)
    drawShape(0.25 + 0.15 * increase, 0.3 - 0.28 * increase, 0.2, 10)  # 2
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_darkRed)
    glTranslatef(0.0, 0.0, 0.2)
    drawShape(0.2 + 0.1 * increase, 0.25 - 0.23 * increase, 0.2, 20)  # 1

    glPopMatrix()

    if increase < 1: increase += 1 / 10

    glFlush()
    glutSwapBuffers()


# Run the script
if __name__ == '__main__':
    STEP_TIME = 0.001
    increase = 0

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB)
    glutInitWindowSize(800, 800)
    glutInitWindowPosition(50, 50)
    glutInit(sys.argv)

    glutCreateWindow(b"** Binocular -> Christmas Tree **")
    glutDisplayFunc(draw)
    glutTimerFunc(150, timer, 0)

    init()
    glutMainLoop()
