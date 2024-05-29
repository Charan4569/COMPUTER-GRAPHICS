#include <GL/glut.h>
#include <cmath>

void display() {
    static float angle = 0.0f;  // Rotation angle
    angle += 0.1f;  // Incrementing the angle for rotation

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Rotate the triangle
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);  // Red
        glVertex2f(0.5f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);  // Green
        glVertex2f(-0.25f, 0.433f);
        glColor3f(0.0f, 0.0f, 1.0f);  // Blue
        glVertex2f(-0.25f, -0.433f);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Rotating Triangle");

    glutDisplayFunc(display);
    glutIdleFunc(display);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutMainLoop();
    return 0;
}