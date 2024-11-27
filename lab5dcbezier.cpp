#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

// Danh s�ch c�c di?m di?u khi?n
vector<pair<float, float> > controlPoints;

// H�m v? m?t di?m
void drawPoint(float x, float y) {
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

// H�m t�nh di?m tr�n du?ng cong B�zier t?i t
pair<float, float> bezier(float t) {
    float x = 0, y = 0;
    int n = controlPoints.size() - 1;

    for (int i = 0; i <= n; ++i) {
        // T�nh h? s? nh? th?c
        int binomial = 1;
        for (int j = 1; j <= i; ++j) binomial *= (n - j + 1) / j;

        float bernstein = binomial * pow(t, i) * pow(1 - t, n - i);
        x += bernstein * controlPoints[i].first;
        y += bernstein * controlPoints[i].second;
    }

    return {x, y};
}

// H�m v? du?ng cong B�zier
void drawBezierCurve() {
    glColor3f(1.0, 0.0, 0.0); // M�u d?
    glLineWidth(2.0);

    glBegin(GL_LINE_STRIP);
    for (float t = 0.0; t <= 1.0; t += 0.01) {
        pair<float, float> point = bezier(t);
        glVertex2f(point.first, point.second);
    }
    glEnd();
}

// H�m hi?n th?
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // V? c�c di?m di?u khi?n
    glColor3f(0.0, 0.0, 1.0); // M�u xanh
    //for (auto& point : controlPoints) {
    for(int i=0;i<controlPoints.size();i++) {
    	pair<float, float> &point = controlPoints[i];
        drawPoint(point.first, point.second);
    }

    // V? du?ng cong B�zier
    if (controlPoints.size() >= 4) {
        drawBezierCurve();
    }

    glFlush();
}

// H�m x? l� s? ki?n chu?t d? th�m di?m di?u khi?n
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float xf = (float)x / 500 * 2 - 1;  // Chuy?n d?i t?a d? c?a s? sang t?a d? OpenGL
        float yf = 1 - (float)y / 500 * 2; // Tuong t? v?i tr?c Y
        controlPoints.push_back({xf, yf});
        glutPostRedisplay();
    }
}

// H�m kh?i t?o
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // M�u n?n tr?ng
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // H? t?a d? t? -1 d?n 1
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bezier Curve");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

