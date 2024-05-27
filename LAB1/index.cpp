// write a open gl program to draw circle ellipse , lines ( parallel and perpendicular ) using freegult library

#include <GL/freeglut.h>
#include <cmath>

const int windowWidth = 800;
const int windowHeight = 600;

void drawCircle(float radius, int segments) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        float theta = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(segments);
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawEllipse(float a, float b, int segments) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        float theta = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(segments);
        float x = a * cos(theta);
        float y = b * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // Set color to white

    // Draw a circle
    glColor3f(1.0, 0.0, 0.0); // Set color to red
    drawCircle(50.0, 100);

    // Draw an ellipse
    glColor3f(0.0, 1.0, 0.0); // Set color to green
    drawEllipse(80.0, 40.0, 100);

    // Draw a parallel line
    glColor3f(0.0, 0.0, 1.0); // Set color to blue
    drawLine(-60.0, -60.0, 60.0, -60.0);
    drawLine(-70.0, -80.0, 70.0, -80.0);

    // Draw a perpendicular line
    glColor3f(1.0, 1.0, 0.0); // Set color to yellow
    drawLine(-70.0, -70.0, -70.0, 70.0);
    drawLine(-70.0, -70.0, 70.0, -70.0);

    glFlush();
}

void initialize() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    gluOrtho2D(-windowWidth / 2, windowWidth / 2, -windowHeight / 2, windowHeight / 2);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Graphics Program");

    initialize();
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}

