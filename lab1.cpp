#include <GL/glut.h>
#include<iostream>
int x1=0;
int y1=0;
int x2=250;
int y2=150;

using namespace std;

void MouseEventHandler(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state ==  GLUT_UP)
		{   		
		y = 600 - y;  
        
			cout<<x-300<<"    "<<y<<endl;
			glutPostRedisplay();
			x1=x2;
			y1=y2;
			x2=x-300;
			y2=y-300;
		}
}

void lineBres(int x1, int y1, int x2, int y2){
		 int Dx,Dy,P,x,y,const1,const2;
		 Dx=x2-x1;	Dy=y2-y1;
		 const1=2*Dy;	const2=2*(Dy-Dx);
		 P=2*Dy-Dx;
		 x=x1;		y=y1;
		 glBegin(GL_POINTS);
		 while (x<=x2)
			{
				glVertex3i(x,y,0);
			
				if (P <0)
					 P+=const1;
				else
				{
					P+=const2;
					y++;
				}
				x++;
			}
		 glEnd();
}

void mydisplay(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	lineBres(x1,y1,x2,y2);
	glFlush();
	}
int main(int argc, char** argv){
	
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize (600, 600); 
	glutInitWindowPosition (10, 10); 
	glutCreateWindow("VE DUONG THANG DUNG TT BRESENHAM");
	
	glClearColor(1.0,1.0,1.0,0.0);
	glOrtho(-300, 300, -300, 300, -1.0, 1.0);
	glutDisplayFunc(mydisplay);
	glutMouseFunc(MouseEventHandler);
	glutMainLoop();
}

