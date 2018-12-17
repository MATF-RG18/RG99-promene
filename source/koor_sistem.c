#include "koor_sistem.h"


void coord_sys(void)
{
     glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(10,0,0);
        glColor3f(0.4,0,0);
        glVertex3f(0,0,0);
        glVertex3f(-10,0,0);
        
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,10,0);
        glColor3f(0,0.4,0);
        glVertex3f(0,0,0);
        glVertex3f(0,-10,0);
        
        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,10);
        glColor3f(0,0,0.4);
        glVertex3f(0,0,0);
        glVertex3f(0,0,-40);
    glEnd();
}
