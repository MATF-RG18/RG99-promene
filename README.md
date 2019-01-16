# RG99-promene
Promene

Projekat Promene je nastao na kursu Računarska grafika na III godini studija Informatike. <br />
Cilj projekta jeste da se bolje razume funkcionisanje OpenGL i GLut biblioteka, kao i da <br />
se obuči za rad sa njima. <br />
Projekat obuhvata većinu gradiva koje je rađeno na vežbama kursa Računarska grafika. <br />

Ideja projekta jesu geometrijske transformacije objekata.<br />



## Pokretanje:

Nakon kloniranja projekta, program treba prevesti sa komandom makefile-a: `make`. <br />
Pokretanje programa: `./promene`. <br />

Za učitavanje tekstura korišćena je biblioteka SOIL, koja je preuzeta i instalirana kao aplikacija: <br />
```
#include "SOIL.h" 
sudo apt-get install libsoil-dev
```

## Komande:

 <kbd>G</kbd> - korisnik pokreće svaku narednu transformaciju <br />
 
 
 
 U poslednjem koraku, nakon što se povećava vidljivost sfere upisane u kocku, <br />
 korisnik ima mogućnost uvećavanja i smanjivanja veličine sfere komandama: <br />

 <kbd>M</kbd> - uvećavanje radijusa sfere <br />
 <kbd>N</kbd> - smanjivanje radijusa sfere <br />
 
# Promena pozicije kamere:
 
 <kbd>A</kbd> - kamera se pomera u levo (look left) <br />
 <kbd>D</kbd> - kamera se pomera u desno (look right) <br />
 <kbd>Q</kbd> - kamera se približava koordinatom početku (zoom in) <br />
 <kbd>E</kbd> - kamera se odaljava od koordinatnog početka (zoom out) <br />
 
 <kbd>R</kbd> - resetovanje programa <br />
 <kbd>T</kbd> - pauzira se program <br />
 
 
