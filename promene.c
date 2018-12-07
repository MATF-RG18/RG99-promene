
#include <stdlib.h>
#include <GL/glut.h>

static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void init();
static void init_lights();
static void set_material(int id);
static void coord_sys();
static void my_obj();

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Promene");
    
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    
    /*  glClearColor( 0.35,  0.35 , 0.67,0);
      glClearColor(0.2,0.2,0.5,0);*/
   glClearColor(0,0,0,0);
   glEnable(GL_COLOR_MATERIAL);
    
    glEnable(GL_DEPTH_TEST);
    glLineWidth(5);
    
    glutMainLoop();

    return 0;
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    }
}

static void on_reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 100);
}

static void init()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_NORMALIZE); 
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10, 4, 3, 0, 0, -3, 0, 0, 1);
}

static void init_lights()
{
    GLfloat light_position[] = { 1, 10, 5, 0 };
    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat light_diffuse[] = { 1, 1, 1, 1 };
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

static void set_material(int id)
{
    GLfloat ambient_coeffs[] = { 0.3, 0.3, 0.3, 1 };
    GLfloat diffuse_coeffs[] = { 0.4, 0.4, 0.4, 1 };
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
    GLfloat shininess = 30;

    switch (id) {
        case 0:
            diffuse_coeffs[0] = 1.0;
            diffuse_coeffs[3] = 0.7;
            break;
        case 1:
            diffuse_coeffs[1] = 1.0;
            break;
        case 2:
            diffuse_coeffs[2] = 1.0;
            break;
    }

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

}

static void coord_sys()
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

static void my_obj()
{
    glPushMatrix();
    glColor3f(1.0,0.87541,0.0);
    glutSolidSphere(0.2, 1000, 1000);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1.0,0.87541,0.0);
    glTranslatef(0,0,-2.2);
    glutSolidSphere(0.2, 1000, 1000);
    glPopMatrix();
    
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

static void on_display(void)
{
    init();
    init_lights();
    
    my_obj();
    coord_sys();   
   
    glutSwapBuffers();
}
