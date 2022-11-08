#include <mpi.h>
#include <cstdio>
#include <cstdlib>

int main(int argc, char **argv) {
    const int N = 100;
    int a1[N];
    int a2[N];

    MPI_Init(NULL, NULL);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (!rank) {
        for (int i = 0; i < N; i++) {
            a1[i] = rand() % 100;
            a2[i] = rand() % 10;
        }
    }

    int *counts = new int[size];
    int *indexes = new int[size];

    int rest = N;
    int k = N / size;
    counts[0] = k;
    indexes[0] = 0;

    for (int i = 1; i < size; i++) {
        rest -= k;
        k = rest / (size - i);
        counts[i] = k;
        indexes[i] = indexes[i - 1] + counts[i - 1];
    }

    int nProc = counts[rank];
    int *a1Proc = new int[nProc];
    int *a2Proc = new int[nProc];

    MPI_Scatterv(a1, counts, indexes, MPI_INT, a1Proc, nProc, MPI_INT,
                 0, MPI_COMM_WORLD);

    MPI_Scatterv(a2, counts, indexes, MPI_INT, a2Proc, nProc, MPI_INT,
                 0, MPI_COMM_WORLD);

    long long int sum = 0;

    for (int i = 0; i < nProc; i++) {
        sum += (long int) (a1Proc[i] * a2Proc[i]);
    }

    printf("Rank = %d, Sum = %d, Count = %d\n", rank, sum, nProc);

    long long int totalSum = 0;

    MPI_Reduce(&sum, &totalSum, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (!rank) {
        printf("Sum = %d", totalSum);
    }

    MPI_Finalize();
}

// mpiexec ./cmake-build-release/task5