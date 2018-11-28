#include <stdlib.h>
#include <GL/glut.h>

static int window_width, window_height;

static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    
    /*  glClearColor( 0.35,  0.35 , 0.67,0);
      glClearColor(0.2,0.2,0.5,0);*/
   glClearColor(0,0,0,0);
    
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
    window_width = width;
    window_height = height;
}

static void on_display(void)
{
    /*
    GLfloat light_ambient[] = { 0, 0, 0, 1 };

    
    GLfloat light_diffuse[] = { 1, 1, 1, 1 };

    
    GLfloat light_specular[] = { 1, 1, 1, 1 };

    
    GLfloat model_ambient[] = { 0.4, 0.4, 0.4, 1 };
    
    
    GLfloat light_position[] = { 1, 1, 1, 0 };

    
    GLfloat no_material[] = { 0, 0, 0, 1 };

    
    GLfloat material_ambient[] = { 0.7, 0.7, 0.7, 1 };

    
    GLfloat material_ambient_heterogeneous[] = { 0.8, 0.8, 0.2, 1 };

    
    GLfloat material_diffuse[] = { 0.1, 0.5, 0.8, 1 };

   
    GLfloat material_specular[] = { 1, 1, 1, 1 };

    
    GLfloat no_shininess[] = { 0 };

    
    GLfloat low_shininess[] = { 5 };

    
    GLfloat high_shininess[] = { 100 };

    
    GLfloat material_emission[] = { 0.3, 0.2, 0.2, 0 };
    */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glViewport(0, 0, window_width, window_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 50);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(6, 4, 2, 0, 0, -3, 0, 0, 1);
    /*
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
        */
    
    glColor3f(200,200,0);
    
    glPushMatrix();
    /*glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient_heterogeneous);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_material);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, material_emission);*/
    glutSolidSphere(0.2, 1000, 1000);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(200,200,0);
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
    glColor3f(0.4, 0.4, 0.4);
    glutSolidCube(3);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0, -8);
    glColor3f(0.5, 0.1, 0.1);
    glutSolidCube(5);
    glPopMatrix();
    
       
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
   
    glutSwapBuffers();
}
