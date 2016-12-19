compilation:
-mpic++ main.cpp ConjugateGradient.c blas1.c -o Test

exec:
-mpirun -np 2  Test

