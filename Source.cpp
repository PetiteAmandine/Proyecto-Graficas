#include "GL/glut.h"
GLsizei winWidth =1000, winHeight = 1000; // Initial display-window size.

void iniciar(void)
{	

	glClearColor(0, 0, 0, 1);
	glOrtho(-500, 500, -500, 500, -100, 100);
}

float angulo = 0;
void Dibujo(void)
{
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glFlush();
	//glMatrixMode(GL_PROJECTION);
	//glOrtho(-100, 100, -100, 100, 0, 100);
	//glClear(GL_COLOR_BUFFER_BIT); // Clear display window.
	//gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 100.0, 10.0, 10.0, 0.0);
	//glClearColor(1.0, 1.0, 1.0, 1.0); // Set display-window color.
	//						  /* Set viewing parameters with world z axis as view-up direction. */
	//
	//glLoadIdentity();
	//

	//
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(100, 0, 0);
	glEnd();


	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 100, 0);
	glEnd();


	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 100);
	glEnd();
	
	glColor3f(1, 1, 1);
	float i = 500;
	while (i > -250) {
		glBegin(GL_QUADS);
		glVertex3f(i, 500, 100.0);
		glVertex3f(i, -500, 100.0);
		glVertex3f(i - 5, -500, 100.0);
		glVertex3f(i - 5, 500, 100.0);
		glEnd();
		i -= 20;
	}
	glPushMatrix();
	glColor3f(1, 0, 1);
	glTranslated(375,-375, -30);
	glRotated(angulo/3, 1, 1, 0);//Rota elipse
	glutWireSphere(100, 30, 30);//Crea esfera
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(-375, 0, -30);//Traslada elipse
	glRotated(-angulo/2, 1, 1, 0);//Rota elipse
	glScalef(1.2, .9, .6);//alarga la esfera
	glutWireSphere(100, 30, 30);//Crea la esfera
	glPopMatrix();

	glColor3f(0, 1, 1);
	glPushMatrix();
	glTranslatef(-375, 375, -1);
	glRotatef(-angulo/2, 0, 1, 1);
	glutWireCube(125);
	glPopMatrix();

	glutSwapBuffers();
}

void actualiza() {
	angulo += 5;
	glutPostRedisplay();


}

//void winReshapeFcn(GLint newWidth, GLint newHeight)
//{
//	glLoadIdentity();
//	glViewport(0, 0, newWidth, newHeight);
//	glMatrixMode(GL_PROJECTION);
//	gluPerspective(60, 1, 0.0, 200.0);
//	glMatrixMode(GL_MODELVIEW);
//	glClear(GL_COLOR_BUFFER_BIT);
//}

void main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Proyecto");
	angulo = 45;
	iniciar();
	glutDisplayFunc(Dibujo);
	/*glutMainLoop();*/
	
	glutIdleFunc(actualiza);
	glutMainLoop();
}
