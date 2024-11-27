#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <cstdlib>

float angleX = 0.0f, angleY = 0.0f, angleZ = 0.0f;  
float scale = 1.0f; 
float eyeX = 0.0f, eyeY = 1.0f, eyeZ = 100.0f; // Adjusted for slight tilt upwards
bool perspective = true;

void initOpenGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
	
	
	GLfloat lightPosition[] = { -2.0f, 0.0f, -2.0f, 0.0f };  // V? trí nguon sang (x, y, z, w)
    GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };   // Ánh sáng khuech tan (white)
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // Ánh sáng phan chieu (white)
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };   // Ánh sáng moi truong

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);

    GLfloat materialDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };  
    GLfloat materialAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; 
    GLfloat materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
    GLfloat materialShininess[] = { 50.0f };                 

    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
}

void applyTransformationMatrix(const float matrix[16]) {
    glMultMatrixf(matrix);
}

void buildRotationMatrixX(float angle, float matrix[16]) {
    float rad = angle * M_PI / 180.0f;
    float c = cos(rad);
    float s = sin(rad);

    matrix[0] = 1; matrix[1] = 0;  matrix[2] = 0;  matrix[3] = 0;
    matrix[4] = 0; matrix[5] = c;  matrix[6] = -s; matrix[7] = 0;
    matrix[8] = 0; matrix[9] = s;  matrix[10] = c; matrix[11] = 0;
    matrix[12] = 0; matrix[13] = 0; matrix[14] = 0; matrix[15] = 1;
}

void buildRotationMatrixY(float angle, float matrix[16]) {
    float rad = angle * M_PI / 180.0f;
    float c = cos(rad);
    float s = sin(rad);

    matrix[0] = c;  matrix[1] = 0; matrix[2] = s;  matrix[3] = 0;
    matrix[4] = 0;  matrix[5] = 1; matrix[6] = 0;  matrix[7] = 0;
    matrix[8] = -s; matrix[9] = 0; matrix[10] = c; matrix[11] = 0;
    matrix[12] = 0; matrix[13] = 0; matrix[14] = 0; matrix[15] = 1;
}

void buildRotationMatrixZ(float angle, float matrix[16]) {
    float rad = angle * M_PI / 180.0f;
    float c = cos(rad);
    float s = sin(rad);

    matrix[0] = c;  matrix[1] = -s; matrix[2] = 0; matrix[3] = 0;
    matrix[4] = s;  matrix[5] = c;  matrix[6] = 0; matrix[7] = 0;
    matrix[8] = 0;  matrix[9] = 0;  matrix[10] = 1; matrix[11] = 0;
    matrix[12] = 0; matrix[13] = 0; matrix[14] = 0; matrix[15] = 1;
}

void buildScalingMatrix(float sx, float sy, float sz, float matrix[16]) {
    matrix[0] = sx; matrix[1] = 0;  matrix[2] = 0;  matrix[3] = 0;
    matrix[4] = 0;  matrix[5] = sy; matrix[6] = 0;  matrix[7] = 0;
    matrix[8] = 0;  matrix[9] = 0;  matrix[10] = sz; matrix[11] = 0;
    matrix[12] = 0; matrix[13] = 0; matrix[14] = 0;  matrix[15] = 1;
}

void buildTranslationMatrix(float tx, float ty, float tz, float matrix[16]) {
    matrix[0] = 1; matrix[1] = 0; matrix[2] = 0; matrix[3] = 0;
    matrix[4] = 0; matrix[5] = 1; matrix[6] = 0; matrix[7] = 0;
    matrix[8] = 0; matrix[9] = 0; matrix[10] = 1; matrix[11] = 0;
    matrix[12] = tx; matrix[13] = ty; matrix[14] = tz; matrix[15] = 1;
}

void drawObject() {
	//https://free3d.com/
	std::string objFileName = "12190_Heart_v1_L3.obj";
    std::string nhanFileName = objFileName.substr(0, objFileName.find_last_of('.')) + ".nhan";
	
    //std::string command = "python ./tonhan.py " + objFileName;
    //std::string command = "C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe -Command \"python ./tonhan.py " + objFileName + "\"";
	//std::string command = "C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe -Command \"ls\"";
	std::string pythonPath = "C:\\Users\\hosyb\\AppData\\Local\\Programs\\Python\\Python312\\python.exe";
    std::string scriptPath = "./tonhan.py"; 
    std::string command = pythonPath + " " + scriptPath + " " + objFileName;
    
    int result = system(command.c_str());
    if (result != 0) {
        std::cerr << "Error running Python script to generate .nhan file." << std::endl;
        return;
    }

    std::ifstream file(nhanFileName.c_str());
    if (!file.is_open()) {
        std::cerr << "Cannot open " << nhanFileName << " file." << std::endl;
        return;
    }

    int numFaces;
    file >> numFaces;
    file.ignore();    

    for (int i = 0; i < numFaces; ++i) {
        int numVertices;
        float r, g, b;
        
        file >> numVertices >> r >> g >> b;
        file.ignore();

        glColor3f(r, g, b);

        std::vector<std::vector<float> > vertices(numVertices, std::vector<float>(3));
        for (int j = 0; j < numVertices; ++j) {
            file >> vertices[j][0] >> vertices[j][1] >> vertices[j][2];
        }
        file.ignore();
		
		// tinh vector phap tuyen
        std::vector<float> v0 = vertices[0];
        std::vector<float> v1 = vertices[1];
        std::vector<float> v2 = vertices[2];
	
        float edge1[3] = { v1[0] - v0[0], v1[1] - v0[1], v1[2] - v0[2] };
        float edge2[3] = { v2[0] - v0[0], v2[1] - v0[1], v2[2] - v0[2] };

        float normal[3] = {
            edge1[1] * edge2[2] - edge1[2] * edge2[1],
            edge1[2] * edge2[0] - edge1[0] * edge2[2],
            edge1[0] * edge2[1] - edge1[1] * edge2[0]
        };

        float length = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
        normal[0] /= length;
        normal[1] /= length;
        normal[2] /= length;

        glNormal3f(normal[0], normal[1], normal[2]);

        glBegin(GL_POLYGON); 
        for (int j = 0; j < numVertices; ++j) {
            glVertex3f(vertices[j][0], vertices[j][1], vertices[j][2]);
        }
        glEnd();
    }

    file.close();
}


void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (perspective) {
        gluPerspective(70.0, 1.0, 1.0, 200.0); // fovy=45 , aspect=1.0, zNear=1.0, zFar=200.0
    } else {
        glOrtho(-2, 2, -2, 2, 1.0, 200.0); // left=-2, right=2, bottom=-2, top=2, zNear=1.0, zFar=200.0
    }

    float viewMatrix[16];
    buildTranslationMatrix(-eyeX, -eyeY, -eyeZ, viewMatrix);
    applyTransformationMatrix(viewMatrix);

    float scaleMatrix[16];
    buildScalingMatrix(scale, scale, scale, scaleMatrix);
    applyTransformationMatrix(scaleMatrix);

    float rotationXMatrix[16];
    buildRotationMatrixX(angleX, rotationXMatrix);
    applyTransformationMatrix(rotationXMatrix);

    float rotationYMatrix[16];
    buildRotationMatrixY(angleY, rotationYMatrix);
    applyTransformationMatrix(rotationYMatrix);

    float rotationZMatrix[16];
    buildRotationMatrixZ(angleZ, rotationZMatrix);
    applyTransformationMatrix(rotationZMatrix);

    drawObject();
    glutSwapBuffers();
}

void keyboardControl(int key, int x, int y) {
    switch (key) {
    	
        case GLUT_KEY_UP:
            angleX += 5.0; break;
        case GLUT_KEY_DOWN:
            angleX -= 5.0; break;
        case GLUT_KEY_LEFT:
            angleY -= 5.0; break;
        case GLUT_KEY_RIGHT:
            angleY += 5.0; break;
        
    }
    glutPostRedisplay();
}

void mouseControl(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        angleZ += 5.0;
    }
    glutPostRedisplay();
}

void cameraControl(unsigned char key, int x, int y) {
    switch (key) {
    	case 'p':  // ASCII of ESC key
            exit(0); 
            break;
        case 'w': 
            eyeZ -= 1.1f; break;
        case 's': 
            eyeZ += 1.1f; break;
        case 'a': 
            eyeX -= 1.1f; break;
        case 'd': 
            eyeX += 1.1f; break;
        case 'q': 
            eyeY += 1.1f; break;
        case 'e': 
            eyeY -= 1.1f; break;
        case 'n':
        	scale += 1.1f; break;
        case 'm':
        	scale -= 1.1f; break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("3D Object Viewer");

    glutFullScreen(); 

    initOpenGL();
    glutDisplayFunc(renderScene);
    glutSpecialFunc(keyboardControl);
    glutMouseFunc(mouseControl);
    glutKeyboardFunc(cameraControl); 
    glutMainLoop();
    return 0;
}

