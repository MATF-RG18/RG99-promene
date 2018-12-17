#include "moji_objekti.h"
#include <stdio.h>


 /*  glBegin(GL_TRIANGLE_FAN);
        //glNormal3f(0, 0, 1);
        glVertex3f(0, 0, 0);
        for (float i = 0.0; i <= 30; i += 0.02) {
            float x =  cosf(i * 2 * M_PI);
            float y =  sinf(i * 2 * M_PI);
            //glNormal3f(0, 0, 1);
            glVertex3f(x, y, 0);
        }
    glEnd();*/ 
// void draw_circle(float x, float y, float radius) { 
//     glMatrixMode(GL_MODELVIEW);
//     glPushMatrix();
//     glLoadIdentity();
//     glTranslatef(x, y, 2.2);
//     static const int circle_points = 100;
//     float angle = 2.0 * 3.1416f / circle_points;
// 
//     // this code (mostly) copied from question:
//     glBegin(GL_POLYGON);
//     double angle1=0.0;
//     glVertex2d(radius * cos(0.0) , radius * sin(0.0));
//     int i;
//     for (i=0; i<circle_points; i++)
//     {       
//         glVertex2d(radius * cos(angle1), radius *sin(angle1));
//         angle1 += angle;
//     }
//     glEnd();
//     glPopMatrix();
// }
//     */


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
        
       // glLineWidth(1);
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
    delete_cone();
//     if (start_cone == 1)
//         start_cone = 2;
    
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
    
//     if (brojac > 7000)
//     {
//         glPushMatrix();
//         glColor3f(1.0,0.0,0.0);
//         //glTranslatef(0,0,0);
//         draw_circle(0,0,1);
//         glPopMatrix();
//     }
    
    
    
    //glLineWidth(1);
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
        //start_cone = start_cone == 0 ? 1 : 2;
        if (brojac > 3000) {
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
    
        
        float tacka1[3], tacka2[3];
        
        if (brojac < 11000) {
            float koef = (brojac - 10000) / 1000.0f;
            printf("%f\n", koef);
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
    glPopMatrix();
    

}
