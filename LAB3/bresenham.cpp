#include <GL/freeglut.h>
#include <cmath>

// Window dimensions
#define WIDTH 800
#define HEIGHT 600

// Draw point
void drawPoint(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Bresenham's circle drawing algorithm
void drawCircle(int xc, int yc, int radius) {
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (x <= y) {
        drawPoint(xc + x, yc + y);
        drawPoint(xc + x, yc - y);
        drawPoint(xc - x, yc + y);
        drawPoint(xc - x, yc - y);
        drawPoint(xc + y, yc + x);
        drawPoint(xc + y, yc - x);
        drawPoint(xc - y, yc + x);
        drawPoint(xc - y, yc - x);

        x++;

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            y--;
            d = d + 4 * (x - y) + 10;
        }
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); // Set color to black

    // Draw circle centered at (400, 300) with radius 150
    drawCircle(400, 300, 150);

    glFlush();
}

// Initialize OpenGL
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set clear color to white
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Bresenham's Circle Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

