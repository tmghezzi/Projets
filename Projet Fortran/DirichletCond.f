      SUBROUTINE CONDITION_DIRICHLET(N,M,SIZEMAX,
     M VECTEUR_MIN,VECTEUR_BOUND,VECTEUR_DIAGONAL,VECTEUR_SECONDMEMBRE,
     L VECTEUR_STOCKAGE,VECTEUR_SECONDA)
      IMPLICIT NONE
      INTEGER  I,J,T,IB,DEC,N,M,PMIN,SIZEMAX,VECTEUR_MIN((N+1)*(M+1)),
     L VECTEUR_DIAGONAL((N+1)*(M+1)),VECTEUR_BOUND(2*(M+N+2)),POS,PTRCOL
      REAL    VECTEUR_STOCKAGE(SIZEMAX),VECTEUR_SECONDA((N+1)*(M+1)),
     L VECTEUR_SECONDMEMBRE((N+1)*(M+1))

C     ------------BOUND GAMA1 --------------      

      PTRCOL = 1
      DO 1 I=1,(N+1)
           POS = VECTEUR_DIAGONAL(I)
           VECTEUR_STOCKAGE(POS) = 1
           DEC = POS

C          SET ZERO -> LIGN I
           T = I-VECTEUR_MIN(I)
           DO 2 J=1,T
                DEC = DEC-1
                VECTEUR_STOCKAGE(DEC) = 0.
2               CONTINUE


          PTRCOL = 1
C         SET ZERO -> COLOGN I
          DO 3 J=I+1,(N+1)*(M+1)
               PMIN = VECTEUR_MIN(J)

               IF(I.GE.PMIN) THEN 
                VECTEUR_SECONDA(J)=VECTEUR_SECONDA(J)+
     F          VECTEUR_STOCKAGE(VECTEUR_DIAGONAL(J)-PTRCOL)
     L          *VECTEUR_SECONDMEMBRE(I)
                VECTEUR_STOCKAGE(VECTEUR_DIAGONAL(J)-PTRCOL) = 0.
               ENDIF
               PTRCOL = PTRCOL + 1

3         CONTINUE

1     CONTINUE

C     ------------BOUND GAMA4 --------------   
      WRITE(*,*) ' --------------Bound Gama4 ----------------'
      PTRCOL = 1
      DO 4 I=2*(N+1)+M+2,2*(N+M+2)
           IB = VECTEUR_BOUND(I)
           POS = VECTEUR_DIAGONAL(IB)
           VECTEUR_STOCKAGE(POS) = 1
           DEC = POS

C     SET ZERO -> LIGN I
           T = IB-VECTEUR_MIN(IB)
           DO 5 J=1,T
               DEC = DEC-1
               VECTEUR_STOCKAGE(DEC) = 0.
5          CONTINUE
      

      PTRCOL = 1
C     SET ZERO -> COLOGN I
           DO 6 J=IB+1,(N+1)*(M+1)
               PMIN = VECTEUR_MIN(J)
               IF(IB.GE.PMIN) THEN 
               VECTEUR_SECONDA(J)=VECTEUR_SECONDA(J)+
     F         VECTEUR_STOCKAGE(VECTEUR_DIAGONAL(J)-PTRCOL)
     L         *VECTEUR_SECONDMEMBRE(IB)
               VECTEUR_STOCKAGE(VECTEUR_DIAGONAL(J)-PTRCOL) = 0.
               ENDIF
               PTRCOL = PTRCOL+1 
6          CONTINUE

4     CONTINUE
      END
