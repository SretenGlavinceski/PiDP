#include<mpi.h>
#include<stdio.h>

int main(int argc, char **argv) {

    const int BUFFER_SIZE = 256;

    MPI_Init(NULL, NULL);


    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_size == 3) {

        char message_received[BUFFER_SIZE];

        for (int i = 0; i < 10; i++) {
            if (world_rank == 0) {
                char message_send[BUFFER_SIZE];
                sprintf(message_send, "This is random message from process %d, this is the %d time this message is send.\n", world_rank, i + 1);

                MPI_Send(message_send, BUFFER_SIZE, MPI_CHAR, 1, 0, MPI_COMM_WORLD);

                MPI_Recv(message_received, BUFFER_SIZE, MPI_CHAR, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("Message: %s", message_received);

            } else if (world_rank == 1) {

                MPI_Recv(message_received, BUFFER_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(message_received, BUFFER_SIZE, MPI_CHAR, 2, 0, MPI_COMM_WORLD);

            } else if (world_rank == 2) {

                MPI_Recv(message_received, BUFFER_SIZE, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(message_received, BUFFER_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

            }
        }

    } else {
        printf("Three processes are required for this program!\n");
    }

    MPI_Finalize();
}