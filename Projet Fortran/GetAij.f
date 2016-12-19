      SUBROUTINE GETAIJ(X,Y,AIJ)
      IMPLICIT NONE
      INTEGER  I,J
      REAL X(3),Y(3),AIJ(6),DETJ
      DETJ=1
      DETJ=(X(2)-X(1))*(Y(3)-Y(1))-(Y(2)-Y(1))*(X(3)-X(1))
      WRITE(*,*) 'DETERMINANT: ',DETJ
      WRITE(*,*) '  '
      IF(DETJ.EQ.0) THEN
      ELSE
      AIJ(1)=(1/(2*DETJ))*((Y (2)-Y(3))*(Y(2)-Y(3))+
     R (X(3)-X(2))*(X(3)-X(2)))
      AIJ(2)=(1/(2*DETJ))*((Y(2)-Y(3))*(Y(3)-Y(1))+
     R (X(3)-X(2))*(X(1)-X(3)))
      AIJ(4)=(1/(2*DETJ))*((Y(3)-Y(1))*(Y(3)-Y(1))+
     R (X(1)-X(3))*(X(1)-X(3)))
      AIJ(3)=(1/(2*DETJ))*((Y(2)-Y(3))*(Y(1)-Y(2))+
     R (X(3)-X(2))*(X(2)-X(1)))
      AIJ(5)=(1/(2*DETJ))*((Y(3)-Y(1))*(Y(1)-Y(2))+
     R (X(1)-X(3))*(X(2)-X(1)))
      AIJ(6)=(1/(2*DETJ))*((Y(1)-Y(2))*(Y(1)-Y(2))+
     R (X(2)-X(1))*(X(2)-X(1)))
      ENDIF
      END
