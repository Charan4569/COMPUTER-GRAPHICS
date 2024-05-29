#include <GL/freeglut.h>

GLfloat vertices[][2] = {{-0.5, -0.5}, {0.5, -0.5}, {0.5, 0.5}, {-0.5, 0.5}};
int numVertices = 4;

GLfloat translateX = 0.0;

void drawPolygon()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(translateX, 0.0, 0.0);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < numVertices; ++i)
    {
        glVertex2fv(vertices[i]);
    }
    glEnd();

    glFlush();
}
void mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        translateX += 1.5;
        glutPostRedisplay();
    }
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2D Translation");

    init();
    glutDisplayFunc(drawPolygon);
    glutMouseFunc(mouseClick);

    glutMainLoop();
    return 0;
}
