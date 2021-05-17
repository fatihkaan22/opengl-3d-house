#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

enum Color {WHITE, BROWN, ORANGE, GREY, BLUE, DARK_GREY, YELLOW, GREEN};

// translation
float X = 0, Y = 0, Z = 0;
// rotation
float I = 0, J = 0, K = 0;
// scale
float SCALE = 1;

void applyTranslationRotation() {
  glTranslatef(X, Y, Z);
  glRotatef(I, 1, 0, 0);
  glRotatef(J, 0, 1, 0);
  glRotatef(K, 0, 0, 1);
}

void nextColor(Color c) {
	switch(c) {
		case WHITE:
			glColor3f(0.90, 0.90, 0.90);
			break;
		case BROWN:
			glColor3f(0.45, 0.35, 0.25);
			break;
		case GREY:
			glColor3f(0.8, 0.8, 0.8);
			break;
		case DARK_GREY:
			glColor3f(0.4, 0.4, 0.4);
			break;
		case BLUE:
			glColor3f(0.6, 0.75, 0.85);
			break;
		case ORANGE:
			glColor3f(0.75, 0.25, 0);
			break;
		case YELLOW:
			glColor3f(1, 1, 0);
			break;
		case GREEN:
			glColor3f(0, 0.5, 0);
			break;
	}
}

// glut tutorialindaki pencre boyut degisimlerine perspective ayarlama
void changeSize(int w, int h) {
  if (h == 0)
    h = 1;
  float ratio = w * 1.0 / h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, w, h);
  gluPerspective(45.0f, ratio, 0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
}

void drawCube(float x, float y, float z, float length) {
  GLfloat h = length * 0.5f;

  GLfloat vertices[] = {
      // ön yüz
      x + h, y + h, z + h,
      x + h, y - h, z + h,
      x - h, y - h, z + h,
      x - h, y + h, z + h,
      // arka yüz
      x + h, y + h, z - h,
      x + h, y - h, z - h,
      x - h, y - h, z - h,
      x - h, y + h, z - h,
      // sol yüz
      x - h, y - h, z + h,
      x - h, y + h, z + h,
      x - h, y + h, z - h,
      x - h, y - h, z - h,
      // sağ yüz
      x + h, y - h, z + h,
      x + h, y + h, z + h,
      x + h, y + h, z - h,
      x + h, y - h, z - h,
      // üst yüz
      x - h, y + h, z + h,
      x - h, y + h, z - h,
      x + h, y + h, z - h,
      x + h, y + h, z + h,
      // alt yüz // gerek yok
      /* x - h, y - h, z + h, */
      /* x - h, y - h, z - h, */
      /* x + h, y - h, z - h, */
      /* x + h, y - h, z + h, */
  };

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices);

  glDrawArrays(GL_QUADS, 0, 5 * 4);
  glDisableClientState(GL_VERTEX_ARRAY);
}

// position: x,y,z
// en: b
// boy: l
// yükseklik: h
void drawRoof(float x, float y, float z, 
		float b, float l, float h) {

	// çatının çıkıntıları için 0.5 yerine 0.55 kullanıldı
	float bh = b * 0.55;
	float lh = l * 0.55;
	float hh = h * 0.55;

  GLfloat vertices[] = {
		// dörtgen sol yüz
		x+lh, y+hh, z,
		x+lh, y-hh, z+bh,
		x-lh, y-hh, z+bh,
		x-lh, y+hh, z,
		// dörtgen sağ yüz
		x+lh, y+hh, z,
		x+lh, y-hh, z-bh,
		x-lh, y-hh, z-bh,
		x-lh, y+hh, z,
		/* // dörtgen alt: çizmeye gerek yok */
		/* x+lh, y-hh, z+bh, */
		/* x+lh, y-hh, z-bh, */
		/* x-lh, y-hh, z-bh, */
		/* x-lh, y-hh, z+bh, */
	};

	nextColor(ORANGE);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glDrawArrays(GL_QUADS, 0, 8);

	// üçgenler duvarlara bitişik olmalı
	lh = l * 0.5;

	GLfloat triangles[] {
		// üçgen ön yüz
		x+lh, y+hh, z,
		x+lh, y-hh, z-bh,
		x+lh, y-hh, z+bh,
		// üçgen arka yüz
		x-lh, y+hh, z,
		x-lh, y-hh, z+bh,
		x-lh, y-hh, z-bh,
	};

	nextColor(WHITE);
  glVertexPointer(3, GL_FLOAT, 0, triangles);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glDisableClientState(GL_VERTEX_ARRAY);
}

// k: scale
// i: x ekseni transformasyonu
// j: z ekseni transformasyonu
void drawWindow(float k, int i, int j) {
  glPushMatrix();
	applyTranslationRotation();
	nextColor(BLUE);
  glTranslatef(0.4*k*i, 0, j*k/2+0.01*j);
	glRectf(-0.2*k,-0.2*k,0.2*k,0.2*k);
  glPopMatrix();
}

// k evin scale'i
void drawHouse(const float k) {

#ifdef DEBUG
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  cout << "X:" << X << " Y:" << Y << " Z:" << Z << endl;
  cout << "I:" << I << " J:" << J << " K:" << K << endl;
  cout << "-----------" << endl;
#endif

  glPushMatrix();
  applyTranslationRotation();
  nextColor(WHITE);
  drawCube(-0.5 * k, 0, 0, 1 * k);
  drawCube(0.5 * k, 0, 0, 1 * k);
  drawRoof(0, 0.7 * k, 0, 1.2 * k, 2 * k, 0.5 * k);
  // baca
  nextColor(GREY);
  drawCube(0.5 * k, 0.65 * k, 0.3 * k, 0.15 * k);
  drawCube(0.5 * k, 0.8 * k, 0.3 * k, 0.15 * k);
  // kapı
  nextColor(BROWN);
  glRotatef(90, 0, k, 0);
  glTranslatef(0, 0, k + 0.01);
  glRectf(-0.15 * k, -0.5 * k, 0.15 * k, 0.1 * k);

  nextColor(YELLOW);
  glTranslatef(-0.1 * k, -0.2 * k, 0.008);
  glutSolidSphere(0.02f * k, 10, 10);

  glPopMatrix();

  // pencereler
  drawWindow(k, 1, 1);
  drawWindow(k, -1, 1);
  drawWindow(k, 1, -1);
  drawWindow(k, -1, -1);

  // garaj
  glPushMatrix();
  applyTranslationRotation();
  nextColor(DARK_GREY);
  glRotatef(90, 0, k, 0);
  glTranslatef(0, 0, -k - 0.01);
  glRectf(-0.35 * k, -0.5 * k, 0.35 * k, 0.2 * k);
  glPopMatrix();
}

void renderScene(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // reset transformations
  glLoadIdentity();
  gluLookAt(6, 3, 2, // kameranın konumu
						0, 0, 0, // kameranın nereye baktığı
						0, 1, 0);

#ifdef DEBUG
	// time
  float t = (float)glutGet(GLUT_ELAPSED_TIME) / 800;
  glLoadIdentity();
  gluLookAt(5.0 * cos(t), 2.0 * cos(2*t), 5.0 * sin(t), 
            0, 0, 0,                         
            0, 1, 0);
#endif

  drawHouse(SCALE);

  // yer
	nextColor(GREEN);
  glBegin(GL_QUADS);
  	glVertex3f(-5, -0.5, -5);
  	glVertex3f(-5, -0.5,  5);
  	glVertex3f( 5, -0.5,  5);
  	glVertex3f( 5, -0.5, -5);
  glEnd();

  glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
  float threshold = 0.1;
  switch (key) {
  case 'q':
  case 27: // escape
    exit(0);
    break;
  // vim keybindings translation için
  case 'h': // sol
    Z += threshold;
    break;
  case 'l': // sağ
    Z -= threshold;
    break;
  case 'k': // ön
    X -= threshold;
    break;
  case 'j': // arka
    X += threshold;
    break;
  case 'K': // yukarı
    Y += threshold;
    break;
  case 'J': // aşağı
    Y -= threshold;
    break;
  case '+':
    SCALE += threshold;
    break;
  case '-':
    if (SCALE > threshold)
      SCALE -= threshold;
    break;
  }
}

void processSpecialKeys(int key, int x, int y) {
  float threshold = 7.5;

  if (glutGetModifiers() & GLUT_ACTIVE_SHIFT) {
    switch (key) {
    case GLUT_KEY_LEFT:
      I += threshold;
      break;
    case GLUT_KEY_RIGHT:
      I -= threshold;
      break;
    }
    return;
  }

  switch (key) {
  case GLUT_KEY_LEFT:
    J -= threshold;
    break;
  case GLUT_KEY_RIGHT:
    J += threshold;
    break;
  case GLUT_KEY_UP:
    K += threshold;
    break;
  case GLUT_KEY_DOWN:
    K -= threshold;
    break;
  }
}

int main(int argc, char **argv) {
  int w = 1280;
  int h = 720;

  // init GLUT and create window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  /* glutInitWindowPosition(100,100); */
  glutInitWindowSize(w, h);
  glutCreateWindow("GTU CSE461");

  // register callbacks
  glutDisplayFunc(renderScene);
  glutReshapeFunc(changeSize);
  glutIdleFunc(renderScene);
  glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

  // arkada çizilenleri arkaya render etmek için
  glEnable(GL_DEPTH_TEST);

  glutMainLoop();
  return 1;
}
