#include "oko.h"

void napravi_oko(void)
{
    // Postavljanje radijusa
    oko.r = OKO_RAD;
    oko.d_r = OKO_RAD_D;
    
    // Postavljanje azimuta
    oko.phi = OKO_PHI;
    oko.d_phi = OKO_PHI_D;
    
    // Postavljanje polara
    oko.theta = OKO_THETA;
    oko.d_theta = OKO_THETA_D;
    
    //Postavljanje razlika
    razlika.r = RAZ_POC;
    razlika.phi = RAZ_POC;
    razlika.theta = RAZ_POC;
}

void popravi_oko(void)
{
    // Prevodjenje sfernih koordinata u Dekartove
    oko.x = kliker.x + oko.r * cos(oko.theta) * cos(oko.phi);
    oko.y = kliker.y + oko.r * cos(oko.theta) * sin(oko.phi);
    oko.z = kliker.z + oko.r * sin(oko.theta);
}

int resetuj_oko(void)
{
    /* Postepeno vracanje oka u pocetno stanje:
       za pozitivne razlike to podrazumeva inverzne
       radnje koje ih smanjuju (napred, levo, dole),
       a za negativne suprotno (nazad, desno, gore) */
    if (razlika.r || razlika.phi || razlika.theta){
        if (razlika.r > RAZ_POC){
            oko_napred();
        } else if (razlika.r < RAZ_POC){
            oko_nazad();
        }
        
        /* Ispostavlja se da ova razlika nije znacajna,
           jer se ne treba kamera vratiti bas u pocetnu
           tacku, pa je algoritam samo postavlja na nulu,
           ali cuva se u komentaru ako kasnije zatreba */
        /*if (razlika.phi > RAZ_POC){
            oko_levo();
        } else if (razlika.phi < RAZ_POC){
            oko_desno();
        }*/
        razlika.phi = RAZ_POC;
        
        if (razlika.theta > RAZ_POC){
            oko_dole();
        } else if (razlika.theta < RAZ_POC){
            oko_gore();
        }
    // 1 ako je vracanje zavrseno
    } else return RES_KRAJ;
    
    // 0 ako vracanje nije zavrseno
    return !RES_KRAJ;
}

void oko_levo(void)
{
    /* Oko se krece levo:
       smanjivanje azimuta */
    oko.phi -= oko.d_phi;
    razlika.phi--;
    
    // Popravka jer phi = [-pi, pi)
    if (oko.phi < OKO_PHI_MIN){
        oko.phi += OKO_PHI_POM;
        razlika.phi = (oko.phi - OKO_PHI) / OKO_PHI_D;
    }
}

void oko_desno(void)
{
    /* Oko se krece desno:
       povecavanje azimuta */
    oko.phi += oko.d_phi;
    razlika.phi++;
    
    // Popravka jer phi = [-pi, pi)
    if (oko.phi >= OKO_PHI_MAX){
        oko.phi -= OKO_PHI_POM;
        razlika.phi = (oko.phi - OKO_PHI) / OKO_PHI_D;
    }
}

void oko_gore(void)
{
    /* Oko se krece gore:
       povecavanje polara */
    oko.theta += oko.d_theta;
    razlika.theta++;
    
    /* Popravka jer theta = [0, pi/2]
       Inace je [-pi/2, pi/2], ali ovako
       se izbegava odlazak ispod scene */
    if (oko.theta > OKO_THETA_MAX){
        oko.theta = OKO_THETA_MAX;
        razlika.theta--;
    }
}

void oko_dole(void)
{
    /* Oko se krece dole:
       smanjivanje polara */
    oko.theta -= oko.d_theta;
    razlika.theta--;
    
    /* Popravka jer theta = [0, pi/2]
       Inace je [-pi/2, pi/2], ali ovako
       se izbegava odlazak ispod scene */
    if (oko.theta < OKO_THETA_MIN){
        oko.theta = OKO_THETA_MIN;
        razlika.theta++;
    }
}

void oko_napred(void)
{
    /* Oko se priblizava:
       smanjivanje radijusa */
    oko.r -= oko.d_r;
    razlika.r--;
    
    // Popravka jer r = [3, 20]
    if (oko.r < OKO_RAD_MIN){
        oko.r = OKO_RAD_MIN;
        razlika.r++;
    }
}

void oko_nazad(void)
{
    /* Oko se udaljava:
       povecavanje radijusa */
    oko.r += oko.d_r;
    razlika.r++;
    
    // Popravka jer r = [3, 20]
    if (oko.r > OKO_RAD_MAX){
        oko.r = OKO_RAD_MAX;
        razlika.r--;
    }
}
