#ifndef OKO_H
#define OKO_H

#include <GL/glut.h>
#include <math.h>
#include "kliker.h"

// Opis kamere
// Pocetni sferni parametri
#define OKO_RAD 10
#define OKO_PHI 0
#define OKO_THETA (M_PI/6)

// Promena parametara
#define OKO_RAD_D 0.03
#define OKO_PHI_D (M_PI/450)
#define OKO_THETA_D (M_PI/450)

// Minimum parametara
#define OKO_RAD_MIN 3
#define OKO_PHI_MIN -M_PI
#define OKO_THETA_MIN 0

// Maksimum parametara
#define OKO_RAD_MAX 20
#define OKO_PHI_MAX M_PI
#define OKO_THETA_MAX (M_PI/2-M_PI/450)

// Pun krug za azimut
#define OKO_PHI_POM (2*M_PI)

// Razlike, resetovanje
#define RAZ_POC 0
#define RES_KRAJ 1

/* Struktura koja enkapsulira kliker
   sa centrom x, y, z i radijusom r */
extern struct kliker kliker;

/* Struktura koja enkapsulira oko/kameru,
   predstavljeno sfernim koordinatama */
struct oko{
    // Poluprecnik i promena
    GLdouble r, d_r;
    
    // Azimutni ugao i promena
    GLdouble phi, d_phi;
    
    // Polarni ugao i promena
    GLdouble theta, d_theta;
    
    // Dekartove koordinate
    GLdouble x, y, z;
} oko;

/* Struktura koja enkapsulira razlike
   izmedju pocetnog i trenutnog stanja oka */
struct razlika{
    int r, phi, theta;
} razlika;

// Deklaracije fja za oko/kameru
void napravi_oko(void);
void popravi_oko(void);
int resetuj_oko(void);
void oko_levo(void);
void oko_desno(void);
void oko_gore(void);
void oko_dole(void);
void oko_napred(void);
void oko_nazad(void);

#endif // OKO_H
