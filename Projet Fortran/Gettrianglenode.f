      SUBROUTINE GETTRIANGLENODE(N,M,VECTEUR_TRIANGLE)
      IMPLICIT NONE
      INTEGER  I,J,T,N,M,C,BOOL
      INTEGER     VALEUR,VECTEUR(3),VECTEUR_TRIANGLE(N*M)
      T = 1
      C = 1
      BOOL = 0
      DO 2 J=1,M
      IF(BOOL.EQ.1) THEN
      C = C+1
      ENDIF
      DO 1 I=1,N
      VECTEUR_TRIANGLE(T)=C
      WRITE(*,*) 'Noeud n°1 Triangle bas:  ',VECTEUR_TRIANGLE(T)
      T=T+1
      VECTEUR_TRIANGLE(T)=C+1
      WRITE(*,*) 'Noeud n°2 Triangle bas:  ',VECTEUR_TRIANGLE(T)
      T=T+1
      VECTEUR_TRIANGLE(T)=N*J+I+J
      WRITE(*,*) 'Noeud n°3 Triangle bas:  ',VECTEUR_TRIANGLE(T)
      T=T+1
      VECTEUR_TRIANGLE(T)=C+1
      WRITE(*,*) 'Noeud n°1 Triangle haut: ',VECTEUR_TRIANGLE(T)
      T=T+1
      VECTEUR_TRIANGLE(T)=N*J+I+J+1
      WRITE(*,*) 'Noeud n°2 Triangle haut: ',VECTEUR_TRIANGLE(T)
      T=T+1
      VECTEUR_TRIANGLE(T)=N*J+I+J
      WRITE(*,*) 'Noeud n°3 Triangle haut: ',VECTEUR_TRIANGLE(T)
      T=T+1
      C = C+1
1     CONTINUE
      BOOL = 1
2     CONTINUE
      END
