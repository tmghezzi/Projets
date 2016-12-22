SRCS    = .
FILES =	Main

Main :  Laplace2D.cxx MatriceBande.cxx Vecteur.cxx 
	g++ -g Vecteur.cxx MatriceBande.cxx Laplace2D.cxx Fonction.cxx Main.cxx -o Main


clean: 
	rm -f *.o *~ $(FILES)

