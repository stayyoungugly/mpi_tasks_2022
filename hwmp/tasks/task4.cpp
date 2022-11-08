#include <mpi.h>
#include <cstdio>
#include <cstdlib>

int main(int argc, char **argv) {
    const int N = 100;
    int a[N];

    MPI_Init(NULL, NULL);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (!rank) {
        for (int i = 0; i < N; i++) {
            a[i] = rand() % 100;
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
    int *aProc = new int[nProc];

    MPI_Scatterv(a, counts, indexes, MPI_INT, aProc, nProc, MPI_INT,
                 0, MPI_COMM_WORLD);

    int sum = 0;
    int count = 0;
    for (int i = 0; i < nProc; i++) {
        sum += aProc[i];
        count++;
    }

    printf("Rank = %d, Sum = %d, Count = %d\n", rank, sum, count);

    int result[2];
    int totalResult[2];

    result[0] = count;
    result[1] = sum;

    MPI_Reduce(result, totalResult, 2, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (!rank) {
        double average = (double) totalResult[1] / (double) totalResult[0];
        printf("Average = %f, Sum = %d, Count = %d\n", average, totalResult[1], totalResult[0]);
    }

    MPI_Finalize();
}