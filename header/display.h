#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include "kamera.h"
#include "osvetljenje.h"
#include "moji_objekti.h"
#include "koor_sistem.h"
#include "image.h"

extern float move_camera_circle;
extern double translacija_x;
extern int indikator_kamera;
extern double granica_theta;
extern float prva_prava; 
extern int ind;
extern int indikator_prozirnost;
extern float radijus;
extern GLUquadricObj* sfera_obj2;
extern GLuint tekstura_sfere2;

double uvecaj_theta;
int indikator_kvadrat;
int brojac;
int timer_active;
float animation_clip_cone;
int start_line;
int start_cone;

void on_keyboard(unsigned char, int, int);
void on_display(void);
void on_timer(int);
void init_main(int*, char**);
void uvedi_teksture();
void draw_name();

#endif //DISPLAY_H_
