#include "kamera.h"
#include "SOIL.h"
//#include "koor_sistem.h"
//#include "osvetljenje.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>


#define TEKSTURA_SFERE "teksture/as.png"
#define TEKSTURA_SFERE2 "teksture/ra.png"
#define FILENAME0 "teksture/se.bmp"
#define FILENAME1 "teksture/blusky.bmp"
#define FILENAME2 "teksture/blusky.bmp"
#define TEKSTURA_KOCKE "teksture/1.png"


extern int indikator_kvadrat;
extern int brojac;
extern float animation_clip_cone;
extern int start_cone;
extern double nova_kamera;
extern float MIN_THETA_CIRCLE;
double translacija_x;

float prozirnost;
int indikator_kamera;
int ind;
float prva_prava;
float radijus;

GLuint tekstura_sfere;
GLuint tekstura_sfere2;
GLuint tekstura_kocke;
GLuint names[5];
GLUquadricObj* sfera_obj2;

void my_obj();
void delete_cone();
void draw_eyes();
void draw_lines();
void draw_square();
void piramida(float);
void kocke(float);
