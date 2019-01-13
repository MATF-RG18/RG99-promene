#include "../header/display.h"

int brojac = 0;
int timer_active = 0;
float animation_clip_cone = 0;
int start_line = 0;
int start_cone = 0;
int indikator_kvadrat = 0;
double uvecaj_theta = M_PI/60;


void on_keyboard(unsigned char key, int x, int y)
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
    case 'M':
    case 'm':
        radijus += 0.05;
        glutPostRedisplay();
        break;
    case 'N':
    case 'n':
        if (radijus>=0)
            radijus -= 0.05;
        glutPostRedisplay();
        break;
        
    }
        
}

void on_display(void)
{
    init();
    init_lights();
    
    my_obj();
    //coord_sys();   
   
    glutSwapBuffers();
}

void on_timer(int value)
{
    /* Proverava se da li callback dolazi od odgovarajuceg tajmera. */
    if (value != 0)
        return;

    /* Azurira se vreme simulacije. */
    brojac += 50;
    move_camera_circle += 0.1;
    if (translacija_x <= 2)
        translacija_x += M_PI/200;
    else{
        if (indikator_kvadrat!=2)
            indikator_kvadrat = 1;
    }

    if (indikator_prozirnost && prozirnost>=0.7)
    {
        prozirnost -= 0.001;
    }
        
        
    /* Po potrebi se ponovo postavlja tajmer. */
    
    if (brojac % 1000 == 0 && brojac<=4000) {
        timer_active = 0;
    }
    
   
    if (animation_clip_cone != 0){
        animation_clip_cone += 0.05;
    }
    
    if (timer_active)
        glutTimerFunc(50, on_timer, 0);
    /* Forsira se ponovno iscrtavanje prozora. */
    glutPostRedisplay();
    
}

void init_main(int* argc, char** argv)
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    glutInitWindowSize(1200, 800);
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
    glLineWidth(1);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glEnable(GL_DEPTH_TEST);
    /* Ukljucujemo normalizaciju vektora normala */
    glEnable(GL_NORMALIZE);
    uvedi_teksture();
    
    //glEnable(GL_LINE_SMOOTH);
}

void uvedi_teksture(){

    Image * image;
    /* Ukljucuju se teksture. */
    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);
       
    /* Inicijalizuje se objekat koji ce sadrzati teksture ucitane iz fajla */
    image = image_init(0, 0);

    /* Kreira se prva tekstura */
    image_read(image, FILENAME0);

    /* Generisu se identifikatori tekstura */
    glGenTextures(5, names);

    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    
    /* Kreira se druga tekstura */
    image_read(image, FILENAME1);
    
    glBindTexture(GL_TEXTURE_2D, names[1]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels); 
    
    /* Kreira se treca tekstura */
    image_read(image, FILENAME2);
    
    glBindTexture(GL_TEXTURE_2D, names[2]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Unistava se objekat za citanje tekstura iz fajla */
    image_done(image);
}
