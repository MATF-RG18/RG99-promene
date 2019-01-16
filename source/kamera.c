#include "../header/kamera.h"

float move_camera_circle = 0;
double nova_kamera = 0;
float MIN_THETA_CIRCLE=0.25;

/*Funkcija za prevodjenje sfernih u Dekartove koordinate*/
void convert_decart(void)
{
    kamera.x = kamera.rad * cos(kamera.theta) * cos(kamera.phi);
    kamera.y = kamera.rad * cos(kamera.theta) * sin(kamera.phi);
    kamera.z = kamera.rad * sin(kamera.theta);
}

void on_reshape(int width, int height)
{
    /*Postavljanje projekcije pogleda na scenu*/
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 300);
}

void init(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_NORMALIZE); 
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    convert_decart();
    
    /*Provera indikatora omogucava da upravljamo kamerom*/
    if (indikator_kamera==1){
        
        /*Rotiramo se dok ne dodjemo do pozicije gde je y koordinata jednaka nuli, jer 
         zelimo da posmatramo dogadjaj iz druge pozicije*/
        if (kamera.phi>0){
            kamera.phi -= translacija_x;
            convert_decart();
            gluLookAt(kamera.x, kamera.y, kamera.z, 0, 0, 0, 0, 0, 1);
        }
        else{
            kamera.phi = 0;
            convert_decart();
            gluLookAt(kamera.x, kamera.y, kamera.z, 0, 0, 0, 0, 0, 1);
        }
    }
    else if (indikator_kamera==2){
        /*Izdizemo se u odnosu na Oxy ravan*/
        if (kamera.theta<M_PI/3-M_PI/10){
            kamera.theta +=M_PI/70;
            convert_decart();
            gluLookAt(kamera.x, kamera.y, kamera.z, 0, 0, 0, 0, 0, 1);
        }
        else if (kamera.theta>=M_PI/3-M_PI/10){
            /*Nova kamera omogucava da ostanemo na visini do koje je kamera stigla*/
            kamera.theta = nova_kamera = kamera.theta;
            convert_decart();
            gluLookAt(kamera.x, kamera.y, kamera.z, 0, 0, 0, 0, 0, 1);
            /*Obavestavamo da je kamera dostigla svoju zeljenu poziciju*/
            ind = 0;
        }
    }
    else{
        gluLookAt(kamera.x, kamera.y, kamera.z, 0, 0, 0, 0, 0, 1);
    }    
}
void camera_init(void)
{
    kamera.rad = RADIUS; kamera.phi = PHI; kamera.theta = THETA;
    kamera.dr = DR; kamera.dphi = DPHI; kamera.dtheta = DTHETA;
}

void look_left(void)
{
    /* Dekrementira se ugao phi i ponovo iscrtava scena. Ovaj
         * ugao se odrzava u intervalu [0,2*Pi] stepeni.
         */
    kamera.phi -= kamera.dphi;
    if (kamera.phi > MAX_PHI) {
        kamera.phi -= MAX_PHI;
    } else if (kamera.phi < 0) {
        kamera.phi += MAX_PHI;
    }
}

void look_right()
{
    /* Inkrementira se ugao phi i ponovo iscrtava scena. Ovaj
         * ugao se odrzava u intervalu [0,2*Pi] stepeni.
         */
    kamera.phi += kamera.dphi;
    if (kamera.phi > MAX_PHI) {
        kamera.phi -= MAX_PHI;
    } else if (kamera.phi < 0) {
        kamera.phi += MAX_PHI;
    }
}

void look_down()
{
     /* Dekrementira se ugao theta i ponovo iscrtava scena. Ovaj
         * ugao se odrzava u intervalu [-89,89] stepeni.
         */
    kamera.theta -= kamera.dtheta;
    if (kamera.theta < MIN_THETA) {
        kamera.theta = MIN_THETA;
    }
    else if(kamera.theta < MIN_THETA_CIRCLE )
    {
        kamera.theta = MIN_THETA_CIRCLE;
    }
}

void look_up()
{
    /*
         * Inkrementira se ugao theta i ponovo iscrtava scena. Ovaj
         * ugao se odrzava u intervalu [-89,89] stepeni.
         */
    kamera.theta += kamera.dtheta;
    if (kamera.theta > MAX_THETA) {
        kamera.theta = MAX_THETA;
    }
}

void zoom_in()
{
    /* Dekrementira se radijus i ponovo iscrtava scena. Ovaj
         * parametar ima raspon [1,16] stepeni.
         */
    kamera.rad -= kamera.dr;
    
    if (kamera.rad < MIN_R)
        kamera.rad = MIN_R;
}

void zoom_out()
{
    /* Inkrementira se radijus i ponovo iscrtava scena. Ovaj
         * parametar ima raspon [1,16] stepeni.
         */
    kamera.rad += kamera.dr;
    if (kamera.rad > MAX_R)
        kamera.rad = MAX_R;
}

