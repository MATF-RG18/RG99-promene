PROGRAM = promene
CC      = gcc
CFLAGS  = -g -Wall -I/usr/X11R6/include -I/usr/pkg/include
PROGR   = promene.c kamera.c moji_objekti.c koor_sistem.c osvetljenje.c display.c
ADD 	= kamera.h moji_objekti.h koor_sistem.h osvetljenje.h display.h
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): $(PROGR) $(ADD)
	$(CC) $(LDFLAGS) -o $(PROGRAM) $(PROGR) $(LDLIBS)

.PHONY: clean dist

clean:
	./$(PROGRAM) &

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
