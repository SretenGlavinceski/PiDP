#include<mpi.h>
#include<stdio.h>

const int ARRAY_SIZE = 16;
const int SIZE_SUBARRAY = ARRAY_SIZE / 4;

int sum_array(const int array[], int size) {
    int sum = 0;
    for (int i = 0; i < size ;i++) {
        sum += array[i];
    }
    return sum;
}

int main(int argc, char **argv) {

    int arr [] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int send_arr[SIZE_SUBARRAY];
    int start = world_rank * 4;
    int end = start + SIZE_SUBARRAY;

    for (int i = start, j = 0; i < end; i++)
        send_arr[j++] = arr[i];

    if (world_size == 4) {

        if (world_rank != 3) {

            MPI_Send(send_arr, SIZE_SUBARRAY, MPI_INT, 3, 0, MPI_COMM_WORLD);
        } else {
            int total_sum = sum_array(send_arr, SIZE_SUBARRAY);

            for (int i = 0; i < 3; i++) {
                MPI_Recv(send_arr, SIZE_SUBARRAY, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                total_sum += sum_array(send_arr, SIZE_SUBARRAY);
                printf("I'm process %d, received array from process: %d\n", world_rank, i);
            }

            printf("Total sum for array: %d\n", total_sum);
        }

    } else {
        printf("Four processes are needed for this program!\n");
    }

    MPI_Finalize();
}