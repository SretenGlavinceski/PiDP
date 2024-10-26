#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {

    MPI_Init(NULL, NULL);

    char string[3] = "ABC";

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank == 0)
        sprintf(string, "123");

    printf("Rank: %d, characters before broadcast: %s\n", world_rank, string);

    MPI_Bcast(&string,sizeof(string),MPI_CHAR,0,MPI_COMM_WORLD);

    printf("Rank: %d, characters after broadcast: %s\n", world_rank, string);

    MPI_Finalize();


    return 0;
}
