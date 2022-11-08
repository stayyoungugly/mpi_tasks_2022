#include <mpi.h>
#include <cstdio>
int main(int argc, char **argv) {
    MPI_Init(NULL, NULL);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("Hello world from rank %d out of %d processors\n", rank, size);

    MPI_Finalize();

    // mpiexec ./cmake-build-release/task1
}