#include <GL/freeglut.h>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

// program to flood fill algorithm

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

void floodFill(int x, int y, float oldColor[], float newColor[]) {
    float color[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
    if (color[0] == oldColor[0] && color[1] == oldColor[1] && color[2] == oldColor[2]) {
        glColor3f(newColor[0], newColor[1], newColor[2]);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();
        floodFill(x + 1, y, oldColor, newColor);
        floodFill(x - 1, y, oldColor, newColor);
        floodFill(x, y + 1, oldColor, newColor);
        floodFill(x, y - 1, oldColor, newColor);
    }
}

void floodFillInVector(int x,int y,vector<vector<int>> &polygon) {
    if(polygon[x][y] == 0) {
        polygon[x][y] = 1;
        floodFillInVector(x+1,y,polygon);
        floodFillInVector(x-1,y,polygon);
        floodFillInVector(x,y-1,polygon);
        floodFillInVector(x,y+1,polygon);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2i(150, 150);
    glVertex2i(150, 200);
    glVertex2i(200, 200);
    glVertex2i(200, 150);
    glEnd();
    glFlush();
}

void mouse(int btn, int state, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float oldColor[] = {1.0, 0.0, 0.0};
        float newColor[] = {0.0, 1.0, 0.0};
        floodFill(x, 500 - y, oldColor, newColor);
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Flood Fill Algorithm");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
