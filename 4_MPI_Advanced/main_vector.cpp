
#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) 
{
    MPI_Init(&argc, &argv);
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    MPI_Status status;
    double a[4][4];
    for (unsigned int i = 0; i < 4; i++)
        for (unsigned int j = 0; j < 4; j++)
            a[i][j] = (rank == 0) ? i * 4.0 + j : 0.0;
    
    MPI_Datatype rowType, colType;
    
    MPI_Type_contiguous(4, MPI_DOUBLE, &rowType);
    MPI_Type_vector(4, 2, 4, MPI_DOUBLE, &colType);
    
    MPI_Type_commit(&rowType);
    MPI_Type_commit(&colType);
    
    if (rank == 0)
    {
        MPI_Send(&a[2][0], 1, rowType, 1, 10, MPI_COMM_WORLD);
        MPI_Send(&a[0][2], 1, colType, 1, 11, MPI_COMM_WORLD);
    }
    else if (rank == 1)
    {
        MPI_Recv(&a[2][0], 1, rowType, 0, 10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&a[0][2], 1, colType, 0, 11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    
    std::cout<< "Process "<< rank<< ": "<< std::endl;
    for (unsigned int i = 0; i < 4; i++)
    {
        for (unsigned int j = 0; j < 4; j++)
            std::cout<< (j == 0 ? "" : ", ")<< a[i][j];
        std::cout<< std::endl;
    }
    
    MPI_Type_free(&rowType);
    MPI_Type_free(&colType);
    
    MPI_Finalize();
    return 0;
}
