#ifndef KLIKER_H
#define KLIKER_H

#include <GL/glut.h>
#include <math.h>
#include "oko.h"

// Opis klikera
#define KLIK_CENT 0
#define KLIK_RAD 1
#define KLIK_PREC 22
#define GLATKOST 100
#define POMERAJ 20

/* Struktura koja enkapsulira oko/kameru
   sa javnim koordinatama x, y, z */
extern struct oko oko;

// Struktura koja enkapsulira kliker
struct kliker{
    // Koordinate centra
    GLdouble x, y, z;
    
    // Poluprecnik
    GLdouble r;
    
    // Preciznost
    GLdouble prec;
} kliker;

// Deklaracije fja za kliker
void napravi_kliker(void);
void postavi_kliker(void);
void kliker_napred(void);
void kliker_nazad(void);

#endif // KLIKER_H
