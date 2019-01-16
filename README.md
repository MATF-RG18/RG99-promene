# RG99-promene
Promene

Projekat Promene je nastao na kursu Računarska grafika na III godini studija Informatike.
Cilj projekta jeste da se bolje razume funkcionisanje OpenGL i GLut biblioteka, kao i da se 
obuči za rad sa njima. 
Projekat obuhvata većinu gradiva koje je rađeno na vežbama kursa Računarska grafika. 

Ideja projekta jesu geometrijske transformacije objekata.



## Pokretanje:

Nakon kloniranja projekta, program treba prevesti sa komandom makefile-a: `make`.
Pokretanje programa: `./promene`.

Za učitavanje tekstura korišćena je biblioteka SOIL, koja je preuzeta i instalirana kao aplikacija:
```
#include "SOIL.h" 
sudo apt-get install libsoil-dev
```

## Komande:

 <kbd>G</kbd> - korisnik pokreće svaku narednu transformaciju
 
 
 
 U poslednjem koraku, nakon što se povećava vidljivost sfere upisane u kocku, korisnik ima mogućnost
 uvećavanja i smanjivanja veličine sfere komandama:

 `M` - uvećavanje radijusa sfere
 `N` - smanjivanje radijusa sfere
 
# Promena pozicije kamere:
 
 `A` - kamera se pomera u levo (look left)
 `D` - kamera se pomera u desno (look right)
 `Q` - kamera se približava koordinatom početku (zoom in)
 `E` - kamera se odaljava od koordinatnog početka (zoom out)
 
 `R` - resetovanje programa
 `T` - pauzira se program
 
 
