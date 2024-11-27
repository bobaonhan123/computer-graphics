#include <GL/glut.h>
#include <iostream>
using namespace std;

int centerx = 0, centery = 0;
int a = 0;
int b = 0;

void plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(centerx + x, centery + y);
    glVertex2i(centerx - x, centery + y);
    glVertex2i(centerx + x, centery - y);
    glVertex2i(centerx - x, centery - y);
    glEnd();
}


bool isInsideEllipseColor(int x, int y, float* color) {
    float pointColor[3];
    glReadPixels(x + 300, y + 300, 1, 1, GL_RGB, GL_FLOAT, pointColor);
    return pointColor[0] == color[0] && pointColor[1] == color[1] && pointColor[2] == color[2];
}


const int MAX_SIZE = 600; // Kích thu?c vùng v?
bool visited[MAX_SIZE][MAX_SIZE]; // M?ng theo dõi di?m dã tô màu hay chua
void floodFill(int x, int y, float* fillColor, float* boundaryColor) {
    if (x < -300 || x > 300 || y < -300 || y > 300) {
        return;  // Gi?i h?n vùng tô màu
    }

    if (visited[x + 300][y + 300]) {
        return;
    }

    float currentColor[3];
    glReadPixels(x + 300, y + 300, 1, 1, GL_RGB, GL_FLOAT, currentColor);

    if ((currentColor[0] == boundaryColor[0] && currentColor[1] == boundaryColor[1] && currentColor[2] == boundaryColor[2]) ||
        (currentColor[0] == fillColor[0] && currentColor[1] == fillColor[1] && currentColor[2] == fillColor[2])) {
        return;
    }

    visited[x + 300][y + 300] = true;

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();

    floodFill(x + 1, y, fillColor, boundaryColor);
    floodFill(x - 1, y, fillColor, boundaryColor);
    floodFill(x, y + 1, fillColor, boundaryColor);
    floodFill(x, y - 1, fillColor, boundaryColor);
}



void drawEllipse() {
    int x = 0;
    int y = b;

    float d1 = (b * b) - (a * a * b) + (0.25 * a * a);
    int dx = 2 * b * b * x;
    int dy = 2 * a * a * y;

    while (dx < dy) {
        plot(x, y);

        if (d1 < 0) {
            x++;
            dx = dx + (2 * b * b);
            d1 = d1 + dx + (b * b);
        } else {
            x++;
            y--;
            dx = dx + (2 * b * b);
            dy = dy - (2 * a * a);
            d1 = d1 + dx - dy + (b * b);
        }
    }

    float d2 = ((b * b) * ((x + 0.5) * (x + 0.5))) + ((a * a) * ((y - 1) * (y - 1))) - (a * a * b * b);

    while (y >= 0) {
        plot(x, y);

        if (d2 > 0) {
            y--;
            dy = dy - (2 * a * a);
            d2 = d2 + (a * a) - dy;
        } else {
            y--;
            x++;
            dx = dx + (2 * b * b);
            dy = dy - (2 * a * a);
            d2 = d2 + dx - dy + (a * a);
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    drawEllipse();
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    gluOrtho2D(-300, 300, -300, 300);
}

void MouseEventHandler(int button, int state, int x, int y) {
    y = 600 - y; // Chuy?n d?i t?a d? OpenGL
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        if (centerx == 0 && centery == 0) {
            centerx = x - 300;
            centery = y - 300;
            return;
        }

        if (a == 0) {
            a = x - 300;
            return;
        }

        if (b == 0) {
            b = y - 300;
            display();
        }
    }

    // Kích ho?t tô màu b?ng nút chu?t ph?i
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
        float boundaryColor[] = {1.0, 0.0, 0.0}; // Màu ranh gi?i (ellipse)
        float fillColor[] = {0.0, 0.0, 1.0};     // Màu tô (màu xanh duong)
        floodFill(centerx, centery, fillColor, boundaryColor);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Midpoint Ellipse Drawing with Flood-Fill");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(MouseEventHandler);

    glutMainLoop();
    return 0;
}

