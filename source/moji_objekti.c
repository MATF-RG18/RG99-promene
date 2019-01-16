#include "../header/moji_objekti.h"
#include "../header/osvetljenje.h"
#include "../header/display.h"
#include "../header/SOIL.h"
#include <stdio.h>

#define DESETICA 20

double translacija_x = -2.0;
int indikator_kamera = 0;
int ind=1;
float prva_prava = 0;
double  x = 2, y = -2, y_k1 = -2, z_k1 = 2.2, y_k2 = -2, z_k2 = 2.2, delta1=0, delta2=0, delta_korak=0.02;
double y_k_levo1 = 2, z_k_levo1 = 2.2, z_k_iza = 2.2, x_k_iza=2, x_k_ispred = -2, z_k_ispred = 2.2;
float radijus = 1;
float prozirnost = 1;
int indikator_prozirnost = 0; 

void init_teksture() {
    sfera_obj = gluNewQuadric();
    tekstura_sfere = SOIL_load_OGL_texture(TEKSTURA_SFERE,
    SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    
    sfera_obj2 = gluNewQuadric();
    tekstura_sfere2 = SOIL_load_OGL_texture(TEKSTURA_SFERE2,
    SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    
    tekstura_kocke = SOIL_load_OGL_texture(TEKSTURA_KOCKE,
    SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
}

void my_obj()
{   
    /*Translacija sfere do koordinatnog pocetka
     * Ovime je predstavljeno kretanje jedne tacke u 2D prostoru */
    glPushMatrix();
    glColor3f(1.0,0.87541,0.0);
    glTranslatef(0,0,-2.2);
    /*U programu se dogadjaji desavaju u funkciji od brojaca*/
    if (brojac <= 2000) {
        float koef = brojac < 1000 ? brojac / 1000.0f : 1.0f;
        glTranslatef(0, 0, 2.2 * koef);
        glutSolidSphere(0.05, 100, 100);
    }
    glPopMatrix();
    
    /*Tacka se "udvaja" i druga tacka se udaljava od prve, ali one ostaju povezane
     jer nesto sto je jednom bilo povezano ostaje povezano zauvek, te one formiraju
     duz izmedju njih*/
    glPushMatrix();
    if (brojac > 1000 && brojac <= 2000) {
        /*Niz kojim se kontrolise i iscrtava druga sfera u zavisnosti od njenog trenutnog polozaja*/
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
        
        /* Primeceno je da glLineWidth() ne radi na svim sistemima
        glLineWidth(10);
        int lajnvidth=-1;
        glGetIntegerv(GL_LINE_WIDTH, &lajnvidth);
        printf("%d\n", lajnvidth);*/
        
        /*Iscrtavanje duzi koja povezuje dve malopredjasnje povezane tacke*/
        glBegin(GL_LINES);
            glVertex3f(0, 0, 0);
            glVertex3f(-tacka[0], -tacka[1], -tacka[2]);
        glEnd();
    }
    glPopMatrix();
    
    /*Sledeci deo koda pokrece iscrtavanje kupe i nakon iscrtavanja uklanja kupu
     detaljan opis funkcije je u samoj funkciji*/
    if (brojac == 4000){
        /*Parametar se uvecava ukoliko je razlicit od nule, sto ovde postavljamo*/
        animation_clip_cone = 0.001;
    }
    if (brojac > 2000)
        delete_cone();
 
    /*Menja se polozaj kamere radi vizuelnog efekta da bi se video prvo ceo krug,
     a zatim se bira ugao tako da se od kruga samo jedna duz*/
    if (brojac > 6000 && brojac<8000){
       look_up();
    }
    if (brojac > 8000){
        look_down();
    }
    
    /*Sledeci deo koda iscrtava duzi koje se spajaju u kvadrat,
     a zatim se dobijeni kvadrat pretvara u kocku, dobija jednu dimenziju vise,
     rotacijom pocetnog kvadrata oko svake od njegovih ivica
     Detaljnije objasnjenje sledi u funkciji draw_square() */
    if (brojac > 9300){
        draw_lines();
    }
    draw_square();
    
    /* Sledece kocke su kostur za iscrtavanje kvadrata nad kojim se transformacije 
     * oblika desavaju. 
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
    glPopMatrix();*/
    
    /* Vodena povrsina ispod kocki */
    /*
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, names[0]);
    //glTranslatef()
    glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1);
        glTexCoord2f(1, 0);
        glVertex3f(-DESETICA*10, -DESETICA*10, -40);    
                
        glTexCoord2f(0, 0);
        glVertex3f(DESETICA*10, -DESETICA*10, -40);
                
        glTexCoord2f(0, 1); 
        glVertex3f(DESETICA*10, DESETICA*10, -40);
                    
        glTexCoord2f(1, 1);
        glVertex3f(-DESETICA*10, DESETICA*10, -40);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);    
    glPopMatrix(); 
    */
    /* Nebo koje okruzuje morsku povrsinu */
    /*
    glPushMatrix();
    
    glBindTexture(GL_TEXTURE_2D, names[1]);
    glBegin(GL_POLYGON);
        glNormal3f(1, 0, 0);
        glTexCoord2f(1, 0);
        glVertex3f(-DESETICA*10, -DESETICA*10, -40);    
                
        glTexCoord2f(0, 0);
        glVertex3f(-DESETICA*10, DESETICA*10, -40);
                
        glTexCoord2f(0, 1); 
        glVertex3f(-DESETICA*10, DESETICA*10, -40+DESETICA*10);
                    
        glTexCoord2f(1, 1);
        glVertex3f(-DESETICA*10, -DESETICA*10, -40+DESETICA*10);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
    
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, names[1]);
    glBegin(GL_POLYGON);
        glNormal3f(1, 0, 0);
        glTexCoord2f(1, 0);
        glVertex3f(DESETICA*10, -DESETICA*10, -40);    
                
        glTexCoord2f(0, 0);
        glVertex3f(-DESETICA*10, -DESETICA*10, -40);
                
        glTexCoord2f(0, 1); 
        glVertex3f(-DESETICA*10, -DESETICA*10, -40+DESETICA*10);
                    
        glTexCoord2f(1, 1);
        glVertex3f(DESETICA*10, -DESETICA*10, -40+DESETICA*10);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();*/
    
    /*Iscrtavanje kocki*/
    glEnable(GL_TEXTURE_2D);
    kocke(-10.5);
    piramida(-10.5); 
    glDisable(GL_TEXTURE_2D);
    
    /* Iscrtavanje pozadine
     Teksturirana je sfera i cela scena se nalazi unutar jedne sfere. */
    glPushMatrix();
    
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tekstura_sfere2);
        
    gluQuadricTexture(sfera_obj2, GLU_TRUE);
    glTranslatef(0,0,0);
    gluSphere(sfera_obj2, 20, 50, 50);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    
    glPopMatrix();               
}

void kocke(float transliraj){
    /*Iscrtavanje kocke*/
    glPushMatrix();
    glTranslatef(0, 0, transliraj);
    glBindTexture(GL_TEXTURE_2D, tekstura_kocke);
    /*iscrtavanje kocke i teksturiranje strana po strana*/
    glBegin(GL_POLYGON);
        glNormal3f(1, 0, 0);
        glTexCoord2f(1, 0);
        glVertex3f(2.5, -2.5, 0);    
                
        glTexCoord2f(0, 0);
        glVertex3f(2.5, 2.5, 0);
                
        glTexCoord2f(0, 1); 
        glVertex3f(2.5, 2.5, 5);
                    
        glTexCoord2f(1, 1);
        glVertex3f(2.5, -2.5, 5);
    glEnd();
    glBegin(GL_POLYGON);
        glNormal3f(1, 0, 0);
        glTexCoord2f(1, 0);
        glVertex3f(-2.5, -2.5, 0);    
                
        glTexCoord2f(0, 0);
        glVertex3f(-2.5, 2.5, 0);
                
        glTexCoord2f(0, 1); 
        glVertex3f(-2.5, 2.5, 5);
                    
        glTexCoord2f(1, 1);
        glVertex3f(-2.5, -2.5, 5);
    glEnd();
    glBegin(GL_POLYGON);
        glNormal3f(0, 1, 0);
        glTexCoord2f(1, 0);
        glVertex3f(-2.5, 2.5, 0);    
                
        glTexCoord2f(0, 0);
        glVertex3f(2.5, 2.5, 0);
                
        glTexCoord2f(0, 1); 
        glVertex3f(2.5, 2.5, 5);
                    
        glTexCoord2f(1, 1);
        glVertex3f(-2.5, 2.5, 5);
    glEnd();
    glBegin(GL_POLYGON);
        glNormal3f(0, 1, 0);
        glTexCoord2f(1, 0);
        glVertex3f(-2.5, -2.5, 0);    
                
        glTexCoord2f(0, 0);
        glVertex3f(2.5, -2.5, 0);
                
        glTexCoord2f(0, 1); 
        glVertex3f(2.5, -2.5, 5);
                    
        glTexCoord2f(1, 1);
        glVertex3f(-2.5, -2.5, 5);
    glEnd();
    /*gornja strana kocke*/
    glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1);
        glTexCoord2f(1, 0);
        glVertex3f(-2.5, -2.5, 5);    
                
        glTexCoord2f(0, 0);
        glVertex3f(-2.5, 2.5, 5);
                
        glTexCoord2f(0, 1); 
        glVertex3f(2.5, 2.5, 5);
                    
        glTexCoord2f(1, 1);
        glVertex3f(2.5, -2.5, 5);
    glEnd();
    /*donja strana kocke*/
    glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1);
        glTexCoord2f(1, 0);
        glVertex3f(-2.5, -2.5, 0);    
                
        glTexCoord2f(0, 0);
        glVertex3f(-2.5, 2.5, 0);
                
        glTexCoord2f(0, 1); 
        glVertex3f(2.5, 2.5, 0);
                    
        glTexCoord2f(1, 1);
        glVertex3f(2.5, -2.5, 0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);   
    glPopMatrix();
}

void piramida(float transliraj){
    /*Iscrtava se piramida koja stoji na kocki. 
     *Sa vrha piramide ce se pokrenuti sfera na transformacije. */
    glPushMatrix();
    glTranslatef(0,0,transliraj+5);
    glBindTexture(GL_TEXTURE_2D, tekstura_kocke);
    glBegin(GL_TRIANGLES);          
        glNormal3f(1, 0, 0);
        glTexCoord2f(0, 0);
        glVertex3f(1.5, -1.5, 0);
        
        glTexCoord2f(1, 0);
        glVertex3f(1.5, 1.5, 0);
        
        glTexCoord2f(0, 1); 
        glVertex3f(0, 0, 3.25);
    glEnd();
    glBegin(GL_TRIANGLES);          
        glNormal3f(1, 0, 0);
        glTexCoord2f(0, 0);
        glVertex3f(-1.5, -1.5, 0);
        
        glTexCoord2f(1, 0);
        glVertex3f(-1.5, 1.5, 0);
        
        glTexCoord2f(0, 1); 
        glVertex3f(0, 0, 3.25);
    glEnd();
    glBegin(GL_TRIANGLES);          
        glNormal3f(0, -1, 0);
        glTexCoord2f(0, 0);
        glVertex3f(-1.5, -1.5, 0);
        
        glTexCoord2f(1, 0);
        glVertex3f(1.5, -1.5, 0);
        
        glTexCoord2f(0, 1); 
        glVertex3f(0, 0, 3.25);
   glEnd();
   glBegin(GL_TRIANGLES);          
        glNormal3f(0, 1, 0);
        glTexCoord2f(0, 0);
        glVertex3f(-1.5, 1.5, 0);
        
        glTexCoord2f(1, 0);
        glVertex3f(1.5, 1.5, 0);
        
        glTexCoord2f(0, 1); 
        glVertex3f(0, 0, 3.25);
   glEnd();
   glPopMatrix();
}

/*Sledeca funkcija iscrtava kupu, 
 *a zatim uklanja omotac kupe pomocu kliping ravni */
void delete_cone()
{
    /*Definisemo koju kliping ravan zelimo da koristimo. */
    double clipPlane[] = { 0, 0, 1, -animation_clip_cone};
    glClipPlane(GL_CLIP_PLANE0, clipPlane);
  
    /*U zavisnosti od stanja brojaca iscrtava se kupa.
     Ideja je da se duz dobijena u prethodnom koraku iscrtavanja rotira oko z ose 
     sa fiksiranim donjim temenom u koordinatnom pocetku i da tom rotacijom nastaje kupa. 
     Baza kupe se naknadno dodaje, nakon sto je omotac kupe iscrtan. */
    if (brojac > 2000) {
        glPushMatrix();
        glEnable(GL_CLIP_PLANE0);        
        /*Iscrtavanje kupe je zasnovano na principu iscrtavanja medjusobno povezanih trouglova.
         To su tacke: koordinatni pocetak (polozaj prve sfere), trenutna tacka polozaja druge sfere i 
         tacka polozaja druge sfere nakon njene rotacije oko z ose. */
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
        
        /*Iscrtavanje baze kupe koje se krece u istom smeru kao i formiranje omotaca kupe. */
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
    /*Iscrtavanje linija koje formiraju kvadrat. 
     Kada se kvadrat iscrta, on se popuni odgovarajucom bojom. */
    glPushMatrix();
    
    if (brojac<21900){
        float tacka1[3], tacka2[3];
        if (brojac < 12000){
            /*Linija koju smo videli nakon rotacije kamere po uglu theta, 
             zamenjuje se duzom linijom koja predstavlja stranicu kvadrata. */
            if (brojac < 11000) {
                float koef = (brojac - 10000) / 1000.0f;
                tacka1[0] = 2 * koef;            
                tacka1[1] = -2 * koef;
                tacka1[2] = 2.2;
                tacka2[0] = -2 * koef;            
                tacka2[1] = 2 * koef;
                tacka2[2] = 2.2;
            } 
            else {
                tacka1[0] = 2;            
                tacka1[1] = -2;
                tacka1[2] = 2.2;
                tacka2[0] = -2;            
                tacka2[1] = 2;
                tacka2[2] = 2.2;
            }
        /*Iscrtavanje stranice, od sredine ka krajevima duzi. */   
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
        /*Rotira se kamera dok ne dodje do pozicije gde je y koordinata jednaka nuli, jer 
         zelimo da posmatramo dogadjaj iz druge pozicije. */
            indikator_kamera = 1;
            /*Nakon iscrtane duzi iz dva dela, zamenjujemo je jednom duzi, koja predstavlja stranicu kvadrata. */
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
    /*Iscrtavanje kocke 
     */
    if (brojac < 32000){
    if (indikator_kvadrat==1 && brojac<22000){
        if (ind==1)
        {
        /*Pocev od temena iscrtane linije, iscrtavaju se u isto vreme druge dve stranice kvadrata 
         *koje su paralelne jedna drugoj*/ 
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
            /*Dodavanje poslednje stranice kvadrata, od leve ka desnoj ivici. 
             Kameru fiksiramo na odredjenoj visini, ukoliko je ind=0, jer nam 
             on ukazuje da je kamera stigla do svog odredjenog theta. 
             Indikator kamere postavljamo na nulu jer zelimo da kamera moze da se krece.*/
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
                        /*Indikator kamere kojim se kamera pocinje udaljavati od koordinatnog pocetka. */
                        indikator_kvadrat=2;
                    }
                }
            glEnd();
        }        
    }
    else if (indikator_kvadrat == 2){
        /* Iscrtavanje kvadrata koji je baza kocke. */
        indikator_kamera = 0;
        kamera.theta = nova_kamera;
        glPushMatrix();
        
        if (brojac > 24000 && brojac < 32000){
            zoom_out();
        }

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_POLYGON);
        glColor3f(0.1,0.2,0.8);
            glVertex3f(2,2,2.2);
            glVertex3f(-2,2,2.2);
            glVertex3f(-2,-2,2.2);
            glVertex3f(2,-2,2.2);
        glEnd();
        
        /*Kvadrati koji se inicijalno nalaze na bazi kocke, podizu se sa cetiri 
         *razlicite strane i formiraju kocku. */
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        /* Desna strana u odnosu na polozaj kamere. */
        glBegin(GL_POLYGON);
            glColor3f(0.1,0.2,0.8);
            
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
        /* Leva strana u odnosu na polozaj kamere. */
        glBegin(GL_POLYGON);
            glColor3f(1,0.6,0.7);
            
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
            }
        glEnd();

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        /* Zadnja strana u odnosu na polozaj kamere. */
        glBegin(GL_POLYGON);
            glColor3f(0.1,0.9,0.8);
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
        /* Prednja strana u odnosu na polozaj kamere. */
        glBegin(GL_POLYGON);
            glColor3f(0.7,0.4,0.8);
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
                
            }
        glEnd();
        
        if (brojac > 32000){
            /*Iscrtavanje gornje strane kocke. */
            glPushMatrix();
            glBegin(GL_POLYGON);
                glColor3f(0.8,0.4,0.1);
                glVertex3f(-2,-2,6.2);
                glVertex3f(-2,2,6.2);
                glVertex3f(2,2,6.2);
                glVertex3f(2,-2,6.2);
            glEnd();
            glPopMatrix();
            indikator_kvadrat = 0;
        }
        glPopMatrix();
    }
    }
    else if (brojac>=32000){
        indikator_kvadrat = 0;
        indikator_prozirnost = 1;
        MIN_THETA_CIRCLE = 0;
        kamera.theta = nova_kamera;
        /*Inicijalizacije kamere. */
        init();
        
        /*Sfera koja je upisana u kocku. */
        glPushMatrix();
        glDisable(GL_COLOR_MATERIAL);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tekstura_sfere);
        
        gluQuadricTexture(sfera_obj, GLU_TRUE);
        glTranslatef(0,0,4.2);
        gluSphere(sfera_obj, radijus, 100, 100);        
       
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_COLOR_MATERIAL);
        glPopMatrix();
        
        /*Kocka cija se prozirnost povecava i otkriva sferu. */
        //if (brojac < 40000){
        glPushMatrix();
        glDisable(GL_COLOR_MATERIAL);
        set_material(0);
        glTranslatef(0,0,4.2);
        glutSolidCube(4);
        glEnable(GL_COLOR_MATERIAL);
        glPopMatrix();
        //}
        
    }  
}
