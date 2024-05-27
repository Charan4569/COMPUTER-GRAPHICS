#include <GL/glut.h>
#include <iostream>
#include <cmath>
void drawLineDDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = std::max(abs(dx), abs(dy));

    float xIncrement = static_cast<float>(dx) / steps;
    float yIncrement = static_cast<float>(dy) / steps;

    float x = x1;
    float y = y1;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // Set line color to white

    glBegin(GL_POINTS);

    for (int i = 0; i <= steps; ++i) {
        glVertex2i(round(x), round(y));
        x += xIncrement;
        y += yIncrement;
    }

    glEnd();
    glFlush();
}

void display() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glClear(GL_COLOR_BUFFER_BIT);

    drawLineDDA(50, 50, 200, 150); // Example line coordinates

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("DDA Line Drawing Algorithm");
    glutInitWindowSize(400, 300); // Set window size
    glutDisplayFunc(display);

    gluOrtho2D(0, 400, 0, 300); // Set orthographic viewing region

    glutMainLoop();

    return 0;
}

