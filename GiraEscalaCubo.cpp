#include <Windows.h>
#include "GL/glut.h"
#include <math.h>
#include <time.h>
#include "Metodos.h"


GLsizei winWidth = 1000, winHeight = 1000; // Initial display-window size.
int anguloEsf1[100], anguloEsf2[100];
float escalaEsf[100];
float escalaCub[100];
int anguloCub1[100], anguloCub2[100];
int anguloElip1[100], anguloElipf2[100];
float mover[100];
char tecla;

int a = 0, b=0;

boolean rota1 = false, escala1 = false, mueve1 = false, colorea1 = false, tranfiere1 = false;
boolean rota2 = false, escala2 = false, mueve2 = false, colorea2 = false, tranfiere2 = false;
boolean esfera = false, cubo = false, elipse = false;

int mouseX = 0, mouseY = 0;

char figura;
boolean click = false;

char e[] = "E        Escalar";
char m[] = "M       Mover";
char c[] = "C        Cambiar de color";
char r[] = "R        Rotar";
char t[] = "T        Transparente";
char esc[] = "ESC    Salir";



//void agregaAnguloEsf() {
//	for (int i = 0; i < a; i++) {
//		anguloEsf1[i] = rand() % 15;
//	}
//}

void agregaAnguloCub() {
	for (int i = 0; i < b; i++) {
		anguloCub1[i] = 1 + (rand() % 4);
	}
}

void escalarCub() {
	for (int i = 0; i < b; i++) {
		escalaCub[i] = 10 + (rand() % 200);
		escalaCub[i] = escalaCub[i] / 100;
	}
}

void eliminaAnguloCub() {
	for (int i = 0; i < b; i++) {
		anguloCub1[i] = 0;
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



ColorPT cEsf;
ColorPT cCub;
ColorPT cEli;
CoordPT cd1, cd2, cd3;



void pintaEsfera(ColorPT cl, CoordPT cd, int angulo, float escala ) {
	glPushMatrix();
	glColor3f(cl.r, cl.g, cl.b);
	glTranslated(cd.x2, cd.y2, cd.z2);
	glRotated(angulo, 1, 1, 0);
	glScalef(1*escala, 1*escala, 1*escala);
	glutSolidSphere(50, 100, 100);
	glPopMatrix();
}

void pintaEsferaInicio(ColorPT cl, CoordPT cd) {
	glPushMatrix();
	glColor3f(cl.r, cl.g, cl.b);
	glTranslated(cd.x2, cd.y2, cd.z2);
	glutSolidSphere(100, 100, 100);
	glPopMatrix();
}

//void pintaElipsoide(ColorPT cl, CoordPT cd) {
//	glPushMatrix();
//	glColor3f(cl.r, cl.g, cl.b);
//	glTranslated(cd.x2, cd.y2, cd.z2);
//	glRotated(angulo, 1, 1, 0);
//	glScalef(1.3, .7, .6);
//	glutSolidSphere(50, 100, 100);
//	glPopMatrix();
//}

//void pintaElipsoideInicio(ColorPT cl, CoordPT cd) {
//	glPushMatrix();
//	glColor3f(cl.r, cl.g, cl.b);
//	glTranslated(cd.x2, cd.y2, cd.z2);
//	glRotated(angulo, 1, 1, 0);
//	glScalef(1.3, .7, .6);
//	glutSolidSphere(90, 100, 100);
//	glPopMatrix();
//}

void pintaCubo(ColorPT cl, CoordPT cd, int angulo, float escala) {
	glPushMatrix();
	glColor3f(cl.r, cl.g, cl.b);
	glTranslated(cd.x2, cd.y2, cd.z2);
	glRotatef(angulo, 0, 1, 1);
	glScalef(1 * escala, 1 * escala, 1 * escala);
	glutSolidCube(100);
	glPopMatrix();
}

void pintaCuboInicio(ColorPT cl, CoordPT cd, int angulo) {
	glPushMatrix();
	glColor3f(cl.r, cl.g, cl.b);
	glTranslated(cd.x2, cd.y2, cd.z2);
	glRotatef(angulo, 0, 1, 1);
	glutSolidCube(155);
	glPopMatrix();
}

void pintaBotones() {
	CoordPT esf = CoordPT(375, 350, 100);
	CoordPT cub = CoordPT(375, 100, 100);
	CoordPT eli = CoordPT(375, -150, 100);
	pintaEsferaInicio(cEsf, esf);
	pintaCuboInicio(cCub, cub, 0);
	/*pintaElipsoideInicio(cEli, eli);*/
}

//CoordPT circulos[100];
//ColorPT colorCirculo[100];
//void AgregaCirculo() {
//	circulos[a] = randomCoord();
//	colorCirculo[a] = randomColor();
//	a = a + 1;
//	if (a == 100) {
//		a = 0;
//	}
//}
//
//void dibujaCirculos() {
//	for (int i = 0; i < a; i++) {
//		pintaEsfera(colorCirculo[i], circulos[i], anguloEsf2[i]);
//	}
//}


CoordPT cubos[100];
ColorPT colorCubo[100];
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
		pintaCubo(colorCubo[i], cubos[i], anguloCub2[i], escalaCub[i]);
	}
}


//CoordPT elipses[100];
//ColorPT colorElipse[100];
//int eli = 0;
//void AgregaElipse() {
//	elipses[eli] = randomCoord();
//	colorElipse[eli] = randomColor();
//	eli = eli + 1;
//	if (eli == 100) {
//		eli = 0;
//	}
//}
//
//void dibujaElipses() {
//	for (int i = 0; i < eli; i++) {
//		if (colEli) {
//			colorElipse[i] = randomColor();
//			colEli = false;
//		}
//		pintaElipsoide(colorElipse[i], elipses[i], true, mueveEli);
//	}
//}

void iniciar(void) {
	srand(time(NULL));
	glClearColor(0.8, 0.8, 0.8, 1);
	glOrtho(-500, 500, -500, 500, 0, 1000);
	gluLookAt(0, 0, 0, 0, 0, 100, 0, 1, 0);

	float ambiente[] = { 0.9, 0.9, 0.9, 1 };

	float posicion1[] = { -240, 240, 200, 1 };
	float difusion1[] = { 0.1, 0.1, 0.1, 1 };
	float especular1[] = { 0.1, 0.1, 0.1, 1 };

	for (int i = 0; i < 100; i++) {
		escalaEsf[i] = 1;
		escalaCub[i] = 1;
	}


	float posicion2[] = { -480, -240, 0, 1 };
	float difusion2[] = { 0.7, 0.7, 0.7, 1 };
	float especular2[] = { 0.7, 0.7, 0.7, 1 };

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_SMOOTH);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, posicion1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusion1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, especular1);
	/*glEnable(GL_LIGHT1);
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

void Dibujo(void) {
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	pintaBarras();
	pintaCajaTexto();
	pintaBotones();
	/*dibujaCirculos();*/
	dibujaCubos();
	//dibujaElipses();
	glutSwapBuffers();
}

void teclado(unsigned char tecla, int x4, int y4) {
	switch (tecla)
	{
	case 'e':
	case 'E':
		escala1 = true;
		rota1 = false;
		mueve1 = false;
		colorea1 = false;
		tranfiere1 = false;
		if (!escala2) {
			escala2 = true;
		}
		else {
			escala2 = false;
		}
		break;


	case 'm':
	case 'M':
		if (!mueve1) {
			mueve1 = true;
			rota1 = false;
			escala1 = false;
			colorea1 = false;
			tranfiere1 = false;
			if (!mueve2) {
				mueve2 = true;
			}
			else {
				mueve2 = false;
			}
		}
		else {
			mueve1 = false;
		}
		break;


	case 'c':
	case 'C':
		if (!colorea1) {
			colorea1 = true;
			rota1 = false;
			escala1 = false;
			mueve1 = false;
			tranfiere1 = false;
			if (!colorea2) {
				colorea2 = true;
			}
			else {
				colorea2 = false;
			}
		}
		else {
			colorea1 = false;
		}
		break;

	case 'r':
	case 'R':
		rota1 = true;
		colorea1 = false;
		escala1 = false;
		mueve1 = false;
		tranfiere1 = false;
		if (!rota2) {
			rota2 = true;
		}
		else {
			rota2 = false;
		}
		break;

	case 27:
		exit(0);
		break;
	}
}


void OnMouseClick(int button, int state, int x5, int y5) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		int mouseX = x5 - 125;
		int mouseY = y5 - 150;

		/*int d = sqrt((mouseX*mouseX) + (mouseY*mouseY));
		if (d < 100) {
			if (rota || escala || mueve || colorea || tranfiere) {
				if (rota) {
					agregaAnguloEsf();
				}
			}
			else {
				AgregaCirculo();
			}
		}*/
		double lado = 90 * sin(45);
		mouseX = x5;
		mouseY = y5;
		if (mouseX > (125 - lado) && mouseX < (125 + lado) && mouseY< (400 + lado) && mouseY>(400 - lado)) {
			if (rota1 || escala1 /*|| mueve1 || colorea1 || tranfiere1*/) {
				
				if (rota1) {
					if (rota2) {
						agregaAnguloCub();
						rota1 = false;
					}
					else {
						eliminaAnguloCub();
						rota1 = false;
					}
				}
				if (escala1) {
					escalarCub();
					escala1 = false;
					
				}
				
			}
			else {
				AgregaCubo();
			}
		}

		/*mouseX = x5 - 125;
		mouseY = y5 - 650;
		d = sqrt(((mouseX / 1.2)*(mouseX / 1.2)) + ((mouseY / 0.9)*(mouseY / 0.9)));
		if (d < 90) {
			if (rota || escala || mueve || colorea || tranfiere) {
				esfera = false;
				cubo = false;
				elipse = true;
			}
			else {
				AgregaElipse();
			}
		}*/
	}
}

boolean limite = false;
int dato1;
void actualiza() {
	/*if (cd1.z2 >= 900) {
		limite = true;
	}
	if (cd1.z2 <= 100) {
		limite = false;
	}
	if (limite){
		dato1 = -5;
	}
	else{
		dato1 = 5;
	}
	cd1.z2 += dato1;*/
/*
	if (esfera) {
		if (rota) {
			for (int i = 0; i < a; i++) {
				anguloEsf2[i] = anguloEsf2[i] + anguloEsf1[i];
			}
		}
		else {
			for (int i = 0; i < a; i++) {
				angulo2[i] = 0;
			}
		}
	}
	if (cubo) {
		if (rota) {
			for (int i = 0; i < a; i++) {
				angulo2[i] = angulo2[i] + angulo1[i];
			}
		}
		else {
			for (int i = 0; i < a; i++) {
				angulo2[i] = 0;
			}
		}
	}*/

	//for (int i = 0; i < a; i++) {
	//	anguloEsf2[i] = anguloEsf2[i] + anguloEsf1[i];
	//}

	for (int i = 0; i < b; i++) {
		anguloCub2[i] = anguloCub2[i] + anguloCub1[i];
	}

	glutPostRedisplay();
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Proyecto");
	/*angulo = 45;*/
	iniciar();
	glutDisplayFunc(Dibujo);
	glutIdleFunc(actualiza);
	glutKeyboardFunc(teclado);
	glutMouseFunc(OnMouseClick);
	glutMainLoop();
}