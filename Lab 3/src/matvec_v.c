#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define M 10 // number of rows (not necessarily divisible by size)
#define N 8  // number of columns

int main(int argc, char **argv)
{
    int rank, size;
    double *A = NULL; // full matrix on root
    double *local_A;  // local rows
    double *x;        // vector (replicated on all processes)
    double *local_y;  // local result for local rows
    double *y = NULL;  // full result on root
    int local_rows;

    int *sendcounts_A; // number of doubles to send for matrix rows
    int *displs_A;     // displacements for matrix rows
    int *recvcounts_y; // number of doubles to gather for result
    int *displs_y;     // displacements for result

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Compute row distribution for all processes
    sendcounts_A = (int *)malloc(size * sizeof(int));
    displs_A = (int *)malloc(size * sizeof(int));
    recvcounts_y = (int *)malloc(size * sizeof(int));
    displs_y = (int *)malloc(size * sizeof(int));

    int row_offset = 0;
    for (int i = 0; i < size; i++)
    {
        int rows_i = M / size + (i < M % size ? 1 : 0);
        recvcounts_y[i] = rows_i;          // number of result elements
        displs_y[i] = row_offset;
        sendcounts_A[i] = rows_i * N;      // number of matrix elements (rows * cols)
        displs_A[i] = row_offset * N;
        row_offset += rows_i;
    }
    local_rows = recvcounts_y[rank];

    // Allocate local storage
    local_A = (double *)malloc(local_rows * N * sizeof(double));
    local_y = (double *)malloc(local_rows * sizeof(double));
    x = (double *)malloc(N * sizeof(double));

    // Root initialises matrix and vector
    if (rank == 0)
    {
        A = (double *)malloc(M * N * sizeof(double));
        y = (double *)malloc(M * sizeof(double));

        // Initialise A as a simple matrix (e.g., all 1's)
        for (int i = 0; i < M * N; i++)
            A[i] = 1.0;

        // Initialise x as a vector of 1's
        for (int i = 0; i < N; i++)
            x[i] = 1.0;
    }

    // Broadcast vector x to all processes
    MPI_Bcast(x, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Scatter rows of A using Scatterv (handles uneven row distribution)
    MPI_Scatterv(A, sendcounts_A, displs_A, MPI_DOUBLE,
                 local_A, local_rows * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Compute local matrix-vector product
    for (int i = 0; i < local_rows; i++)
    {
        local_y[i] = 0.0;
        for (int j = 0; j < N; j++)
        {
            local_y[i] += local_A[i * N + j] * x[j];
        }
    }

    // Gather all local_y into y on root using Gatherv
    MPI_Gatherv(local_y, local_rows, MPI_DOUBLE,
                y, recvcounts_y, displs_y, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Result vector y (M=%d, N=%d, %d processes):\n", M, N, size);
        for (int i = 0; i < M; i++)
            printf("%f ", y[i]);
        printf("\n");
        free(A);
        free(y);
    }

    free(sendcounts_A);
    free(displs_A);
    free(recvcounts_y);
    free(displs_y);
    free(local_A);
    free(local_y);
    free(x);
    MPI_Finalize();
    return 0;
}
