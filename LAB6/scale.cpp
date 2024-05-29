#include <GL/freeglut.h>

GLfloat vertices[][2] = {{-0.5, -0.5}, {0.5, -0.5}, {0.5, 0.5}, {-0.5, 0.5}};
int numVertices = 4;

GLfloat scaleX = 1.0;
GLfloat scaleY = 1.0;

void drawPolygon()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glScalef(scaleX,scaleY,1.0);

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
        scaleX += 1.0;
        scaleY += 1.0;
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
