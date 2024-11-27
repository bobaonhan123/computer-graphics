#include <GL/glut.h>
#include <iostream>
#include <cmath>

float angleX = 0.0f, angleY = 0.0f, angleZ = 0.0f;  
float scale = 1.0f; 
float eyeX = 0.0f, eyeY = 0.0f, eyeZ = 5.0f; 
bool perspective = true;

void initOpenGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

void applyTransformationMatrix(const float matrix[16]) {
    glMultMatrixf(matrix);
}

void buildRotationMatrix(float angle, float x, float y, float z, float matrix[16]) {
    float rad = angle * M_PI / 180.0f;
    float c = cos(rad);
    float s = sin(rad);
    float t = 1 - c;

    matrix[0] = t * x * x + cos(rad);
    matrix[1] = t * x * y + s * z;
    matrix[2] = t * x * z - s * y;
    matrix[3] = 0;

    matrix[4] = t * x * y - s * z;
    matrix[5] = t * y * y + c;
    matrix[6] = t * y * z + s * x;
    matrix[7] = 0;

    matrix[8] = t * x * z + s * y;
    matrix[9] = t * y * z - s * x;
    matrix[10] = t * z * z + c;
    matrix[11] = 0;

    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1;
}

void buildScalingMatrix(float sx, float sy, float sz, float matrix[16]) {
    matrix[0] = sx; matrix[1] = 0;  matrix[2] = 0;  matrix[3] = 0;
    matrix[4] = 0;  matrix[5] = sy; matrix[6] = 0;  matrix[7] = 0;
    matrix[8] = 0;  matrix[9] = 0;  matrix[10] = sz; matrix[11] = 0;
    matrix[12] = 0; matrix[13] = 0; matrix[14] = 0;  matrix[15] = 1;
}

void buildTranslationMatrix(float tx, float ty, float tz, float matrix[16]) {
    matrix[0] = 1; matrix[1] = 0; matrix[2] = 0; matrix[3] = 0;
    matrix[4] = 0; matrix[5] = 1; matrix[6] = 0; matrix[7] = 0;
    matrix[8] = 0; matrix[9] = 0; matrix[10] = 1; matrix[11] = 0;
    matrix[12] = tx; matrix[13] = ty; matrix[14] = tz; matrix[15] = 1;
}

void drawObject() {
    glBegin(GL_QUADS);
    glColor3f(10.0, 0.0, 0.0); 
    glVertex3f(-1.0, -1.0,  1.0);
    glVertex3f( 1.0, -1.0,  1.0);
    glVertex3f( 1.0,  1.0,  1.0);
    glVertex3f(-1.0,  1.0,  1.0);
    glEnd();
    glBegin(GL_QUADS);
    // Back face
    glColor3f(0.0, 10.0, 0.0); 
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0,  1.0, -1.0);
    glVertex3f( 1.0,  1.0, -1.0);
    glVertex3f( 1.0, -1.0, -1.0);
    glEnd();
    glBegin(GL_QUADS);

    glColor3f(0.0, 0.0, 10.0);
    glVertex3f(-1.0,  1.0, -1.0);
    glVertex3f(-1.0,  1.0,  1.0);
    glVertex3f( 1.0,  1.0,  1.0);
    glVertex3f( 1.0,  1.0, -1.0);
    glEnd();
    glBegin(GL_QUADS);

    glColor3f(10.0, 10.0, 0.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f( 1.0, -1.0,  1.0);
    glVertex3f(-1.0, -1.0,  1.0);
    glEnd();
    glBegin(GL_QUADS);

    glColor3f(10.0, 0.0, 10.0);
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f( 1.0,  1.0, -1.0);
    glVertex3f( 1.0,  1.0,  1.0);
    glVertex3f( 1.0, -1.0,  1.0);
    glEnd();
    glBegin(GL_QUADS);

    glColor3f(0.0, 10.0, 10.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0,  1.0);
    glVertex3f(-1.0,  1.0,  1.0);
    glVertex3f(-1.0,  1.0, -1.0);
    glEnd();
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (perspective) {
        gluPerspective(45.0, 1.0, 1.0, 100.0);
    } else {
        glOrtho(-2, 2, -2, 2, 1.0, 100.0);
    }

    float viewMatrix[16];
    buildTranslationMatrix(-eyeX, -eyeY, -eyeZ, viewMatrix);
    applyTransformationMatrix(viewMatrix);

    float scaleMatrix[16];
    buildScalingMatrix(scale, scale, scale, scaleMatrix);
    applyTransformationMatrix(scaleMatrix);

    float rotationXMatrix[16];
    buildRotationMatrix(angleX, 1.0f, 0.0f, 0.0f, rotationXMatrix);
    applyTransformationMatrix(rotationXMatrix);

    float rotationYMatrix[16];
    buildRotationMatrix(angleY, 0.0f, 1.0f, 0.0f, rotationYMatrix);
    applyTransformationMatrix(rotationYMatrix);

    float rotationZMatrix[16];
    buildRotationMatrix(angleZ, 0.0f, 0.0f, 1.0f, rotationZMatrix);
    applyTransformationMatrix(rotationZMatrix);

    drawObject();
    glutSwapBuffers();
}

void keyboardControl(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            angleX += 5.0; break;
        case GLUT_KEY_DOWN:
            angleX -= 5.0; break;
        case GLUT_KEY_LEFT:
            angleY -= 5.0; break;
        case GLUT_KEY_RIGHT:
            angleY += 5.0; break;
    }
    glutPostRedisplay();
}

void mouseControl(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        angleZ += 5.0;
    }
    glutPostRedisplay();
}

void cameraControl(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': 
            eyeZ -= 0.1f; break;
        case 's': 
            eyeZ += 0.1f; break;
        case 'a': 
            eyeX -= 0.1f; break;
        case 'd': 
            eyeX += 0.1f; break;
        case 'q': 
            eyeY += 0.1f; break;
        case 'e': 
            eyeY -= 0.1f; break;
        case 'n':
        	scale += 0.1f; break;
        case 'm':
        	scale -= 0.1f; break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Object Viewer");

    initOpenGL();
    glutDisplayFunc(renderScene);
    glutSpecialFunc(keyboardControl);
    glutMouseFunc(mouseControl);
    glutKeyboardFunc(cameraControl); 

    glutMainLoop();
    return 0;
}

