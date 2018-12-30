#include "kamera.h"
//#include "koor_sistem.h"
//#include "osvetljenje.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

extern int indikator_kvadrat;
extern int brojac;
extern float animation_clip_cone;
extern int start_cone;
extern double nova_kamera;


double translacija_x;
int indikator_kamera;
int ind;
float prva_prava;

void my_obj();
void delete_cone();
void draw_eyes();
void draw_lines();
void draw_square();
