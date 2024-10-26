#include<mpi.h>
#include<stdio.h>

int main(int argc, char **argv) {

    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    double start_time = MPI_Wtime();

    MPI_Barrier(MPI_COMM_WORLD);

    double end_time = MPI_Wtime();
    double total_waiting = end_time - start_time;

    printf("Rank: %d waited for %f seconds.", world_rank, total_waiting);

    MPI_Finalize();
}