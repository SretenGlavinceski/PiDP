#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int numTasks, rank;
    char send_buf[100];
    char receive_buf[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numTasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (numTasks > 3) {
        MPI_Request req[numTasks];
        MPI_Status status[numTasks];

        if (rank == 0) {
            sprintf(send_buf, "Message from process %d to All others.", rank);

            for (int i = 1; i < numTasks; i++) {
                MPI_Isend(send_buf, 100, MPI_CHAR, i, 0, MPI_COMM_WORLD, &req[i]);
            }

            MPI_Irecv(receive_buf, 100, MPI_CHAR, numTasks - 1, 0, MPI_COMM_WORLD, &req[0]);

            MPI_Waitall(numTasks, req, status);
            printf("Process 0 send messages to all others. Received message: %s\n", receive_buf);

        } else {
            MPI_Irecv(receive_buf, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &req[0]);

            int wait = 1;

            if (rank == numTasks - 1) {
                sprintf(send_buf, "Reply from process %d", rank);
                MPI_Isend(send_buf, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &req[1]);

                wait++;
            }

            MPI_Waitall(wait, req, status);

            printf("Process %d received message from process 0: %s\n", rank, receive_buf);

        }
    }

    MPI_Finalize();
    return 0;
}
