#include "../header/osvetljenje.h"

/*Postavljanje inicijalnog osvetljenja i pozicije svetla*/
void init_lights()
{
    GLfloat light_position[] = {  1, 15, 5, 0 };
    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

/*Postavljamo materijale koji su korisceni za postavljanje na objekte*/
void set_material(int id)
{
    GLfloat ambient_coeffs[] = { 0.7, 0.7, 0.7, 1 };
    GLfloat diffuse_coeffs[] = { 0.4, 0.1, 0.1, 1 };
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
    GLfloat shininess = 30;

    switch (id) {
        case 0:
            diffuse_coeffs[0] = 1.0;
            diffuse_coeffs[3] = prozirnost;
            break;
        case 1:
            diffuse_coeffs[0] = 0.1;
            diffuse_coeffs[1] = 0.1;
            diffuse_coeffs[2] = 0.8;
            diffuse_coeffs[3] = 1;
            break;
        case 2:
            diffuse_coeffs[2] = 1.0;
            break;
    }

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

}
