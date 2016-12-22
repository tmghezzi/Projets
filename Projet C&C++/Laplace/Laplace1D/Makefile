SRCS    = .
FILES =	Main

Main : Laplace1D.cxx  MatriceBande.cxx Vecteur.cxx 
	g++ Vecteur.cxx MatriceBande.cxx Laplace1D.cxx Fonction.cxx Main.cxx -o Main

clean: 
	rm -f *.o *~ $(FILES)

