#include <GL/freeglut.h>
#include <vector>
#include <cmath>
#include <iostream>

// Define the vertex data for a cube
static const GLfloat cubeVertices[] = {
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, -0.5f};

static const GLubyte cubeIndices[] = {
	0, 1, 2, 3,
	3, 2, 6, 7,
	7, 6, 5, 4,
	4, 5, 1, 0,
	1, 5, 6, 2,
	4, 0, 3, 7};

// Define the vertex data for a sphere
static const int sphereStacks = 20;
static const int sphereSlices = 20;
std::vector<GLfloat> sphereVertices;
std::vector<GLubyte> sphereIndices;

// Define the vertex data for a cylinder
static const int cylinderStacks = 20;
static const int cylinderSlices = 20;
std::vector<GLfloat> cylinderVertices;
std::vector<GLubyte> cylinderIndices;

// Current object being edited
enum ObjectType
{
	CUBE,
	SPHERE,
	CYLINDER
};
ObjectType currentObject = CUBE;

// Sculpting parameters
float sculptingRadius = 0.1f;
float sculptingStrength = 0.01f;

// Texture data
GLuint textureID;

// Window dimensions
int windowWidth = 800;
int windowHeight = 600;

// Camera parameters
float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 3.0f;
float cameraRotationX = 0.0f, cameraRotationY = 0.0f;

void generateSphereData()
{
	sphereVertices.clear();
	sphereIndices.clear();

	for (int stackIndex = 0; stackIndex <= sphereStacks; ++stackIndex)
	{
		float stackRatio = static_cast<float>(stackIndex) / sphereStacks;
		float phi = stackRatio * M_PI;

		for (int sliceIndex = 0; sliceIndex <= sphereSlices; ++sliceIndex)
		{
			float sliceRatio = static_cast<float>(sliceIndex) / sphereSlices;
			float theta = sliceRatio * 2.0f * M_PI;

			float x = sin(phi) * cos(theta);
			float y = cos(phi);
			float z = sin(phi) * sin(theta);

			sphereVertices.push_back(x);
			sphereVertices.push_back(y);
			sphereVertices.push_back(z);
		}
	}

	for (int stackIndex = 0; stackIndex < sphereStacks; ++stackIndex)
	{
		int stackStart = stackIndex * (sphereSlices + 1);
		int nextStackStart = (stackIndex + 1) * (sphereSlices + 1);

		for (int sliceIndex = 0; sliceIndex < sphereSlices; ++sliceIndex)
		{
			int currentIndex = stackStart + sliceIndex;
			int nextIndex = currentIndex + 1;
			int nextStackIndex = nextStackStart + sliceIndex;
			int nextStackNextIndex = nextStackIndex + 1;

			sphereIndices.push_back(currentIndex);
			sphereIndices.push_back(nextStackIndex);
			sphereIndices.push_back(nextIndex);

			sphereIndices.push_back(nextIndex);
			sphereIndices.push_back(nextStackIndex);
			sphereIndices.push_back(nextStackNextIndex);
		}
	}
}

void generateCylinderData()
{
	cylinderVertices.clear();
	cylinderIndices.clear();

	for (int stackIndex = 0; stackIndex <= cylinderStacks; ++stackIndex)
	{
		float stackRatio = static_cast<float>(stackIndex) / cylinderStacks;
		float y = (stackRatio * 2.0f) - 1.0f;

		for (int sliceIndex = 0; sliceIndex <= cylinderSlices; ++sliceIndex)
		{
			float sliceRatio = static_cast<float>(sliceIndex) / cylinderSlices;
			float theta = sliceRatio * 2.0f * M_PI;

			float x = cos(theta);
			float z = sin(theta);

			cylinderVertices.push_back(x);
			cylinderVertices.push_back(y);
			cylinderVertices.push_back(z);
		}
	}

	for (int stackIndex = 0; stackIndex < cylinderStacks; ++stackIndex)
	{
		int stackStart = stackIndex * (cylinderSlices + 1);
		int nextStackStart = (stackIndex + 1) * (cylinderSlices + 1);

		for (int sliceIndex = 0; sliceIndex < cylinderSlices; ++sliceIndex)
		{
			int currentIndex = stackStart + sliceIndex;
			int nextIndex = currentIndex + 1;
			int nextStackIndex = nextStackStart + sliceIndex;
			int nextStackNextIndex = nextStackIndex + 1;

			cylinderIndices.push_back(currentIndex);
			cylinderIndices.push_back(nextStackIndex);
			cylinderIndices.push_back(nextIndex);

			cylinderIndices.push_back(nextIndex);
			cylinderIndices.push_back(nextStackIndex);
			cylinderIndices.push_back(nextStackNextIndex);
		}
	}
}

void drawObject()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Set up camera
	gluLookAt(cameraX, cameraY, cameraZ,
			  0.0f, 0.0f, 0.0f,
			  0.0f, 1.0f, 0.0f);

	// Draw the current object
	switch (currentObject)
	{
	case CUBE:
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, cubeVertices);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
		glDisableClientState(GL_VERTEX_ARRAY);
		break;
	case SPHERE:
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, &sphereVertices[0]);
		glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_BYTE, &sphereIndices[0]);
		glDisableClientState(GL_VERTEX_ARRAY);
		break;
	case CYLINDER:
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, &cylinderVertices[0]);
		glDrawElements(GL_TRIANGLES, cylinderIndices.size(), GL_UNSIGNED_BYTE, &cylinderIndices[0]);
		glDisableClientState(GL_VERTEX_ARRAY);
		break;
	}

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		currentObject = CUBE;
		break;
	case '2':
		currentObject = SPHERE;
		break;
	case '3':
		currentObject = CYLINDER;
		break;
	case 'w':
		cameraZ -= 0.1f;
		break;
	case 's':
		cameraZ += 0.1f;
		break;
	case 'a':
		cameraX -= 0.1f;
		break;
	case 'd':
		cameraX += 0.1f;
		break;
	case 'q':
		cameraRotationY += 5.0f;
		break;
	case 'e':
		cameraRotationY -= 5.0f;
		break;
		// Add more key bindings for sculpting, texturing, etc.
	}
	glutPostRedisplay();
}

std::vector<GLfloat> getCurrentVertexData()
{
	switch (currentObject)
	{
	case CUBE:
		return std::vector<GLfloat>(std::begin(cubeVertices), std::end(cubeVertices));
	case SPHERE:
		return sphereVertices;
	case CYLINDER:
		return cylinderVertices;
	default:
		return sphereVertices;
	}
}

std::vector<GLubyte> getCurrentIndexData()
{
	switch (currentObject)
	{
	case CUBE:
		return std::vector<GLubyte>(std::begin(cubeIndices), std::end(cubeIndices));
	case SPHERE:
		return sphereIndices;
	case CYLINDER:
		return cylinderIndices;
	default:
		return sphereIndices;
	}
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// Convert mouse coordinates to NDC
		float mouseX = (2.0f * x) / windowWidth - 1.0f;
		float mouseY = 1.0f - (2.0f * y) / windowHeight;
	}

	glutPostRedisplay();
}

int prevX = 0, prevY = 0;
bool isRotating = false;

void motion(int x, int y)
{
	if (isRotating)
	{
		// Calculate the rotation deltas
		int deltaX = x - prevX;
		int deltaY = y - prevY;

		// Update camera rotation
		cameraRotationX += static_cast<float>(deltaY) * 0.1f;
		cameraRotationY += static_cast<float>(deltaX) * 0.1f;

		// Clamp the rotation angles
		cameraRotationX = std::fmax(-89.9f, std::fmin(89.9f, cameraRotationX));
	}

	prevX = x;
	prevY = y;

	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("3D Modeling Tool");

	generateSphereData();
	generateCylinderData();

	// Load texture
	// ...

	glutDisplayFunc(drawObject);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glutMainLoop();

	return 0;
}