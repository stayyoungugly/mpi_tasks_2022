#include <mpi.h>
#include <cstdio>
#include <cstdlib>
#include <time.h>

int main(int argc, char **argv) {
    // координаты точек
    double x, y;

    // число точек
    int N = 1000000;

    MPI_Init(NULL, NULL);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // точек для каждого процесса
    int k = N / size;

    // точки текущего процесса
    int points = 0;

    // общее число точек
    int totalPoints = 0;

    srand(time(nullptr));

    if (rank == size - 1) {
        int new_k = N - size * k;
        k += new_k;
    }

    // процессы генерируют точки
    for (int i = 0; i < k; i++) {
        x = (double) rand() / (double) RAND_MAX;
        y = (double) rand() / (double) RAND_MAX;

        // увеличиваем счетчик, если точки внутри круга
        if (x * x + y * y <= 1)
            points++;

    }

    printf("Rank = %d, Points = %d\n", rank, points);

    MPI_Reduce(&points, &totalPoints, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (!rank) {
        double pi = (double) (4 * totalPoints) / (double) N;
        printf("Number Pi = %f while POINTS = %d", pi, totalPoints);
    }

    MPI_Finalize();
}
// mpiexec ./cmake-build-release/task3