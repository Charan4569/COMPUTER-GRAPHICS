#include <GL/glut.h>
#include <cmath>

float scale = 1.0f; // Initial scale factor
int fixedVertex = 1; // Initially fixed at vertex 1

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

	if(fixedVertex == 0)
    	glScalef(scale,scale,scale);
	else if(fixedVertex == 1) 
		glScalef(1,scale,scale);
	else if(fixedVertex == 2) 
		glScalef(scale,1,scale);
	else if(fixedVertex == 3) 
		glScalef(scale,scale,1);

    glBegin(GL_TRIANGLES);
        // Vertex 1
        if (fixedVertex == 1) glColor3f(1.0f, 0.0f, 0.0f); // Red (fixed vertex)
        else glColor3f(1.0f, 1.0f, 0.0f); // Yellow
        glVertex2f(0.5f, 0.0f);

        // Vertex 2
        if (fixedVertex == 2) glColor3f(1.0f, 0.0f, 0.0f); // Red (fixed vertex)
        else glColor3f(0.0f, 1.0f, 0.0f); // Green
        glVertex2f(-0.25f, 0.433f);

        // Vertex 3
        if (fixedVertex == 3) glColor3f(1.0f, 0.0f, 0.0f); // Red (fixed vertex)
        else glColor3f(0.0f, 0.0f, 1.0f); // Blue
        glVertex2f(-0.25f, -0.433f);
    glEnd();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '1':
            fixedVertex = 1;
            break;
        case '2':
            fixedVertex = 2;
            break;
        case '3':
            fixedVertex = 3;
            break;
		case '0': 
			fixedVertex = 0;
			break;
        case 'c':
        case 'C':
            scale = 1.0f; // Reset scale
            break;
    }
    glutPostRedisplay();
}

void specialInput(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            scale += 0.1f;
            break;
        case GLUT_KEY_DOWN:
            scale -= 0.1f;
            if (scale < 0.1f) scale = 0.1f; // Prevent scale from going negative
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Scaling Triangle");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialInput);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutMainLoop();
    return 0;
}