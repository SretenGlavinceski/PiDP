#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
    const int TAG = 0;
    const int BUF_SIZE = 100;
    int numOfTasks, rank;

    MPI_Request req[2];
    MPI_Status stats[2];

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &numOfTasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (numOfTasks == 2) {
        char send_buf[BUF_SIZE];
        char receive_buf[BUF_SIZE];

        sprintf(send_buf, "Message from process %d", rank);

        int process_from = rank == 1 ? 0 : 1;

        MPI_Irecv(receive_buf, BUF_SIZE, MPI_CHAR, process_from, TAG, MPI_COMM_WORLD, &req[0]);
        MPI_Isend(send_buf, BUF_SIZE, MPI_CHAR, process_from, TAG, MPI_COMM_WORLD, &req[1]);

        MPI_Waitall(2, req, stats);

        printf("This is process: %d, message received: %s", rank, receive_buf);
    }

    MPI_Finalize();
    return 0;
}