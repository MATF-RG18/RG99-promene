#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define M_PI 3.141592653589793

#define RADIUS 9
#define PHI 0.5
#define THETA 0.3

#define MAX_R 5
#define MIN_R 1
#define MAX_PHI 2*M_PI
#define MIN_PHI 0
#define MAX_THETA M_PI/2
#define MIN_THETA -M_PI/2

#define DR 0.05
#define DPHI M_PI/90
#define DTHETA M_PI/90


static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void init();
static void init_lights();
static void set_material(int id);
static void coord_sys();
static void my_obj();

struct kamera
{
    double x,y,z;
    double rad, phi, theta;
    double dr, dphi,dtheta;
    
}kamera;

static void look_left();
static void look_right();
static void look_up();
static void look_down();
static void zoom_in();
static void zoom_out();
static void camera_init();

static void on_timer(int value);
int brojac = 0;
int timer_active = 0;
float animation_clip_cone = 0;

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
    camera_init();
    
    
    glEnable(GL_DEPTH_TEST);
    
    //glEnable(GL_LINE_SMOOTH);
    
    glutMainLoop();

    return 0;
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    case 'A':
    case 'a':
        look_left();
        glutPostRedisplay();
        break;
    case 'D':
    case 'd':
        look_right();
        glutPostRedisplay();
        break;
    case 'r':
    case 'R':
        /* Resetuju se uglovi phi i theta na pocetne vrednosti. */
        brojac = 0;
        if (!timer_active) {
            timer_active = 1;
            glutTimerFunc(50, on_timer, 0);
        }
        break;
    case 'S':
    case 's':
        look_down();
        glutPostRedisplay();
        break;    
    case 'W':
    case 'w':
        look_up();
        glutPostRedisplay();
        break;
    case 'Q':
    case 'q':
        zoom_in();
        glutPostRedisplay();
        break;
    case 'E':
    case 'e':
        zoom_out();
        glutPostRedisplay();
        break;
    case 'g':
    case 'G':
        /* Pokrece se simulacija. */
        if (!timer_active) {
            glutTimerFunc(50, on_timer, 0);
            timer_active = 1;
        }
        break;

    case 't':
    case 'T': 
        /* Zaustavlja se simulacija. */
        timer_active = 0;
        break;
    }
        
}

static void camera_init()
{
    kamera.rad = RADIUS; kamera.phi = PHI; kamera.theta = THETA;
    kamera.dr = DR; kamera.dphi = DPHI; kamera.dtheta = DTHETA;
}

static void convert_decart()
{
    kamera.x = kamera.rad * cos(kamera.theta) * cos(kamera.phi);
    kamera.y = kamera.rad * cos(kamera.theta) * sin(kamera.phi);
    kamera.z = kamera.rad * sin(kamera.theta);
}



static void look_left()
{
    kamera.phi -= kamera.dphi;
    if (kamera.phi > MAX_PHI) {
        kamera.phi -= MAX_PHI;
    } else if (kamera.phi < 0) {
        kamera.phi += MAX_PHI;
    }
}

static void look_right()
{
    kamera.phi += kamera.dphi;
    if (kamera.phi > MAX_PHI) {
        kamera.phi -= MAX_PHI;
    } else if (kamera.phi < 0) {
        kamera.phi += MAX_PHI;
    }
}

static void look_down()
{
     /* Dekrementira se ugao theta i ponovo iscrtava scena. Ovaj
         * ugao se odrzava u intervalu [-89,89] stepeni.
         */
    kamera.theta -= kamera.dtheta;
    if (kamera.theta < MIN_THETA) {
        kamera.theta = MIN_THETA;
    }
}

static void look_up()
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

static void zoom_in()
{
    kamera.rad -= kamera.dr;
    
    if (kamera.rad < MIN_R)
        kamera.rad = MIN_R;
}

static void zoom_out()
{
    kamera.rad += kamera.dr;
    if (kamera.rad > MAX_R)
        kamera.rad = MAX_R;
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
    convert_decart();
    gluLookAt(kamera.x, kamera.y, kamera.z, 0, 0, 0, 0, 0, 1);
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
static void on_timer(int value)
{
    /* Proverava se da li callback dolazi od odgovarajuceg tajmera. */
    if (value != 0)
        return;

    /* Azurira se vreme simulacije. */
    brojac += 50;

    /* Forsira se ponovno iscrtavanje prozora. */
    glutPostRedisplay();

    /* Po potrebi se ponovo postavlja tajmer. */
    
    if (brojac % 1000 == 0) {
        timer_active = 0;
    }
    
    printf("I'm alive");
    if (animation_clip_cone != 0){
        animation_clip_cone += 0.05;
        printf("%f\n", animation_clip_cone);
    }
    
    if (timer_active)
        glutTimerFunc(50, on_timer, 0);
}
static void delete_cone()
{
    
    double clipPlane[] = { 0, 0, 1, -animation_clip_cone};
    printf("%f\n", animation_clip_cone);
    glClipPlane(GL_CLIP_PLANE0, clipPlane);
  
    if (brojac > 2000) {
        glPushMatrix();
        glEnable(GL_CLIP_PLANE0);
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

static void my_obj()
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
            animation_clip_cone = 0.1;
    delete_cone();

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


static void on_display(void)
{
    init();
    init_lights();
    
    my_obj();
    coord_sys();   
   
    glutSwapBuffers();
}
