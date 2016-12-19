      SUBROUTINE GETFJ(X,Y,FUNC,FJ)
      IMPLICIT NONE
      INTEGER  I,J,FUNC
      REAL X(3),Y(3),FJ(3),DETJ
      DETJ=1
      DETJ=(X(2)-X(1))*(Y(3)-Y(1))-(Y(2)-Y(1))*(X(3)-X(1))
      WRITE(*,*) 'DETERMINANT:',DETJ
      WRITE(*,*) '  '
      FJ(1) = (FUNC*DETJ)/6
      FJ(2) = (FUNC*DETJ)/6
      FJ(3) = (FUNC*DETJ)/6
      WRITE(*,*) ' FJ ',FJ(1)
      END
