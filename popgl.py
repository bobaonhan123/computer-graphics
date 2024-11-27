from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

def init():
    glClearColor(0.0, 0.0, 0.0, 1.0)  # Đặt màu nền là đen
    glMatrixMode(GL_PROJECTION)
    gluOrtho2D(0, 500, 0, 500)  # Thiết lập hệ tọa độ

def draw_line():
    glClear(GL_COLOR_BUFFER_BIT)  # Xóa màn hình
    glColor3f(1.0, 1.0, 1.0)  # Đặt màu vẽ là trắng
    glBegin(GL_LINES)
    glVertex2f(100, 100)  # Điểm đầu của đường thẳng
    glVertex2f(400, 400)  # Điểm cuối của đường thẳng
    glEnd()
    glFlush()

def main():
    if not bool(glutInit):
        raise RuntimeError("glutInit is not available, ensure that the GLUT library is properly installed.")
    glutInit()
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowSize(500, 500)
    glutInitWindowPosition(100, 100)
    glutCreateWindow(b"Draw Line")
    init()
    glutDisplayFunc(draw_line)
    glutMainLoop()

if __name__ == "__main__":
    main()