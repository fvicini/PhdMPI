
#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) 
{
    MPI_Init(&argc, &argv);
    
    int process_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    
    int tag = 10;
    float a[2] = { 0.0, 0.0 };
    float b[2] = { 0.0, 0.0 };
    MPI_Status status;
    
    if (process_rank == 0)
    {
        a[0] = 1.0; a[1] = 2.0;
        MPI_Recv(&b, 2, MPI_FLOAT, 1, tag + 1, MPI_COMM_WORLD, &status);
        MPI_Send(&a, 2, MPI_FLOAT, 1, tag, MPI_COMM_WORLD);
    }
    else if (process_rank == 1)
    {
        b[0] = 3.0; b[1] = 4.0;
        MPI_Recv(&a, 2, MPI_FLOAT, 0, tag, MPI_COMM_WORLD, &status);
        MPI_Send(&b, 2, MPI_FLOAT, 0, tag + 1, MPI_COMM_WORLD);
    }
        
    std::cout<< "Process "<< process_rank<< " ";
    std::cout<< "Status SOURCE: "<< status.MPI_SOURCE<< " ";
    std::cout<< "TAG: "<< status.MPI_TAG<< " ";
    std::cout<< "ERROR: "<< status.MPI_ERROR<< std::endl;
        
    std::cout<< "Process "<< process_rank<< " ";
    std::cout<< "a "<< a[0]<< ", "<< a[1]<< " ";
    std::cout<< "b "<< b[0]<< ", "<< b[1]<< std::endl; 
    
    MPI_Finalize();
    return 0;
}
