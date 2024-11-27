#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

int centerx = 0, centery = 0;
int radius = 0;

void plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(centerx + x, centery + y);
    glVertex2i(centerx - x, centery + y);
    glVertex2i(centerx + x, centery - y);
    glVertex2i(centerx - x, centery - y);
    glVertex2i(centerx + y, centery + x);
    glVertex2i(centerx - y, centery + x);
    glVertex2i(centerx + y, centery - x);
    glVertex2i(centerx - y, centery - x);
    glEnd();
}

void drawCircle() {
    int x = 0;
    int y = radius;
    int d = 1 - radius;

    plot(x, y);

    while (x < y) {
        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
        plot(x, y);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); // Red color
    drawCircle();
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    gluOrtho2D(-250, 250, -250, 250);
}

void MouseEventHandler(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        // Convert window coordinates to OpenGL coordinates
        x = x - 250; // Centering on the origin
        y = 250 - y; // Flipping y-axis and centering on the origin

        cout << "Mouse Clicked at: (" << x << ", " << y << ")\n";
        
        if (centerx == 0 && centery == 0) {
            centerx = x;
            centery = y;
            return;
        }

        if (radius == 0) {
            radius = sqrt((x - centerx) * (x - centerx) + (y - centery) * (y - centery));
            display();
        }
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Midpoint Circle Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(MouseEventHandler);
    glutMainLoop();
    return 0;
}
