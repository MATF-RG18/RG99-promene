PROGRAM = promene
CC      = gcc
CFLAGS  = -g -Wall -I/usr/X11R6/include -I/usr/pkg/include
PROGR   = source/promene.c source/kamera.c source/moji_objekti.c source/koor_sistem.c source/osvetljenje.c source/display.c
ADD 	= header/kamera.h header/moji_objekti.h header/koor_sistem.h header/osvetljenje.h header/display.h
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): $(PROGR) $(ADD)
	$(CC) $(LDFLAGS) -o $(PROGRAM) $(PROGR) $(LDLIBS)

.PHONY: clean dist

clean:
	./$(PROGRAM) &

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
