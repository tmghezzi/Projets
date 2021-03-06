      PROGRAM  PRINCIPAL
      IMPLICIT NONE
      INTEGER I,J,K,N,M,NBP,BI,TYPEPROB

      REAL VECTEURX(1000),VECTEURY(1000),X(3),Y(3),AIJ(6),
     B VECTEUR_STOCKAGE(1000),VECTEUR_SECONDMEMBRE(1000),
     C FJ(3),CONDNEWMAN(4),VECTEUR_SECONDA(1000),
     L VECTEURCHOLESKY(1000),VECTEURSOL(1000)
     

      INTEGER VECTEUR_TRIANGLE(1000),VECTEUR_BOUND(1000),
     A     VECTEUR_B1(100),VECTEUR_B2(100),
     C     VECTEUR_B3(100),VECTEUR_B4(100),
     B     VECTEUR_MIN(1000),SIZEMAX,VECTEUR_DIAGONAL(1000),FUNC

C     /********************* INIT VARIABLE *****************/
      N=4
      M=4
      NBP = 1
      FUNC = -4

C     On récupere les différents parametres pour discrétisé notre espace
      WRITE(*,*) 'Nombre de subdivision sur x ?'
      READ(*,*) N
      WRITE(*,*) 'Nombre de subdivision sur Y ?'
      READ(*,*) M
      WRITE(*,*) 'Type de probléme:'
      READ(*,*) TYPEPROB
      
      WRITE(*,*) 'Nombre de subdivision x :',N
      WRITE(*,*) 'Nombre de subdivision y :',M
      WRITE(*,*) 'Probleme type:',TYPEPROB

C     Définition des conditions pour chaque probléme
      IF(TYPEPROB.EQ.1) THEN
      CONDNEWMAN(1) = 0.0
      CONDNEWMAN(2) = 1.0
      CONDNEWMAN(3) = 1.0
      CONDNEWMAN(4) = 0.0
      FUNC = 0.0
      ELSE IF(TYPEPROB.EQ.2) THEN
      CONDNEWMAN(1) = 0.0
      CONDNEWMAN(2) = 40.0
      CONDNEWMAN(3) = 20.0
      CONDNEWMAN(4) = 0.0
      FUNC = -4.0
      ENDIF

C     /***********  Calcul des coordonnées pour chaque noeuds ************/
      DO 1 J=0,M
        DO 2 I=0,N
        VECTEURX(NBP)=(20.0*I)/N
        VECTEURY(NBP)=(10.0*J)/M      
        WRITE(*,*) 'Node: ',VECTEURX(NBP),VECTEURY(NBP)
        NBP=NBP+1
2     CONTINUE
1     CONTINUE

C     Récupération des noeuds pour chaque triangles
C     VECTEUR_TRIANGLE:contient les noeuds de l'ensemble des triangles
      WRITE(*,*) '/---------------TRIANGLE NODES-----------------/'
      CALL GETTRIANGLENODE(N,M,VECTEUR_TRIANGLE)
      WRITE(*,*) ''


C     Récupération des noeuds pour chaque bords
C     VECTEUR_B1:Contient les noeuds pour l'ensemble des bords       
      WRITE(*,*) '/--------------BOUNDARY NODES----------------/'
      CALL GETBOUNDNODE(N,M,VECTEUR_B1)
      DO 3 BI=1,2*(M+N+2)
           write(*,*) 'Boundary node ',BI,':',VECTEUR_B1(BI)
3     CONTINUE
      WRITE(*,*) ''



C     Récupération de la colonne min pour chaque ligne de la matrice, afin d'éffectuer un stockage de type morse
C     Vecteur_min:Retourne la colonne min
      WRITE(*,*) '/----------------MIN MATRICE------------------/'
C     /************* GET MIN No Nul MATRICE ***********/
      CALL GETVECTEURMIN(N,M,VECTEUR_MIN)
      DO 9 I=1,(N+1)*(M+1)
           WRITE(*,*) 'VECTEUR_MIN ',I,': ',VECTEUR_MIN(I) 
9     CONTINUE  
      WRITE(*,*) ''



C     Stockage des positions des coefficients de la matrice appartenant à la diagonale
C     Vecteur_diagonal:Retourne les positions pour l'ensemble des lignes 
      WRITE(*,*) '/--------------POSITION DIAGONAL----------------/'
      CALL GETVECTEURDIAGONAL(N,M,VECTEUR_MIN,SIZEMAX,
     P VECTEUR_DIAGONAL)
      DO 10 I=1,(N+1)*(M+1)
            WRITE(*,*) 'VECTEUR DIAGONAL',VECTEUR_DIAGONAL(I)
10    CONTINUE
      WRITE(*,*) ''




C    Calcul de la matrice AIJ et du second membre
C    /********** GET AIJ FOR EACH TRIANGLE************/
      K=1
      DO 7 I=1,2*N*M
      X(1)= VECTEURX(VECTEUR_TRIANGLE(K))
      X(2)= VECTEURX(VECTEUR_TRIANGLE(K+1))
      X(3)= VECTEURX(VECTEUR_TRIANGLE(K+2))
      Y(1)= VECTEURY(VECTEUR_TRIANGLE(K))
      Y(2)= VECTEURY(VECTEUR_TRIANGLE(K+1))
      Y(3)= VECTEURY(VECTEUR_TRIANGLE(K+2))

      WRITE(*,*) 'Noeud n°1 Triangle :  ',VECTEUR_TRIANGLE(K)
      WRITE(*,*) 'Noeud n°2 Triangle :  ',VECTEUR_TRIANGLE(K+1)
      WRITE(*,*) 'Noeud n°3 Triangle :  ',VECTEUR_TRIANGLE(K+2)

C     Récupération des Coefficients
      CALL GETFJ(X,Y,FUNC,FJ)
      CALL GETAIJ(X,Y,AIJ)
      
C     Stockage du second membre
      CALL STOCKSECONDMEMBRE(N,M,K,FJ,VECTEUR_TRIANGLE,
     L VECTEUR_B1,VECTEUR_SECONDMEMBRE)

C     Stockage de la matrice A
      CALL STOCKAGEMATRIXAIJ(N,M,K,SIZEMAX,AIJ,VECTEUR_DIAGONAL,
     M VECTEUR_TRIANGLE,VECTEUR_STOCKAGE)
      WRITE(*,*) ' '
      
      DO 8 J=1,6
      WRITE(*,*) 'AIJ DU TRIANGLE n°',I,' AIJ ',AIJ(J)
8     CONTINUE
      WRITE(*,*) ' '
      K = K+3
7     CONTINUE
C    /********** END GET AIJ and FJ************/


C    Application des conditions de newman sur le second membre     
      CALL NEWMANSECONDMEMBRE(N,M,VECTEUR_TRIANGLE,
     L VECTEUR_B1,CONDNEWMAN,
     F VECTEURX,VECTEURY,VECTEUR_SECONDMEMBRE)


C     Affichage du second membre aprés l'application des conditions de newman
      WRITE(*,*) ''
      WRITE(*,*) '/********Newman VECTEUR SECONDMEMBRE :**********/'
      DO 14 I=1,(N+1)*(M+1)
           WRITE(*,*) 'VECTEUR SECONDMEMBRE Newman:',I,
     L      VECTEUR_SECONDMEMBRE(I)
14    CONTINUE
      WRITE(*,*) ''


      WRITE(*,*) '/************AIJ BEFORE DIRICHLET*****************/'
      DO 11 I=1,SIZEMAX
            WRITE(*,*) 'AIJ MORSE ',I,' AIJ ',VECTEUR_STOCKAGE(I)
11    CONTINUE
      WRITE(*,*) ''

C    Application des conditions de dirichlet sur le second membre 
      CALL DIRICHLETSECONDMEMBRE(N,M,VECTEUR_TRIANGLE,
     G VECTEUR_B1,TYPEPROB,
     J VECTEURX,VECTEURY,VECTEUR_SECONDMEMBRE)

C     Application des conditions de dirichlet sur la matrice A
C     Retourne:Vecteur_seconda qui contient les modifications à appliquer sur le secondmembre (Secondmembre - Vecteur_seconda)
C    /********** APPLY DIRICHLET CONDITION *********/   
      CALL CONDITION_DIRICHLET(N,M,SIZEMAX,VECTEUR_MIN
     L ,VECTEUR_B1,VECTEUR_DIAGONAL,VECTEUR_SECONDMEMBRE
     L ,VECTEUR_STOCKAGE,VECTEUR_SECONDA) 
 
      WRITE(*,*) '/************AFTER DIRICHLET*****************/'
      DO 12 I=1,SIZEMAX
      WRITE(*,*) 'AIJ VECTEUR MORSE ',I,' AIJ ',VECTEUR_STOCKAGE(I)
12    CONTINUE
      WRITE(*,*) ''

C      Affichage du nouveau second membre
       DO 13 I=1,(N+1)*(M+1)
          VECTEUR_SECONDMEMBRE(I) = VECTEUR_SECONDMEMBRE(I)-
     L    VECTEUR_SECONDA(I)
          WRITE(*,*) 'VECTEUR SECONDMEMBRE:',I,
     L    VECTEUR_SECONDMEMBRE(I),VECTEUR_SECONDA(I)
13     CONTINUE
       WRITE(*,*) ''

      CALL DIRICHLETSECONDMEMBRE(N,M,VECTEUR_TRIANGLE,
     G VECTEUR_B1,TYPEPROB,
     J VECTEURX,VECTEURY,VECTEUR_SECONDMEMBRE)

      WRITE(*,*) ''
      WRITE(*,*) '/***********Second membre final !!!**************/'
       DO 15 I=1,(N+1)*(M+1)
       WRITE(*,*) 'VECTEUR SECONDMEMBRE FINAL:',I,
     L VECTEUR_SECONDMEMBRE(I)
15    CONTINUE
      WRITE(*,*) ''


C     Application de l'algorithme de factorisation de Cholesky
C     Retourne:VECTEURCHOLESKY 
      CALL CHOLESKY(N,M,SIZEMAX,VECTEUR_DIAGONAL,VECTEUR_MIN,
     L VECTEUR_STOCKAGE,VECTEURCHOLESKY)
       DO 16 I=1,SIZEMAX
       WRITE(*,*) 'Matrice de Cholesky:',I,
     L VECTEURCHOLESKY(I)
16    CONTINUE
      WRITE(*,*) ''

C     Résolution du système AU = F 
C     Retourne:VECTEURSOL qui contient la solution du systéme
      CALL RESOLUTION(N,M,SIZEMAX,VECTEUR_MIN,VECTEUR_DIAGONAL,
     L VECTEURCHOLESKY,VECTEUR_SECONDMEMBRE,VECTEURSOL)

       DO 17 I=1,(N+1)*(M+1)
       WRITE(*,*) 'RESOLUTION:',I,
     L VECTEURSOL(I)
17    CONTINUE
      END
      
