#include<mpi.h>
#include<stdio.h>

int main(int argc, char **argv) {

    const int BUFFER_SIZE = 256;

    MPI_Init(NULL, NULL);


    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_size == 2) {

        char message_send[BUFFER_SIZE];
        char message_received[BUFFER_SIZE];
        sprintf(message_send, "Hello from processor %d", world_rank);

        if (world_rank == 0) {
            MPI_Send(message_send, BUFFER_SIZE, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
            MPI_Recv(message_received, BUFFER_SIZE, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        } else if (world_rank == 1) {
            MPI_Recv(message_received, BUFFER_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(message_send, BUFFER_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

        }

        printf("This is processor with rank: %d, i send the message: %s, i received the message: %s",
               world_rank,
               message_send,
               message_received);

    } else {
        printf("Only two processes allowed in this program!");
    }

    MPI_Finalize();
}