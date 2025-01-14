#include <GL/glut.h>
#include <cmath>

float a = 1.0f, b = 1.0f, c = 1.0f;
float uStep = 0.1f, vStep = 0.1f; 
float vMax = 2.0f;                

void drawHyperboloid() {
    glBegin(GL_TRIANGLES);
    for (float v = -vMax; v < vMax; v += vStep) {
        for (float u = 0; u < 2 * M_PI; u += uStep) {
            // T�nh c�c di?m tr�n lu?i
            float x1 = a * cos(u) * cosh(v);
            float y1 = b * sin(u) * cosh(v);
            float z1 = c * sinh(v);

            float x2 = a * cos(u + uStep) * cosh(v);
            float y2 = b * sin(u + uStep) * cosh(v);
            float z2 = c * sinh(v);

            float x3 = a * cos(u) * cosh(v + vStep);
            float y3 = b * sin(u) * cosh(v + vStep);
            float z3 = c * sinh(v + vStep);

            float x4 = a * cos(u + uStep) * cosh(v + vStep);
            float y4 = b * sin(u + uStep) * cosh(v + vStep);
            float z4 = c * sinh(v + vStep);

            // V? hai tam gi�c cho m?i � vu�ng tr�n lu?i
            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
            glVertex3f(x3, y3, z3);

            glVertex3f(x2, y2, z2);
            glVertex3f(x3, y3, z3);
            glVertex3f(x4, y4, z4);
        }
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // �?t camera
    gluLookAt(3.0, 3.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glRotatef(30, 1.0, 0.0, 0.0); 

    // V? hyperboloid
    glColor3f(0.5f, 0.5f, 1.0f);
    drawHyperboloid();

    glutSwapBuffers();
}

void initOpenGL() {
    glEnable(GL_DEPTH_TEST); 
    glClearColor(0.0, 0.0, 0.0, 1.0); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Hyperboloid");

    initOpenGL();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

