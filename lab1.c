#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

int main(int argc, char *argv[]){
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // get N from command line
    int N = atoi(argv[1]);

    // calculate the range for each process
    int range = ceil((double) (N - 1) / size);
    int rangeStart = rank * range + 2;
    int rangeEnd = MIN(rangeStart + range - 1, N);

    bool *primes = malloc(sizeof(bool) * (range + 1));

    // initialize primes w/ true
    for(int i = 0; i <= range; i++){
        primes[i] = true;
    }

    // start timing
    double startTime;
    if (rank == 0) {
        startTime = MPI_Wtime();
    }

    for(int i = 2; i <= floor((N + 1) / 2); i++){
        int minMultiple = MAX(i*i, (rangeStart + i - 1) / i * i);
        if (minMultiple < rangeStart) minMultiple += i;

        for(int j = minMultiple; j <= rangeEnd; j += i){
            primes[j - rangeStart] = false;
        }
    }

    // gather all primes to rank 0
    int totalPrimes = 0;
    int *localPrimes = malloc(sizeof(int) * (range + 1));
    for(int i = 0; i <= rangeEnd - rangeStart; i++){
        if(primes[i]){
            localPrimes[totalPrimes++] = i + rangeStart;
        }
    }

    // end timing
    if (rank == 0) {
        double endTime = MPI_Wtime();
        double elapsedTime = endTime - startTime;

        // print elapsed time
        printf("Elapsed time: %f seconds\n", elapsedTime);
    }

    int *allPrimes = NULL;
    if(rank == 0) {
        allPrimes = malloc(sizeof(int) * N);
    }

    if(rank == 0) {
        // copy primes from rank 0
        for(int i = 0; i < totalPrimes; i++) {
            allPrimes[i] = localPrimes[i];
        }

        // receive primes from other ranks
        for(int i = 1; i < size; i++) {
            MPI_Status status;
            int recvcount;
            MPI_Recv(&recvcount, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            MPI_Recv(allPrimes + totalPrimes, recvcount, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            totalPrimes += recvcount;
        }
    } else {
        // send primes to rank 0
        MPI_Send(&totalPrimes, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(localPrimes, totalPrimes, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if(rank == 0) {
        // write primes to file
        char filename[20];
        sprintf(filename, "%d.txt", N);
        FILE *file = fopen(filename, "w");
        for(int i = 0; i < totalPrimes; i++) {
            fprintf(file, "%d ", allPrimes[i]);
        }
        fclose(file);
    }

    free(primes);
    free(localPrimes);
    if(rank == 0) {
        free(allPrimes);
    }
    MPI_Finalize();
    
    return 0;
}