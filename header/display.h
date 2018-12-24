#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "kamera.h"
#include "osvetljenje.h"
#include "moji_objekti.h"
#include "koor_sistem.h"

extern float move_camera_circle;
extern double translacija_x;

int brojac;
int timer_active;
float animation_clip_cone;
int start_line;
int start_cone;

void on_keyboard(unsigned char, int, int);
void on_display(void);
void on_timer(int);
void init_main(int*, char**);

