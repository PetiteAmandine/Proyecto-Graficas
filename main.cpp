#include <Windows.h>
#include "GL/glut.h"

GLsizei winWidth = 1000, winHeight = 1000; // Initial display-window size.
float angulo = 0, mover = 350;
char tecla;

struct ColorPT {
	double r, g, b;
	ColorPT() {}
	ColorPT(double x, double y, double z) : r(x), g(y), b(z) {}
	ColorPT operator + (const ColorPT &p) const { return ColorPT(r + p.r, g + p.g, b + p.b); }
	ColorPT operator - (const ColorPT &p) const { return ColorPT(r - p.r, g - p.g, b - p.b); }
	ColorPT operator * (double c) const { return ColorPT(r*c, g*c, b*c); }
	ColorPT operator / (double c) const { return ColorPT(r / c, g / c, b / c); }
};

struct CoordPT {
	double x, y, z;
	CoordPT() {}
	CoordPT(double a, double b, double c) : x(a), y(b), z(c) {}
	CoordPT operator + (const CoordPT &p) const { return CoordPT(x + p.x, y + p.y, z + p.z); }
	CoordPT operator - (const CoordPT &p) const { return CoordPT(x - p.x, y - p.y, z - p.z); }
	CoordPT operator * (double c) const { return CoordPT(x*c, y*c, z*c); }
	CoordPT operator / (double c) const { return CoordPT(x / c, y / c, z / c); }
};

ColorPT randomColor() {
	return ColorPT(rand()%256/255, rand()%256/255, rand()%256/255);
}

CoordPT randomCoord() {
	return CoordPT(rand() % 751 - 500, rand() % 751 - 500, rand() % 101);
}

void pintaBarras() {
	glColor3f(0, 0, 0);
	float i = -500;
	while (i < 250) {
		glBegin(GL_QUADS);
		glVertex3f(i, 500, 100.0);
		glVertex3f(i, -500, 100.0);
		glVertex3f(i - 5, -500, 100.0);
		glVertex3f(i - 5, 500, 100.0);
		glEnd();
		i += 20;
	}
}

void pintaEsfera(ColorPT cl, CoordPT cd) {
	glPushMatrix();
	glColor3f(cl.r, cl.g, cl.b);
	glTranslated(cd.x, cd.y, cd.z);
	//glRotated(angulo / 3, 1, 1, 0);
	glutWireSphere(100, 30, 30);
	glPopMatrix();
}

void pintaElipsoide(ColorPT cl, CoordPT cd) {
	glPushMatrix();
	glColor3f(cl.r, cl.g, cl.b);
	glTranslated(cd.x, cd.y, cd.z);
	//glRotated(angulo / 3, 1, 1, 0);
	glScalef(1.2, .9, .6);
	glutWireSphere(100, 30, 30);
	glPopMatrix();
}

void pintaCubo(ColorPT cl, CoordPT cd) {
	glPushMatrix();
	glColor3f(cl.r, cl.g, cl.b);
	glTranslated(cd.x, cd.y, cd.z);
	//glRotatef(-angulo / 2, 0, 1, 1);
	glutWireCube(125);
	glPopMatrix();
}

void pintaBotones() {
	ColorPT c = ColorPT(0, 0, 0);
	CoordPT esf = CoordPT(375, 300, 10);
	CoordPT cub = CoordPT(375, 0, 10);
	CoordPT eli = CoordPT(375, -300, 10);
	pintaEsfera(c, esf);
	pintaCubo(c, cub);
	pintaElipsoide(c, eli);
}

void iniciar(void)
{
	glClearColor(1, 1, 1, 1);
	glOrtho(-500, 500, -500, 500, 0, 400);
	gluLookAt(0, 0, 0, 0, 0, 100, 0, 1, 0);
}

void Dibujo(void) {
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	pintaBarras();
	pintaBotones();
	//Colores y coordenadas de ejemplo
	ColorPT cl;
	cl.r = 1;
	cl.g = 0;
	cl.b = 0;
	CoordPT cd;
	cd.x = 100;
	cd.y = 100;
	cd.z = 70;
	pintaEsfera(cl, cd);
	cl.r = 0;
	cl.g = 1;
	cl.b = 0;
	cd.x = -300;
	cd.y = 100;
	cd.z = 170;
	pintaElipsoide(cl, cd);
	glutSwapBuffers();
}

void teclado(unsigned char tecla, int x, int y) {
	switch (tecla)
	{
	case 'e':
	case 'E':
		tecla = 'E';
		break;


	case 'm':
	case 'M':
		tecla = 'M';
		break;


	case 'c':
	case 'C':
		tecla = 'M';
		break;

	case 'r':
	case 'R':
		tecla = 'M';
		break;

	case 27:
		exit(0);
		break;
	}
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

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Proyecto");
	angulo = 45;
	iniciar();
	glutDisplayFunc(Dibujo);
	glutIdleFunc(actualiza);
	glutKeyboardFunc(teclado);
	glutMainLoop();
}