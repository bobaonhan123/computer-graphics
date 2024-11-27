#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

// Lu?i di?m di?u khi?n
vector<vector<pair<float, float> > > controlGrid;
int gridRows = 4;  // S? hàng trong lu?i
int gridCols = 4;  // S? c?t trong lu?i

// T?o m?t lu?i di?m di?u khi?n tinh d? th? nghi?m
void generateControlGrid() {
    controlGrid.resize(gridRows, vector<pair<float, float> >(gridCols));
    for (int i = 0; i < gridRows; ++i) {
        for (int j = 0; j < gridCols; ++j) {
            float x = -0.8 + j * 0.4;  // Phân b? d?u trên tr?c X
            float y = -0.8 + i * 0.4;  // Phân b? d?u trên tr?c Y
            controlGrid[i][j] = {x, y};
        }
    }
}

// Hàm tính giá tr? Bernstein
float bernstein(int i, int n, float t) {
    int binomial = 1;
    for (int j = 1; j <= i; ++j) binomial *= (n - j + 1) / j;
    return binomial * pow(t, i) * pow(1 - t, n - i);
}

// Hàm tính di?m trên m?t Bézier
pair<float, float> bezierSurface(float u, float v) {
    float x = 0, y = 0;
    int n = gridRows - 1;
    int m = gridCols - 1;

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            float bernsteinU = bernstein(i, n, u);
            float bernsteinV = bernstein(j, m, v);
            x += bernsteinU * bernsteinV * controlGrid[i][j].first;
            y += bernsteinU * bernsteinV * controlGrid[i][j].second;
        }
    }
    return {x, y};
}

// Hàm v? m?t Bézier
void drawBezierSurface() {
    glColor3f(1.0, 0.0, 0.0); // Màu d?
    glLineWidth(2.0);

    for (float u = 0; u <= 1.0; u += 0.05) {
        glBegin(GL_LINE_STRIP);
        for (float v = 0; v <= 1.0; v += 0.05) {
            pair<float, float> point = bezierSurface(u, v);
            glVertex2f(point.first, point.second);
        }
        glEnd();
    }
}

// Hàm hi?n th?
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // V? lu?i di?m di?u khi?n
    glColor3f(0.0, 0.0, 1.0); // Màu xanh
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < gridRows; ++i) {
        for (int j = 0; j < gridCols; ++j) {
            glVertex2f(controlGrid[i][j].first, controlGrid[i][j].second);
        }
    }
    glEnd();

    // V? m?t Bézier
    drawBezierSurface();

    glFlush();
}

// Hàm kh?i t?o
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // N?n tr?ng
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    // Kh?i t?o lu?i di?m di?u khi?n
    generateControlGrid();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bezier Surface");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

