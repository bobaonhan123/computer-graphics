#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

// Bi?n to�n c?c d? luu t?a d? t�m v� b�n k�nh
int centerX, centerY, radius;
bool isCenterSet = false;
bool isRadiusSet = false;

// H�m v? du?ng tr�n b?ng thu?t to�n Bresenham
void CircleBres(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;

    glBegin(GL_POINTS);
    while (y >= x) {
        // V? 8 di?m d?i x?ng
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
    glEnd();
}

// H�m x? l� s? ki?n chu?t
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Chuy?n t?a d? chu?t t? h? t?a d? c?a s? sang h? t?a d? OpenGL
        int winHeight = glutGet(GLUT_WINDOW_HEIGHT);
        y = winHeight - y;

        if (!isCenterSet) {
            centerX = x;
            centerY = y;
            isCenterSet = true;
            std::cout << "Center set at: (" << centerX << ", " << centerY << ")" << std::endl;
        } else if (!isRadiusSet) {
            radius = std::sqrt(std::pow(x - centerX, 2) + std::pow(y - centerY, 2));
            isRadiusSet = true;
            std::cout << "Radius set with length: " << radius << std::endl;
            glutPostRedisplay(); // Y�u c?u v? l?i c?a s? d? hi?n th? du?ng tr�n
        }
    }
}

// H�m hi?n th? (render) trong OpenGL
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (isCenterSet && isRadiusSet) {
        glColor3f(1.0, 0.0, 0.0); // M�u d?
        CircleBres(centerX, centerY, radius);
    }

    glFlush();
}

// H�m kh?i t?o c�c thi?t l?p OpenGL
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // M�u n?n l� den
    glColor3f(1.0, 1.0, 1.0);         // M�u v? m?c d?nh l� tr?ng
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);       // Thi?t l?p h? t?a d? 2D
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Circle Drawing with Mouse");
    
    init();
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    
    return 0;
}

