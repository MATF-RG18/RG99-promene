#ifndef KAMERA_H
#define KAMERA_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

//#define M_PI 3.141592653589793

#define RADIUS 9
#define PHI 0.78
#define THETA 0.3

#define MAX_R 16
#define MIN_R 1
#define MAX_PHI 2*M_PI
#define MIN_PHI 0
#define MAX_THETA M_PI/2
#define MIN_THETA -M_PI/2


#define DR 0.05
#define DPHI M_PI/90
#define DTHETA M_PI/90

double granica_theta;
float MIN_THETA_CIRCLE;
extern double uvecaj_theta;
extern double translacija_x;
extern int indikator_kamera;
extern int ind;
extern float prva_prava;
struct kamera
{
    double x,y,z;
    double rad, phi, theta;
    double dr, dphi,dtheta;
    
}kamera;

float move_camera_circle;
double nova_kamera;

void convert_decart(void);
void on_reshape(int, int);
void init(void);
void look_left(void);
void look_right(void);
void look_up(void);
void look_down(void);
void zoom_in(void);
void zoom_out(void);
void camera_init(void);


#endif //KAMERA_H
