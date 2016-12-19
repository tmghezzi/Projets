      SUBROUTINE GETBOUNDNODE(N,M,VECTEUR_BOUND)
      IMPLICIT NONE
      INTEGER  I,T1,T2,T3,T4,N,M,BINF,BSUP,MODULOX,INV1,INV2
      REAL     VALEUR
      INTEGER  VECTEUR_B1(100),VECTEUR_B2(100),VECTEUR_B3(100),
     L VECTEUR_B4(100),VECTEUR_BOUND((n+1)*(M+1))
      T1 = 1
      T2 = 1
      T3 = 1
      T4 = 1
      INV1 = 0
      INV2 = 0
      BSUP = (N+1)*M+1
      BINF = (N+1)
      DO 1 I=1,(N+1)*(M+1)
      MODULOX = MODULO(I,N+1)
      IF(I.LE.BINF) THEN
      VECTEUR_BOUND(I) = I
      T1 = T1+1
      ENDIF
      IF(I.GE.BSUP) THEN
      VECTEUR_B3(T3) = I
      T3= T3+1
      ENDIF
      IF(MODULOX.EQ.0) THEN
      VECTEUR_B2(T2) = I
      T2 = T2+1
      ENDIF
      IF(MODULOX.EQ.1) THEN
      VECTEUR_B4(T4) = I
      T4 = T4+1
      ENDIF
1     CONTINUE
      DO 2 I = 1,M+1
      VECTEUR_BOUND(N+1+I) = VECTEUR_B2(I)
2     CONTINUE
      DO 3 I = 1,N+1
      VECTEUR_BOUND(M+N+2+I) = VECTEUR_B3(N+2-I)
3     CONTINUE  
      DO 4 I = 1,M+1
      VECTEUR_BOUND(M+2*N+3+I) = VECTEUR_B4(M+2-I)
4     CONTINUE   
      END
