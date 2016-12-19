LINKS = -lglut -lGLU -lGL -lm -lpthread
INCS = -I. -I ../../include
GCC = gcc -g

SRCS    = .

all: Main

FILES =	Main

Main:	Main.c 
	$(GCC) $@.c DrawCourbeBezier.c Fonction.c CourbeBezier.c Matrice.c Vecteur.c $(INCS)	$(LDPATH) $(LINKS)	-o $@

clean:
	cd $(SRCS); rm  $(FILES)
