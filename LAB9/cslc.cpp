#include <GL/freeglut.h>
#include <iostream>

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

// Window boundaries
const int X_MIN = 50;
const int X_MAX = 400;
const int Y_MIN = 50;
const int Y_MAX = 400;

int computeOutCode(double x, double y) {
    int code = INSIDE;

    if (x < X_MIN)      // to the left of rectangle
        code |= LEFT;
    else if (x > X_MAX) // to the right of rectangle
        code |= RIGHT;
    if (y < Y_MIN)      // below the rectangle
        code |= BOTTOM;
    else if (y > Y_MAX) // above the rectangle
        code |= TOP;

    return code;
}

void cohenSutherlandClip(double x0, double y0, double x1, double y1) {
    int outcode0 = computeOutCode(x0, y0);
    int outcode1 = computeOutCode(x1, y1);
    bool accept = false;

    while (true) {
        if (!(outcode0 | outcode1)) { // Bitwise OR is 0. Trivially accept and exit loop
            accept = true;
            break;
        } else if (outcode0 & outcode1) { // Bitwise AND is not 0. Trivially reject and exit loop
            break;
        } else {
            // At least one endpoint is outside the clipping window. Move it inside
            double x, y;

            // Pick one of the endpoints that is outside the clip window
            int outcodeOut = outcode0 ? outcode0 : outcode1;

            // Find intersection point
            if (outcodeOut & TOP) {          // point is above the clip rectangle
                x = x0 + (x1 - x0) * (Y_MAX - y0) / (y1 - y0);
                y = Y_MAX;
            } else if (outcodeOut & BOTTOM) { // point is below the clip rectangle
                x = x0 + (x1 - x0) * (Y_MIN - y0) / (y1 - y0);
                y = Y_MIN;
            } else if (outcodeOut & RIGHT) {  // point is to the right of clip rectangle
                y = y0 + (y1 - y0) * (X_MAX - x0) / (x1 - x0);
                x = X_MAX;
            } else {                           // point is to the left of clip rectangle
                y = y0 + (y1 - y0) * (X_MIN - x0) / (x1 - x0);
                x = X_MIN;
            }

            // Update the endpoint which is outside the clip window
            if (outcodeOut == outcode0) {
                x0 = x;
                y0 = y;
                outcode0 = computeOutCode(x0, y0);
            } else {
                x1 = x;
                y1 = y;
                outcode1 = computeOutCode(x1, y1);
            }
        }
    }

    if (accept) {
        // Draw the clipped line
        glColor3f(1.0, 0.0, 0.0); // red color
        glBegin(GL_LINES);
        glVertex2d(x0, y0);
        glVertex2d(x1, y1);
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); // black color

    // Draw the clipping rectangle
    glBegin(GL_LINE_LOOP);
    glVertex2i(X_MIN, Y_MIN);
    glVertex2i(X_MAX, Y_MIN);
    glVertex2i(X_MAX, Y_MAX);
    glVertex2i(X_MIN, Y_MAX);
    glEnd();

    // Coordinates of the line
    double x0 = 60, y0 = 20, x1 = 80, y1 = 420;

    // Draw the original line
    glColor3f(0.0, 0.0, 1.0); // blue color
    glBegin(GL_LINES);
    glVertex2d(x0, y0);
    glVertex2d(x1, y1);
    glEnd();

    // Clip the line
    cohenSutherlandClip(x0, y0, x1, y1);

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // white background
    gluOrtho2D(0, 500, 0, 500); // 2D orthographic viewing region
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cohen-Sutherland Line Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

