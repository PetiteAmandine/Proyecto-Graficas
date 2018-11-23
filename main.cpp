#include <Windows.h>
#include "GL/glut.h"

GLsizei winWidth = 1000, winHeight = 1000; // Initial display-window size.
float angulo = 0, mover = 350;
char tecla;
char e[] = "E        Escalar";
char m[] = "M       Mover";
char c[] = "C        Cambiar de color";
char r[] = "R        Rotar";
char t[] = "T        Transparente";
char esc[] = "ESC    Salir";

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

void print(int x, int y, int z, char *string) {
	//set the position of the text in the window
	glRasterPos3f(x, y, z);
	//get the length of the string to display
	int len = (int)strlen(string);
	//loop to display character by character
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
}

void pintaBarras() {
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(250, 490, 400.0);
	glVertex3f(250, -250, 400.0);
	glVertex3f(-490, -250, 400.0);
	glVertex3f(-490, 490, 400.0);
	glColor3f(1, 1, 1);
	glVertex3f(240, 480, 399.0);
	glVertex3f(240, -240, 399.0);
	glVertex3f(-480, -240, 399.0);
	glVertex3f(-480, 480, 399.0);
	glEnd();
	glColor3f(0, 0, 0);
	float i = -460;
	while (i <= 230) {
		glBegin(GL_QUADS);
		glVertex3f(i, 490, 100.0);
		glVertex3f(i, -250, 100.0);
		glVertex3f(i - 10, -250, 100.0);
		glVertex3f(i - 10, 490, 100.0);
		glEnd();
		i += 23;
	}
}

void pintaCajaTexto() {
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(250, -450, 400.0);
	glVertex3f(250, -300, 400.0);
	glVertex3f(-490, -300, 400.0);
	glVertex3f(-490, -450, 400.0);
	glColor3f(1, 1, 1);
	glVertex3f(245, -445, 399.0);
	glVertex3f(245, -305, 399.0);
	glVertex3f(-485, -305, 399.0);
	glVertex3f(-485, -445, 399.0);
	glEnd();
	glColor3i(0, -0, 0);
	print(200, -350, 10, e);
	print(200, -385, 10, m);
	print(200, -420, 10, c);
	print(-200, -350, 10, r);
	print(-200, -385, 10, t);
	print(-200, -420, 10, esc);
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
	glutWireSphere(90, 30, 30);
	glPopMatrix();
}

void pintaCubo(ColorPT cl, CoordPT cd) {
	glPushMatrix();
	glColor3f(cl.r, cl.g, cl.b);
	glTranslated(cd.x, cd.y, cd.z);
	//glRotatef(-angulo / 3, 0, 1, 1);
	glutWireCube(155);
	glPopMatrix();
}

void pintaBotones() {
	ColorPT c = ColorPT(0, 0, 0);
	CoordPT esf = CoordPT(375, 350, 10);
	CoordPT cub = CoordPT(375, 100, 10);
	CoordPT eli = CoordPT(375, -150, 10);
	pintaEsfera(c, esf);
	pintaCubo(c, cub);
	pintaElipsoide(c, eli);
}

void iniciar(void)
{
	//glClearColor(1, 1, 1, 1);
	glClearColor(0.8, 0.8, 0.8, 1);
	glOrtho(-500, 500, -500, 500, 0, 400);
	gluLookAt(0, 0, 0, 0, 0, 100, 0, 1, 0);
}

void Dibujo(void) {
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	pintaBarras();
	pintaCajaTexto();
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
	cl.r = 0;
	cl.g = 0;
	cl.b = 1;
	cd.x = -100;
	cd.y = 300;
	cd.z = 100;
	pintaCubo(cl, cd);
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