# RG99-promene
"Promene"

Projekat "Promene" je nastao na kursu Računarska grafika na III godini studija Informatike. 
Cilj rada projekta jeste da se razume funkcionisanje grafičkog sistema OpenGL i GLUT biblioteke, kao i da 
se obuči za rad sa njima. <br />
Projekat obuhvata svo gradivo (osim rada sa mišem) koje je rađeno na vežbama kursa Računarska grafika.  <br />
 
Projekat "Promene" ima za ideju geometrijske transformacije objekata. <br />
Cilj projekta "Promene" je da se u jednom osmišljenom nizu povežu geometrijski oblici sa svim naučenim funkcijama iz oblasti predmeta Računarska grafika koji su obrađeni na vežbama od oktobra do decembra 2018. godine. 

## Vizuelni prikaz projekta "Promene":

### Jednakost makro i mikro sveta u zakonima 

Na vrhu piramide koja leži na kocki je mikro sfera - tačka. Korisničkom interakcijom sfera se ispaljuje u prostor, nakon čega se opet interakcijom udvaja. Sledećom interakcijom se transformiše u ograničeni skup tačaka, duž, koja povezuje te dve tačke.<br /> Sledeći koraci su automatski. <br />
Cela duž se rotira oko jedne svoje krajnje tačke i oko z ose i tako nastaje konusna površ. Nakon toga je popunjen bazni krug istom bojom kao konusna površ koju opisuje slobodna krajnja tačka. <br />
Upotrebom kliping ravni omotač kupe nestaje i ostaje samo bazna površ - krug. Kretanjem kamere, bazni krug se transformiše u duž. Uvećava se duž, nakon čega se duž i pogled kamere na duž rotiraju, tako da im je y-koordinata jednaka nuli. <br />
Sledeći korak je promena pozicije kamere, koju prate projekcione duži po x osi istih dužina kao data duž, a koje kreću iz krajeva date duži. Kada projekcione duži dobiju dužinu početne duži sledeći automatski korak je spajanje krajeva tih projekcionih duži. 
Popunjavanjem ravni mnogougaone kvadratne linije dobija se plavi kvadrat.<br />
Kvadrat se dalje automatski transformiše u figuru kocke čija je svaka strana druge boje. Kada se dobije kocka različitih boja, sve strane prelaze u crvenu boju i paralelno sa tim postavlja se unutar crvene kocke zlatna sfera - Sunce. Sledeći korak je automatska akcija povećavanja transparentnosti crvene boje kocke, do potpunog nestajanja kocke i otkrivanja zlatne sfere - Sunca. Tada počinje interakcija korisnika koji može približiti ili odaljiti sferu na dva načina; promenom radijusa sfere ili promenom pozicije kamere. <br />

Cela scena je urađena unutar jedne velike sfere (simbolika teksture pozadine scene).


## Pokretanje:

Nakon kloniranja projekta, program treba prevesti sa komandom makefile-a: `make`. <br />
Pokretanje programa: `./promene`. <br />

Projekat je rađen u programskom jeziku C uz upotrebu grafičkog sistema OpenGL, okruženju za razvoj interaktivnih 2D i 3D grafičkih aplikacija, i korišćenje GLUT biblioteke. 
Program može da se iskompajlira i izvršava na svakom sistemu koji podržava OpenGL i GLUT. 
Sve potrebne biblioteke mogu se instalirati komandom: `sudo apt-get install binutils-gold freeglut3 freeglut3-dev` za Ubuntu distribuciju Linux-a.

Za učitavanje tekstura korišćena je biblioteka SOIL, koja je preuzeta i instalirana kao aplikacija: <br />
```
#include "SOIL.h" 
sudo apt-get install libsoil-dev
```

## Komande:

 <kbd>G</kbd> - korisnik pokreće narednu transformaciju <br />
 
 Interakcija sa korisnikom je na početku programa. Korisnik pokreće komandom <kbd>G</kbd> narednu "promenu" do određenog koraka. Od tog koraka "promene" počinju automatski da se odvijaju do momenta pojavljivanja geometrijskog oblika sfere.
 
 U poslednjem koraku, nakon što se poveća vidljivost sfere upisane u kocku, 
 korisnik ima mogućnost uvećavanja i smanjivanja (interakcija) veličine sfere komandama: <br />

 <kbd>M</kbd> - uvećavanje radijusa sfere <br />
 <kbd>N</kbd> - smanjivanje radijusa sfere <br />
 
 
### Promena pozicije kamere:
 
 <kbd>A</kbd> - kamera se pomera u levo (look left) <br />
 <kbd>D</kbd> - kamera se pomera u desno (look right) <br />
 <kbd>Q</kbd> - kamera se približava koordinatom početku (zoom in) <br />
 <kbd>E</kbd> - kamera se odaljava od koordinatnog početka (zoom out) <br />
 
 <kbd>R</kbd> - resetovanje programa <br />
 <kbd>T</kbd> - pauzira se program <br />
 
 
