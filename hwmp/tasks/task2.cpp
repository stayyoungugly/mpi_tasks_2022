#include <mpi.h>
#include <cstdio>
#include <cstdlib>

int main(int argc, char **argv) {

    const int N = 20;
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

    MPI_Bcast(a, N, MPI_INT, 0, MPI_COMM_WORLD);

    int k = N / size;
    int i1 = k * rank;
    int i2 = k * (rank + 1);
    if (rank == size - 1)
        i2 = N;

    int max = -1;

    for (int i = i1; i < i2; i++)
        if (a[i] >= max) {
            max = a[i];
        }

    printf("Rank = %d, Max = %d\n", rank, max);

    int totalMax;

    MPI_Reduce(&max, &totalMax, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (!rank) printf("totalMax = %d", totalMax);

    MPI_Finalize();
}
// mpiexec ./cmake-build-release/task2