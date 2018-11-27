#include <Windows.h>
#include "GL/glut.h"
#include <math.h>
#include <time.h>

GLsizei winWidth = 1000, winHeight = 1000; // Initial display-window size.
float angulo = 0, mover = 350;
char tecla;
char e[] = "E        Escalar";
char m[] = "M       Mover";
char c[] = "C        Cambiar de color";
char r[] = "R        Rotar";
char t[] = "T        Transparente";
char esc[] = "ESC    Salir";

boolean escalaEsf = false, mueveEsf = false, colEsf = false, transEsf = false;
boolean rotaCub = false, escalaCub = false, mueveCub = false, colCub = false, transCub = false;
boolean rotaEli = false, escalaEli = false, mueveEli = false, colEli = false, transEli = false;

int mouseX = 0, mouseY = 0;

char figura;
boolean click = false;


struct ColorPT {
	double r, g, b;
	ColorPT() {}
	ColorPT(double x1, double y1, double z1) : r(x1), g(y1), b(z1) {}
	ColorPT operator + (const ColorPT &p) const { return ColorPT(r + p.r, g + p.g, b + p.b); }
	ColorPT operator - (const ColorPT &p) const { return ColorPT(r - p.r, g - p.g, b - p.b); }
	ColorPT operator * (double c) const { return ColorPT(r*c, g*c, b*c); }
	ColorPT operator / (double c) const { return ColorPT(r / c, g / c, b / c); }
};

ColorPT cEsf;
ColorPT cCub;
ColorPT cEli;

struct CoordPT {
	double x2, y2, z2;
	CoordPT() {}
	CoordPT(double a, double b, double c) : x2(a), y2(b), z2(c) {}
	CoordPT operator + (const CoordPT &p) const { return CoordPT(x2 + p.x2, y2 + p.y2, z2 + p.z2); }
	CoordPT operator - (const CoordPT &p) const { return CoordPT(x2 - p.x2, y2 - p.y2, z2 - p.z2); }
	CoordPT operator * (double c) const { return CoordPT(x2*c, y2*c, z2*c); }
	CoordPT operator / (double c) const { return CoordPT(x2 / c, y2 / c, z2 / c); }
};

CoordPT cd1, cd2, cd3;

ColorPT randomColor() {
	return ColorPT((rand() % 256)/255.0, (rand() % 256)/255.0, (rand() % 256)/255.0);
}

CoordPT randomCoord() {
	int x = rand() % 730;
	int y = rand() % 730;
	int z = rand() % 800;
	x = x - 480;
	y = y - 250;
	z = z + 100;
	if (x < 0) {
		x = x + 100;
	}
	else {
		x = x - 100;
	}


	if (y < 0) {
		y = y + 100;
	}
	else {
		y = y - 100;
	}

	return CoordPT(x, y, z);
}


void print(int x3, int y3, int z3, char *string) {
	//set the position of the text in the window
	glRasterPos3f(x3, y3, z3);
	//get the length of the string to display
	int len = (int)strlen(string);
	//loop to display character by character
	for (int i1 = 0; i1 < len; i1++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i1]);
}

void pintaBarras() {
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(200, 490, 1000.0);
	glVertex3f(250, -250, 1000.0);
	glVertex3f(-490, -250, 1000.0);
	glVertex3f(-490, 490, 1000.0);
	glColor3f(0, 0, 0);
	glVertex3f(240, 480, 999.0);
	glVertex3f(240, -240, 999.0);
	glVertex3f(-480, -240, 999.0);
	glVertex3f(-480, 480, 999.0);
	glEnd();
	glColor3f(1, 1, 1);
	float i2 = -460;
	while (i2 <= 230) {
		glBegin(GL_QUADS);
		glVertex3f(i2, 480, 500.0);
		glVertex3f(i2, -240, 500.0);
		glVertex3f(i2 - 10, -240, 500.0);
		glVertex3f(i2 - 10, 480, 500.0);
		glEnd();
		i2 += 23;
	}
}

void pintaCajaTexto() {
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(250, -450, 2.0);
	glVertex3f(250, -300, 2.0);
	glVertex3f(-490, -300, 2.0);
	glVertex3f(-490, -450, 2.0);
	glColor3f(1, 1, 1);
	glVertex3f(245, -445, 1.0);
	glVertex3f(245, -305, 1.0);
	glVertex3f(-485, -305, 1.0);
	glVertex3f(-485, -445, 1.0);
	glEnd();
	glColor3i(0, 0, 0);
	print(200, -350, 0, e);
	print(200, -385, 0, m);
	print(200, -420, 0, c);
	print(-200, -350, 0, r);
	print(-200, -385, 0, t);
	print(-200, -420, 0, esc);
}

void pintaEsfera(ColorPT cl, CoordPT cd, bool mov) {
	glPushMatrix();
	glColor3f(cl.r, cl.g, cl.b);
	glTranslated(cd.x2, cd.y2, cd.z2);
	glutSolidSphere(100, 100, 100);
	glPopMatrix();
}

void pintaElipsoide(ColorPT cl, CoordPT cd, bool rota, bool mov) {
	glPushMatrix();
	glColor3f(cl.r, cl.g, cl.b);
	glTranslated(cd.x2, cd.y2, cd.z2);
	if (rota)
		glRotated(angulo / 3, 1, 1, 0);
	glScalef(1.3, .7, .6);
	glutSolidSphere(90, 100, 100);
	glPopMatrix();
}

void pintaCubo(ColorPT cl, CoordPT cd, bool rota, bool mov) {
	glPushMatrix();
	glColor3f(cl.r, cl.g, cl.b);
	glTranslated(cd.x2, cd.y2, cd.z2);
	if (rota)
		glRotatef(angulo, 0, 1, 1);
	glutSolidCube(155);
	glPopMatrix();
}

void pintaBotones() {
	CoordPT esf = CoordPT(375, 350, 50);
	CoordPT cub = CoordPT(375, 100, 50);
	CoordPT eli = CoordPT(375, -150, 50);
	pintaEsfera(cEsf, esf, false);
	pintaCubo(cCub, cub, false, false);
	pintaElipsoide(cEli, eli, false, false);
}

void iniciar(void) {
	srand(time(NULL));
	glClearColor(0.8, 0.8, 0.8, 1);
	glOrtho(-500, 500, -500, 500, 0, 1000);
	gluLookAt(0, 0, 0, 0, 0, 100, 0, 1, 0);

	float ambiente[] = { 0.9, 0.9, 0.9, 1 };

	float posicion1[] = { -480, 480, 0, 1 };
	float difusion1[] = { 0.7, 0.7, 0.7, 1 };
	float especular1[] = { 0.7, 0.7, 0.7, 1 };


	float posicion2[] = { -480, -240, 0, 1 };
	float difusion2[] = { 0.7, 0.7, 0.7, 1 };
	float especular2[] = { 0.7, 0.7, 0.7, 1 };

	/*glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_SMOOTH);

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, posicion1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusion1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, especular1);

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_POSITION, posicion2);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusion2);
	glLightfv(GL_LIGHT0, GL_SPECULAR, especular2);*/

	cEsf = { 0.9568, 0.298, 0.2392 };
	cCub = { 0.4274, 0.8, 0.102 };
	cEli = { 0.102, 0.6941, 0.8 };

	cd1.x2 = -300;
	cd1.y2 = 100;
	cd1.z2 = 10;
	cd2.x2 = 100;
	cd2.y2 = 100;
	cd2.z2 = 70;
	cd3.x2 = -100;
	cd3.y2 = 300;
	cd3.z2 = 100;
}

CoordPT circulos[100];
ColorPT colorCirculo[100];
int a = 0;
void AgregaCirculo() {
	circulos[a] = randomCoord();
	colorCirculo[a] = randomColor();
	a = a + 1;
	if (a == 100) {
		a = 0;
	}
}

void dibujaCirculos() {
	for (int i = 0; i < a; i++) {
		if (colEsf) {
			colorCirculo[i] = randomColor();
			colEsf = false;
		}
		pintaEsfera(colorCirculo[i], circulos[i], mueveEsf);
	}
}


CoordPT cubos[100];
ColorPT colorCubo[100];
int b = 0;
void AgregaCubo() {
	cubos[b] = randomCoord();
	colorCubo[b] = randomColor();
	b = b + 1;
	if (b == 100) {
		b = 0;
	}
}

void dibujaCubos() {
	for (int i = 0; i < b; i++) {
		if (colCub) {
			colorCubo[i] = randomColor();
			colCub = false;
		}
		pintaCubo(colorCubo[i], cubos[i], rotaCub, mueveCub);
	}
}


CoordPT elipses[100];
ColorPT colorElipse[100];
int eli = 0;
void AgregaElipse() {
	elipses[eli] = randomCoord();
	colorElipse[eli] = randomColor();
	eli = eli + 1;
	if (eli == 100) {
		eli = 0;
	}
}

void dibujaElipses() {
	for (int i = 0; i < eli; i++) {
		if (colEli) {
			colorElipse[i] = randomColor();
			colEli = false;
		}
		pintaElipsoide(colorElipse[i], elipses[i], true, mueveEli);
	}
}


void Dibujo(void) {
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	pintaBarras();
	pintaCajaTexto();
	pintaBotones();
	dibujaCirculos();
	dibujaCubos();
	dibujaElipses();
	glutSwapBuffers();
}

void teclado(unsigned char tecla, int x4, int y4) {
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

boolean limite = false;
int dato1;
void actualiza() {
	angulo += 0.5;
	if (cd1.z2 >= 900) {
		limite = true;
	}
	if (cd1.z2 <= 100) {
		limite = false;
	}
	if (limite)
		dato1 = -5;
	else
		dato1 = 5;
	cd1.z2 += dato1;
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


void OnMouseClick(int button, int state, int x5, int y5) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		int mouseX = x5 - 125;
		int mouseY = y5 - 150;
		
		int d = sqrt((mouseX*mouseX) + (mouseY*mouseY));
		if (d < 100) {
			AgregaCirculo();
		}
		double lado = 90 * sin(45);
		mouseX = x5;
		mouseY = y5;
		if (mouseX > (125 - lado) && mouseX < (125 + lado) && mouseY< (400 + lado) && mouseY>(400 - lado)) {
			AgregaCubo();
		}

		mouseX = x5 - 125;
		mouseY = y5 - 650;
		d = sqrt(((mouseX / 1.2)*(mouseX / 1.2)) + ((mouseY / 0.9)*(mouseY / 0.9)));
		if (d < 90) {
			AgregaElipse();
		}
	}
}

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
	glutMouseFunc(OnMouseClick);
	glutMainLoop();
}