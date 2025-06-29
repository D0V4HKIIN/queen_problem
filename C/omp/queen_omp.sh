mkdir -p bin && gcc queen_omp.c -o bin/queen_omp -fopenmp && ./bin/queen_omp $1
