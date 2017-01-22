#include <glut.h> 
#define _USE_MATH_DEFINES
#include <cmath>
#include <ctime>
#include <random>

int year = 0, day = 0, sp_rotator = 0;
bool up_down = true;
GLfloat size = 0.2;					// Размер планеты
GLfloat sun_size = 1.0;	
GLfloat sun_centre_size = 0.3;
GLfloat sp_size = 0.1;

void init(void) {
	GLfloat position[4] = { 0.0, 0.0, 7.0, 1.0 };
	GLfloat light_color[4] = { 1.0, 0.0,0.0, 1.0 };


	glClearColor(0.0,0.0,0.0,1.0);   
	glShadeModel(GL_FLAT); 
	// Свет
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_DEPTH_TEST);

}

void ManageSizes()
{
	sun_size = sin(sun_centre_size);
	size = sin(sun_centre_size) / 5;
	sp_size = sin(sun_centre_size) / 5 + M_PI;
	if (up_down)
		sun_centre_size += 0.01;
	else
		sun_centre_size -= 0.01;


	if (sun_centre_size > 1.0)
		up_down = false;
	if (sun_centre_size <= 0.1)
		up_down = true;


}

//Изменение размеров окна 
void reshape(int w, int h) {   
	glViewport(0,0,(GLsizei) w, (GLsizei) h);  
	glMatrixMode(GL_PROJECTION);   
	glLoadIdentity();    
	gluPerspective(60.0,(GLfloat) w/ (GLfloat) h,1.0,20.0);   
	glMatrixMode(GL_MODELVIEW);   
	glLoadIdentity();  
	gluLookAt(0.0,0.0,5.0,0.0, 0.0,0.0,0.0,1.0, 0.0); 
} 

void calculations()
{
	sun_size = sin(sun_centre_size);
	if (!up_down)
		sun_centre_size -= 0.01;
	else
		sun_centre_size += 0.01;
	if (sun_centre_size >= 1.0)
		up_down = false;
	if (sun_centre_size <= 0.1)
		up_down = true;

	size -= 0.01;
	sp_size += 0.01;

	if (size <= 0)
		size = 0.2;
	if (sp_size > 0.2)
		sp_size = 0.01;
}

//Отображение  
void display(void) {   
	glClear(GL_COLOR_BUFFER_BIT);   

	glColor3f(1.0,1.0,1.0);  // 1 1 1
	glPushMatrix(); 

	calculations();

	//ManageSizes();


	//Рисуем солнце 
	glutWireSphere(sun_size,30,11);			//11
	glutWireSphere(sun_centre_size, 20, 19); // 20 19

	glRotatef((GLfloat)year,0.1,1.0,0.2);  
	glTranslatef(3.0,0.0,0.0);  
	glRotatef((GLfloat)day, 0.7, 1.0, 0.0);

	//Рисуем планету
	glutWireSphere(size,10,8); 

	// Рисуем спутник планеты
	glRotatef((GLfloat)sp_rotator, 0.0, 1.0, 1.0);
	glTranslatef(0.4, 0.0, 0.0);
	glRotatef((GLfloat)sp_rotator, 1.0, 1.0, 1.0);

	glutWireSphere(sp_size, 12, 16);

	glPopMatrix();
	glutSwapBuffers();

} 

//Реакция на клавиатуру  
void keyboard(unsigned char key,int x, int y) {   
	switch(key)    {     
	case 'd':     
		day=(day+5)%360;			// +10
		glutPostRedisplay();
		break;       
	case 'D':         
		day=(day-5)%360;			// -10         
		glutPostRedisplay();         
		break;     
	case 'y':    
		sp_rotator = (sp_rotator + 15) % 360;
		year = (year + 5) % 360;
		glutPostRedisplay();
		break;      
	case 'Y':       
		sp_rotator = (sp_rotator - 15) % 360;
		year=(year-5)%360;         
		glutPostRedisplay();         
		break;
	default:       
		break;   
	} 
} 

int main(int argc, char **argv) { 
	srand(time(NULL));
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);    
	glutInitWindowSize(1500, 1000); 
	glutInitWindowPosition(0, 0); 
	glutCreateWindow("Planetary System"); 
	init();    
	glutDisplayFunc(display);  
	glutReshapeFunc(reshape);   
	glutKeyboardFunc(keyboard);   
	glutMainLoop(); 
	return 0;
}