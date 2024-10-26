#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

#define NUM_ELEMENTS 100

double find_average(double const *arr, int size) {
    double avr = 0;
    for (int i = 0; i < size; i++) {
        avr += (double)arr[i];
    }
    return avr / (double)size;
}

int main(int argc, char **argv) {

    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    double array[NUM_ELEMENTS];
    if (world_rank == 0) {
        for (int i = 0; i < NUM_ELEMENTS; i++)
            array[i] = i;
    }

    int sub_array_size = NUM_ELEMENTS / world_size;
    double *sub_array = malloc(sizeof(double) * sub_array_size);

    MPI_Scatter(array, sub_array_size, MPI_DOUBLE,
                sub_array, sub_array_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double average = find_average(sub_array, sub_array_size);
    printf("Rank %d local average: %.2f\n", world_rank, average);

    double *local_averages = NULL;
    if (world_rank == 0) {
        local_averages = malloc(sizeof(double) * world_size);
    }

    MPI_Gather(&average, 1, MPI_DOUBLE,
               local_averages,1, MPI_DOUBLE,0,MPI_COMM_WORLD);

    if (world_rank == 0) {
        printf("Global average: %.2f\n", find_average(local_averages, world_size));
    }

    MPI_Finalize();

}