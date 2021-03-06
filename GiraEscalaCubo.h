#pragma once
struct ColorPT {
	double r, g, b;
	ColorPT() {}
	ColorPT(double x1, double y1, double z1) : r(x1), g(y1), b(z1) {}
	ColorPT operator + (const ColorPT &p) const { return ColorPT(r + p.r, g + p.g, b + p.b); }
	ColorPT operator - (const ColorPT &p) const { return ColorPT(r - p.r, g - p.g, b - p.b); }
	ColorPT operator * (double c) const { return ColorPT(r*c, g*c, b*c); }
	ColorPT operator / (double c) const { return ColorPT(r / c, g / c, b / c); }
};

struct CoordPT {
	double x2, y2, z2;
	CoordPT() {}
	CoordPT(double a, double b, double c) : x2(a), y2(b), z2(c) {}
	CoordPT operator + (const CoordPT &p) const { return CoordPT(x2 + p.x2, y2 + p.y2, z2 + p.z2); }
	CoordPT operator - (const CoordPT &p) const { return CoordPT(x2 - p.x2, y2 - p.y2, z2 - p.z2); }
	CoordPT operator * (double c) const { return CoordPT(x2*c, y2*c, z2*c); }
	CoordPT operator / (double c) const { return CoordPT(x2 / c, y2 / c, z2 / c); }
};


ColorPT randomColor() {
	return ColorPT((rand() % 256) / 255.0, (rand() % 256) / 255.0, (rand() % 256) / 255.0);
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

void print(int x3, int y3, int z3, char *string) {
	//set the position of the text in the window
	glRasterPos3f(x3, y3, z3);
	//get the length of the string to display
	int len = (int)strlen(string);
	//loop to display character by character
	for (int i1 = 0; i1 < len; i1++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i1]);
}


void agregaAngulo(int angulo[], int a) {
	for (int i = 0; i < a; i++) {
		angulo[i] = rand() % 15;
	}
}

int eliminaAngulo(int angulo[], int a) {
	for (int i = 0; i < a; i++) {
		angulo[i] = 0;
	}
	return a = 0;
}