#include <GL/freeglut.h>
#include <iostream>
#include <vector>

// Window boundaries
const int X_MIN = 50;
const int X_MAX = 400;
const int Y_MIN = 50;
const int Y_MAX = 400;

struct Point {
    double x, y;
};

Point computeIntersection(Point p1, Point p2, double x1, double y1, double x2, double y2) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double t = ((x1 - p1.x) * dx + (y1 - p1.y) * dy) / (dx * (x2 - x1) + dy * (y2 - y1));

    Point intersection;
    intersection.x = p1.x + t * (p2.x - p1.x);
    intersection.y = p1.y + t * (p2.y - p1.y);

    return intersection;
}

bool isInside(double x, double y, double x1, double y1, double x2, double y2) {
    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

std::vector<Point> clip(const std::vector<Point>& polygon, double x1, double y1, double x2, double y2) {
    std::vector<Point> output;
    int size = polygon.size();

    for (int i = 0; i < size; i++) {
        int nextIndex = (i + 1) % size;
        Point current = polygon[i];
        Point next = polygon[nextIndex];

        bool inside1 = isInside(current.x, current.y, x1, y1, x2, y2);
        bool inside2 = isInside(next.x, next.y, x1, y1, x2, y2);

        if (inside1 && inside2) {
            output.push_back(next);
        } else if (inside1 && !inside2) {
            output.push_back(computeIntersection(current, next, x1, y1, x2, y2));
        } else if (!inside1 && inside2) {
            output.push_back(computeIntersection(current, next, x1, y1, x2, y2));
            output.push_back(next);
        }
    }

    return output;
}

std::vector<Point> clipPolygon(const std::vector<Point>& polygon) {
    std::vector<Point> output = polygon;

    // Clip against left boundary
    output = clip(output, X_MIN, Y_MIN, X_MIN, Y_MAX);

    // Clip against top boundary
    output = clip(output, X_MIN, Y_MAX, X_MAX, Y_MAX);

    // Clip against right boundary
    output = clip(output, X_MAX, Y_MAX, X_MAX, Y_MIN);

    // Clip against bottom boundary
    output = clip(output, X_MAX, Y_MIN, X_MIN, Y_MIN);

    return output;
}



void drawPolygon(const std::vector<Point>& polygon) {
    glColor3f(0.0, 0.0, 1.0); // blue color
    glBegin(GL_LINE_LOOP);
    for (const auto& point : polygon) {
        glVertex2d(point.x, point.y);
    }
    glEnd();
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

    // Define the original polygon
    std::vector<Point> polygon = {{100, 100}, {300, 100}, {300, 300}, {200, 400}, {100, 300}};

    // Draw the original polygon
    glColor3f(0.0, 0.0, 1.0); // blue color
    glBegin(GL_LINE_LOOP);
    for (const auto& point : polygon) {
        glVertex2d(point.x, point.y);
    }
    glEnd();

    // Clip the polygon
    std::vector<Point> clippedPolygon = clipPolygon(polygon);

    // Draw the clipped polygon
    drawPolygon(clippedPolygon);

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
    glutCreateWindow("Cohen-Sutherland-Hodgeman Polygon Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

