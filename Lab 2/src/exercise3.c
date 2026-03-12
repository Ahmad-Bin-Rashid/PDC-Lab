#include <stdio.h>
#include <mpi.h>

#define ARRAY_SIZE 10

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank != 0) {
        // Worker: generate array and send to process 0
        int data[ARRAY_SIZE];
        for (int i = 0; i < ARRAY_SIZE; i++) {
            data[i] = rank * 100 + i;
        }
        MPI_Send(data, ARRAY_SIZE, MPI_INT, 0, rank, MPI_COMM_WORLD);
    } else {
        // Master: receive arrays from all workers and print them
        int recv_buf[ARRAY_SIZE];

        for (int j = 1; j < size; j++) {
            
            MPI_Recv(recv_buf, ARRAY_SIZE, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            int source = status.MPI_SOURCE;
            printf("Process 0 received from %d:", source);

            for (int i = 0; i < ARRAY_SIZE; i++) {
                printf(" %d", recv_buf[i]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}
