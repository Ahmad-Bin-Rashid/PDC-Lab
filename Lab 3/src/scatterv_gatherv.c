#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 1000 // total array size

int main(int argc, char **argv)
{
    int rank, size;
    int *array = NULL;
    int *local_array;
    int *recvcounts = NULL; // number of elements to send/recv for each process
    int *displs = NULL;     // displacements in the global array
    int local_n;
    int local_sum = 0, total_sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // All processes compute sendcounts and displacements
    recvcounts = (int *)malloc(size * sizeof(int));
    displs = (int *)malloc(size * sizeof(int));
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        recvcounts[i] = N / size;
        if (i < N % size)
            recvcounts[i]++; // first remainder processes get one extra
        displs[i] = sum;
        sum += recvcounts[i];
    }
    local_n = recvcounts[rank];

    // Root initialises the full array
    if (rank == 0)
    {
        array = (int *)malloc(N * sizeof(int));
        for (int i = 0; i < N; i++)
            array[i] = i + 1;
    }

    // Allocate local array
    local_array = (int *)malloc(local_n * sizeof(int));

    // Scatter the actual data using MPI_Scatterv (handles uneven distribution)
    MPI_Scatterv(array, recvcounts, displs, MPI_INT, local_array, local_n, MPI_INT, 0, MPI_COMM_WORLD);

    // Compute local sum
    for (int i = 0; i < local_n; i++)
        local_sum += local_array[i];
    printf("Process %d: received %d elements, local sum = %d\n", rank, local_n, local_sum);

    // Use MPI_Reduce to get total sum
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Use MPI_Gatherv to collect all local arrays back to root
    int *gathered = NULL;
    if (rank == 0)
        gathered = (int *)malloc(N * sizeof(int));

    MPI_Gatherv(local_array, local_n, MPI_INT, gathered, recvcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Total sum via MPI_Reduce = %d\n", total_sum);
        printf("Expected total sum = %d\n", N * (N + 1) / 2);

        // Verify gathered data matches original
        int match = 1;
        for (int i = 0; i < N; i++)
        {
            if (gathered[i] != array[i])
            {
                match = 0;
                break;
            }
        }
        printf("MPI_Gatherv verification: %s\n", match ? "PASS" : "FAIL");

        free(array);
        free(gathered);
    }

    free(recvcounts);
    free(displs);
    free(local_array);
    MPI_Finalize();
    return 0;
}