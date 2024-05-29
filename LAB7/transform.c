#include <GL/freeglut.h>
#include <stdio.h>

// Variables for transformation
GLfloat translateX = 0.0f;
GLfloat translateY = 0.0f;
GLfloat translateZ = -5.0f;
GLfloat scaleX = 1.0f;
GLfloat scaleY = 1.0f;
GLfloat scaleZ = 1.0f;
GLfloat rotateAngle = 0.0f;
GLfloat rotateAngleY = 0.0f;
GLfloat rotateAngleZ = 0.0f;
GLfloat rotateAngleX = 0.0f;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(translateX, translateY, translateZ);
    glRotatef(rotateAngle, rotateAngleX, rotateAngleY, rotateAngleZ);
    glScalef(scaleX, scaleY, scaleZ);

    glBegin(GL_QUADS);
    // Front face
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    // Back face
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    // Top face
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    // Bottom face
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    // Right face
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    // Left face
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'd':
        translateX += 0.1f;
        break;
    case 'a':
        translateX -= 0.1f;
        break;
    case 'w':
        translateY += 0.1f;
        break;
    case 's':
        translateY -= 0.1f;
        break;
    case 'q':
        translateZ += 0.1f;
        break;
    case 'e':
        translateZ -= 0.1f;
        break;
    case 'v':
        scaleX += 0.1f;
        scaleY += 0.1f;
        scaleZ += 0.1f;
        break;
    case 'b':
        scaleX -= 0.1f;
        scaleY -= 0.1f;
        scaleZ -= 0.1f;
        break;
    case 'r':
        rotateAngle += 5.0f;
        break;
    case 'R':
        rotateAngle -= 5.0f;
        break;
    case 'x':
        rotateAngleX = 1.0f;
        break;
    case 'X':
        rotateAngleX = -1.0f;
        break;
    case 'y':
        rotateAngleY = 1.0f;
        break;
    case 'Y':
        rotateAngleY = -1.0f;
        break;
    case 'z':
        rotateAngleZ = 1.0f;
        break;
    case 'Z':
        rotateAngleZ = -1.0f;
        break;
    //resetsc
    case 'c':
        translateX = 0.0f;
        translateY = 0.0f;
        translateZ = -5.0f;
        scaleX = 1.0f;
        scaleY = 1.0f;
        scaleZ = 1.0f;
        rotateAngle = 0.0f;
        rotateAngleY = 0.0f;
        rotateAngleZ = 0.0f;
        rotateAngleX = 0.0f;
        break;

    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Object Transformation");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
