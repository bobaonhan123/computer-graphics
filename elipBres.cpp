#include <GL/glut.h>

// H�m kh?i t?o
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // M�u n?n den
    glMatrixMode(GL_PROJECTION);      // S? d?ng ma tr?n chi?u
    glLoadIdentity();                 // �?t ma tr?n don v?
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Thi?t l?p chi?u song song
}

// V? h�nh ch�p
void drawPyramid() {
    glBegin(GL_TRIANGLES);
    
    // M?t tru?c
    glColor3f(1.0, 0.0, 0.0); // �?
    glVertex3f( 0.0,  1.0, 0.0); // �?nh
    glVertex3f(-1.0, -1.0, 1.0); // ��y tr�i
    glVertex3f( 1.0, -1.0, 1.0); // ��y ph?i
    
    // M?t ph?i
    glColor3f(0.0, 1.0, 0.0); // Xanh l�
    glVertex3f( 0.0,  1.0, 0.0);
    glVertex3f( 1.0, -1.0, 1.0);
    glVertex3f( 1.0, -1.0, -1.0);
    
    // M?t sau
    glColor3f(0.0, 0.0, 1.0); // Xanh duong
    glVertex3f( 0.0,  1.0, 0.0);
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    
    // M?t tr�i
    glColor3f(1.0, 1.0, 0.0); // V�ng
    glVertex3f( 0.0,  1.0, 0.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    
    glEnd();
    
    // ��y c?a h�nh ch�p (h�nh vu�ng)
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5); // X�m
    glVertex3f(-1.0, -1.0,  1.0);
    glVertex3f( 1.0, -1.0,  1.0);
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glEnd();
}

// H�m hi?n th?
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Di chuy?n d?i tu?ng v�o khung nh�n
    glTranslatef(0.0, 0.0, -5.0);
    
    // V? h�nh ch�p
    drawPyramid();
    
    glFlush();
}

// H�m ch�nh
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Pyramid - Orthographic Projection");
    
    init();
    
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}

