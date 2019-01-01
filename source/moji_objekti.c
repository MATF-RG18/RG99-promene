#include "../header/moji_objekti.h"
#include <stdio.h>
double translacija_x = -2.0;
int indikator_kamera = 0;
int ind=1;
float prva_prava = 0;
double  x = 2, y = -2, y_k1 = -2, z_k1 = 2.2, y_k2 = -2, z_k2 = 2.2, delta1=0, delta2=0, delta_korak=0.02;
double y_k_levo1 = 2, z_k_levo1 = 2.2, z_k_iza = 2.2, x_k_iza=2, x_k_ispred = -2, z_k_ispred = 2.2;
void my_obj()
{    
    glPushMatrix();
    glColor3f(1.0,0.87541,0.0);
    glTranslatef(0,0,-2.2);
    if (brojac <= 2000) {
        float koef = brojac < 1000 ? brojac / 1000.0f : 1.0f;
        glTranslatef(0, 0, 2.2 * koef);
        glutSolidSphere(0.05, 100, 100);

    }
    glPopMatrix();
    
    glPushMatrix();
    if (brojac > 1000 && brojac <= 2000) {
        
        float tacka[3];
        
        if (brojac < 2000) {
            float koef = (brojac - 1000) / 1000.0f;
            tacka[0] = 2 * koef;            
            tacka[1] = 0;
            tacka[2] = 2.2 * koef;

            glTranslatef(2 * koef, 0, 2.2 * koef);
        } else {
            tacka[0] = 2;            
            tacka[1] = 0;
            tacka[2] = 2.2;
            glTranslatef(2, 0, 2.2);
        }
        
        glutSolidSphere(0.05, 100, 100);
        
        glLineWidth(10);
        //int lajnvidth=-1;
        //glGetIntegerv(GL_LINE_WIDTH, &lajnvidth);
        //printf("%d\n", lajnvidth);
        glBegin(GL_LINES);
            glVertex3f(0, 0, 0);
            glVertex3f(-tacka[0], -tacka[1], -tacka[2]);
            
        glEnd();
    }
    glPopMatrix();
    
    if (brojac == 4000)
            animation_clip_cone = 0.001;
    if (brojac > 2000)
        delete_cone();
 
    if (brojac > 6000 && brojac<8000)
    {
       look_up();
    }
    if (brojac > 8000)
    {
        move_camera_circle=1;
        look_down();
    }
    
    if (brojac > 9300){
        draw_lines();
    }
    
    draw_square();
    
    glPushMatrix();
    glColor3f(0.85, 0.85, 0.1);
    glutWireCube(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0, -3);
    glColor3f(0.8, 0.8, 0.8);
    glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0, -5);
    glColor3f(0.6, 0.6, 0.6);
    glutSolidCube(3);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0, -8);
    glColor3f(0.4, 0.4, 0.4);
    glutSolidCube(5);
    glPopMatrix();
    
}

void delete_cone()
{
    
    double clipPlane[] = { 0, 0, 1, -animation_clip_cone};
    //printf("%f\n", -animation_clip_cone);
    glClipPlane(GL_CLIP_PLANE0, clipPlane);
  
    if (brojac > 2000) {
        glPushMatrix();
        glEnable(GL_CLIP_PLANE0);
        if (start_cone == 0)
             start_cone = 1;
       // start_cone = animation_clip_cone == 0 ? 1 ;
        //printf("%d\n", start_cone);
        glTranslatef(0, 0, 2.2);
        float koef = brojac < 3000 ? (brojac - 2000) / 1000.0f : 1.05;
        glBegin(GL_TRIANGLE_FAN);
            glNormal3f(0, 0, -1);
            glVertex3f(0, 0, -2.2);
            for (float i = 0.0; i < koef; i += 0.02) {
                float x = 2 * cosf(i * 2 * M_PI);
                float y = 2 * sinf(i * 2 * M_PI);
                glNormal3f(x,y,0);
                glVertex3f(x, y, 0);
                
            }
        glEnd();
        glDisable(GL_CLIP_PLANE0);
        
        if (brojac > 3000 && brojac<10000) {
            glBegin(GL_TRIANGLE_FAN);
                glNormal3f(0, 0, 1);
                glVertex3f(0, 0, 0);
                for (float i = 0.0; i <= (brojac-3000) /1000.0f; i += 0.02) {
                    float x = 2 * cosf(i * 2 * M_PI);
                    float y = 2 * sinf(i * 2 * M_PI);
                    glNormal3f(0, 0, 1);
                    glVertex3f(x, y, 0);
                    
                }
            glEnd();
        
        }
        
        glPopMatrix(); 
        
    }    
}

void draw_lines()
{
    glPushMatrix();
    
        if (brojac<21900){
        float tacka1[3], tacka2[3];
        if (brojac < 12000){
        if (brojac < 11000) {
            float koef = (brojac - 10000) / 1000.0f;
            //printf("%f\n", koef);
            tacka1[0] = 2 * koef;            
            tacka1[1] = -2 * koef;
            tacka1[2] = 2.2;
            tacka2[0] = -2 * koef;            
            tacka2[1] = 2 * koef;
            tacka2[2] = 2.2;

            //glTranslatef(2 * koef, -2*koef, 2.2);
        } else {
            tacka1[0] = 2;            
            tacka1[1] = -2;
            tacka1[2] = 2.2;
            tacka2[0] = -2;            
            tacka2[1] = 2;
            tacka2[2] = 2.2;
            //glTranslatef(2, -2, 2.2);
        }
    glBegin(GL_LINES);
        glVertex3f(0, 0, 2.2);
        glVertex3f(tacka1[0], tacka1[1], tacka1[2]);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(0, 0, 2.2);
        glVertex3f(tacka2[0], tacka2[1], tacka2[2]);
    glEnd();
        }
    
    else{
        indikator_kamera = 1; 
        glBegin(GL_LINES);
            glVertex3f(2, -2, 2.2);
            glVertex3f(translacija_x, 2, 2.2);
        glEnd();
    }
        }
    glPopMatrix();    
}

void draw_square()
{
    //printf("indikator_kvadrat: %d\n", indikator_kvadrat);
    //if (brojac < )
    if (indikator_kvadrat==1 && brojac<22000){
        //printf("square f: %f\n", kamera.theta);
       // if (kamera.theta <= MAX_THETA)
        if (ind==1)
        {
            indikator_kamera = 2;
            glBegin(GL_LINES);
                glVertex3f(2,2,2.2);
                if (x>=-2){
                    glVertex3f(x,2,2.2);
                    x -= 0.02;
                }
                else
                    glVertex3f(-2,2,2.2);
                
                glVertex3f(2,-2,2.2);
                if (x>=-2){
                    glVertex3f(x,-2,2.2);
                    x -= 0.02;
                }
                else{
                    glVertex3f(-2,-2,2.2);
                    
                }
            glEnd();

        }
        if (ind==0)
        {
            indikator_kamera=0;
            kamera.theta = nova_kamera;
            glBegin(GL_LINES);
                glVertex3f(2,2,2.2);
                if (x>=-2){
                    glVertex3f(x,2,2.2);
                    x -= 0.02;
                }
                else
                    glVertex3f(-2,2,2.2);
             glVertex3f(2,-2,2.2);
                if (x>=-2){
                    glVertex3f(x,-2,2.2);
                    x -= 0.02;
                }
                else{
                    glVertex3f(-2,-2,2.2);
                    
                    glVertex3f(-2,-2,2.2);
                    if (y<=2){
                        glVertex3f(-2,y,2.2);
                        y += 0.05;
                    }
                    else{
                        glVertex3f(-2,2,2.2);
                        indikator_kvadrat=2;
                        //printf("brojac: %d\n", brojac);
                        //printf("indikator_kvadrat: %d\n", indikator_kvadrat);
                        
                    }
                }
                
            glEnd();
        }        
    }
    else if (indikator_kvadrat == 2){
        /* Iscrtavanje kvadrata koji je baza kocke koja dalje treba da nastane */
        kamera.theta = nova_kamera;
        //printf("indikator_kvadrat: %d\n", indikator_kvadrat);
        glPushMatrix();
        
        if (brojac > 24000){
            zoom_out();
            //glRotatef(90,0,0,1);
        }
//         glTranslatef(0,2,0);
//         glRotatef(90.0,0,1.0,0);
//         glTranslatef(0,-2,0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_POLYGON);
        glColor3f(0.1,0.2,0.6);
            glVertex3f(2,2,2.2);
            glVertex3f(-2,2,2.2);
            glVertex3f(-2,-2,2.2);
            glVertex3f(2,-2,2.2);
        glEnd();
        
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_POLYGON);
            glColor3f(0.1,0.2,0.4);
            
            if (z_k1<=6.2){
                glVertex3f(-2,y_k1,z_k1);
                delta1+=delta_korak;
                z_k1+=delta_korak; y_k1 += delta_korak;
            }
            else
                glVertex3f(-2,2,6.2);
            
            
            if (z_k2<=6.2){
                glVertex3f(2,y_k2,z_k2);
                delta2+=delta_korak;
                z_k2+=delta_korak; y_k2 += delta_korak;
            }
            else
                glVertex3f(2,2,6.2);
            glVertex3f(2,2,2.2);
            glVertex3f(-2,2,2.2);
        glEnd();
        
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_POLYGON);
            glColor3f(0.1,0.2,0.4);
            
            glVertex3f(-2,-2,2.2);
            glVertex3f(2,-2,2.2);
            if (z_k_levo1<=6.2){
                glVertex3f(2,y_k_levo1,z_k_levo1);
                glVertex3f(-2,y_k_levo1,z_k_levo1);
                z_k_levo1+=delta_korak; y_k_levo1 -= delta_korak;
            }
            else{
                glVertex3f(2,-2,6.2);
                glVertex3f(-2,-2,6.2);
                //printf("brojac: %d\n", brojac);
            }
        glEnd();
        if (brojac > 32000){
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_POLYGON);
            glColor3f(0.1,0.2,0.8);
            glVertex3f(-2,-2,2.2);
            glVertex3f(-2,2,2.2);
            if (z_k_iza<=6.2){
                glVertex3f(x_k_iza,2,z_k_iza);
                glVertex3f(x_k_iza,-2,z_k_iza);
                z_k_iza+=delta_korak; x_k_iza -= delta_korak;
            }
            else{
                glVertex3f(-2,2,6.2);
                glVertex3f(-2,-2,6.2);
            }
            
        glEnd();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_POLYGON);
            glColor3f(0.1,0.4,0.8);
            glVertex3f(2,-2,2.2);
            glVertex3f(2,2,2.2);
            if (z_k_ispred<=6.2){
                glVertex3f(x_k_ispred,2,z_k_ispred);
                glVertex3f(x_k_ispred,-2,z_k_ispred);
                z_k_ispred+=delta_korak; x_k_ispred += delta_korak;
            }
            else{
                glVertex3f(2,2,6.2);
                glVertex3f(2,-2,6.2);
                printf("brojac: %d\n", brojac);
            }
        glEnd();
        
        }
        if (brojac > 42100){
            glPushMatrix();
            glBegin(GL_POLYGON);
            glColor3f(0.1,0.4,0.8);
            glVertex3f(-2,-2,6.2);
            glVertex3f(-2,2,6.2);
            
            glVertex3f(2,2,6.2);
            glVertex3f(2,-2,6.2);
            glEnd();
            glPopMatrix();
        }
            
        glPopMatrix();
    }
}
