
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>

struct Point {
    double x, y;
};

struct Edge {
    Point p1, p2;
};

struct Vector {
    double x, y;
};

Vector subtract(Point p1, Point p2) {
    return {p1.x - p2.x, p1.y - p2.y};
}

double dotProduct(Vector v1, Vector v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

Point intersection(Point p1, Point p2, double t) {
    Vector vec = subtract(p2, p1);
    return {p1.x + t * vec.x, p1.y + t * vec.y};
}

double cyrusBeckClipping(Point P, Vector D, double t_enter, double t_exit) {
    double t = 0.0;

    if (t_enter < t_exit && t_exit >= 0) {
        Point E = {500, 500}; // Assume a point outside the window
        Vector PE = subtract(E, P);
        double den = dotProduct(D, PE);

        if (den != 0) {
            t = dotProduct(subtract(E, P), D) / den;
            if (t < t_enter || t > t_exit)
                t = -1; // Line is outside the window
        } else {
            t = -1; // Line is parallel to edge
        }
    }

    return t;
}

void cyrusBeckAlgorithm(Point P, Point Q) {
    Vector D = subtract(Q, P);

    // Define the window edges as line segments
    Edge edges[] = {
        {{50, 50}, {400, 50}}, // Top edge
        {{400, 50}, {400, 400}}, // Right edge
        {{400, 400}, {50, 400}}, // Bottom edge
        {{50, 400}, {50, 50}} // Left edge
    };

    double t_enter = 0.0, t_exit = 1.0;

    for (const auto& edge : edges) {
        Vector N = {-(edge.p2.y - edge.p1.y), (edge.p2.x - edge.p1.x)};
        Vector PE = subtract(edge.p1, P);
        double num = dotProduct(N, PE);
        double den = dotProduct(N, D);

        if (den == 0) {
            if (num < 0) {
                return; // Line is parallel and outside the window
            }
        } else {
            double t = num / den;
            if (den < 0) {
                t_enter = fmax(t_enter, t);
            } else {
                t_exit = fmin(t_exit, t);
            }
        }
    }

    if (t_enter < t_exit) {
        Point P1 = intersection(P, Q, t_enter);
        Point P2 = intersection(P, Q, t_exit);

        glColor3f(1.0, 0.0, 0.0); // Red color
        glBegin(GL_LINES);
        glVertex2d(P1.x, P1.y);
        glVertex2d(P2.x, P2.y);
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); // Black color

    // Draw the window
    glBegin(GL_LINE_LOOP);
    glVertex2i(50, 50);
    glVertex2i(400, 50);
    glVertex2i(400, 400);
    glVertex2i(50, 400);
    glEnd();

    // Define the line to be clipped
    Point P = {100, 100};
    Point Q = {300, 300};

    // Draw the original line
    glColor3f(0.0, 0.0, 1.0); // Blue color
    glBegin(GL_LINES);
    glVertex2d(P.x, P.y);
    glVertex2d(Q.x, Q.y);
    glEnd();

    // Clip the line using Cyrus-Beck algorithm
    cyrusBeckAlgorithm(P, Q);

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    gluOrtho2D(0, 500, 0, 500); // 2D orthographic viewing region
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cyrus-Beck Line Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}




