#include <GL/freeglut.h>
#include <iostream>
#include <cmath>

int width = 800, height = 600;

int circleX = 400, circleY = 300;
int circleRadius = 100;

int polygonVertices[][2] = {
    {200, 100},
    {300, 200},
    {400, 100}
};

GLfloat polygonColor[] = {1.0, 0.0, 0.0};

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); 
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    for (float angle = 0; angle <= 360; angle += 1.0) {
        float x = circleX + circleRadius * cos(angle * 3.14159265 / 180);
        float y = circleY + circleRadius * sin(angle * 3.14159265 / 180);
        glVertex2f(x, y);
    }
    glEnd();

    glColor3fv(polygonColor);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 3; ++i) {
        glVertex2iv(polygonVertices[i]);
    }
    glEnd();

    glFlush();
}

void reshape(int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("OpenGL Circle and Polygon");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
