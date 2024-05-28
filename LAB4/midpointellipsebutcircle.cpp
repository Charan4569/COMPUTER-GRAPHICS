#include <GL/freeglut.h>
#include <iostream>

// Window dimensions
#define WIDTH 800
#define HEIGHT 600

// Midpoint ellipse drawing algorithm
void drawEllipse(int xc, int yc, int rx, int ry) {
    int x = 0;
    int y = ry;
    int px = 0;
    int py = 2 * rx * rx * y;

    // Region 1
    int p = ry * ry - rx * rx * ry + rx * rx / 4;
    while (px < py) {
        x++;
        px += 2 * ry * ry;
        if (p < 0) {
            p += ry * ry + px;
        } else {
            y--;
            py -= 2 * rx * rx;
            p += ry * ry + px - py;
        }
        // Plot points for one octant
        glBegin(GL_POINTS);
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glEnd();
    }

    // Region 2
    p = ry * ry * (x + 0.5) * (x + 0.5) + rx * rx * (y - 1) * (y - 1) - rx * rx * ry * ry;
    while (y > 0) {
        y--;
        py -= 2 * rx * rx;
        if (p > 0) {
            p += rx * rx - py;
        } else {
            x++;
            px += 2 * ry * ry;
            p += rx * rx - py + px;
        }
        // Plot points for one octant
        glBegin(GL_POINTS);
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glEnd();
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); // Set color to black

    // Draw ellipse centered at (400, 300) with radii 200 and 150
    drawEllipse(400, 300, 200, 200);
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
    glutCreateWindow("Midpoint Ellipse Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

