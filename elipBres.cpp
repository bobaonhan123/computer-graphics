#include <GL/glut.h>

// Hàm kh?i t?o
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Màu n?n den
    glMatrixMode(GL_PROJECTION);      // S? d?ng ma tr?n chi?u
    glLoadIdentity();                 // Ð?t ma tr?n don v?
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Thi?t l?p chi?u song song
}

// V? hình chóp
void drawPyramid() {
    glBegin(GL_TRIANGLES);
    
    // M?t tru?c
    glColor3f(1.0, 0.0, 0.0); // Ð?
    glVertex3f( 0.0,  1.0, 0.0); // Ð?nh
    glVertex3f(-1.0, -1.0, 1.0); // Ðáy trái
    glVertex3f( 1.0, -1.0, 1.0); // Ðáy ph?i
    
    // M?t ph?i
    glColor3f(0.0, 1.0, 0.0); // Xanh lá
    glVertex3f( 0.0,  1.0, 0.0);
    glVertex3f( 1.0, -1.0, 1.0);
    glVertex3f( 1.0, -1.0, -1.0);
    
    // M?t sau
    glColor3f(0.0, 0.0, 1.0); // Xanh duong
    glVertex3f( 0.0,  1.0, 0.0);
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    
    // M?t trái
    glColor3f(1.0, 1.0, 0.0); // Vàng
    glVertex3f( 0.0,  1.0, 0.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    
    glEnd();
    
    // Ðáy c?a hình chóp (hình vuông)
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5); // Xám
    glVertex3f(-1.0, -1.0,  1.0);
    glVertex3f( 1.0, -1.0,  1.0);
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glEnd();
}

// Hàm hi?n th?
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Di chuy?n d?i tu?ng vào khung nhìn
    glTranslatef(0.0, 0.0, -5.0);
    
    // V? hình chóp
    drawPyramid();
    
    glFlush();
}

// Hàm chính
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

