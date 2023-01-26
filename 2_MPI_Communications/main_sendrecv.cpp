
#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) 
{
    MPI_Init(&argc,&argv);
    
    int rank, procs;
    MPI_Comm_size(MPI_COMM_WORLD, &procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int right = (rank + 1) % procs;
    int left = rank == 0 ? procs - 1 : rank - 1;
    
    int buffer1 = rank, buffer2 = -1;
    MPI_Sendrecv(&buffer1, 1, MPI_INT, right, 123, &buffer2, 1, MPI_INT, left,
    123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    
    std::cout<< "Process "<< buffer1<< " ";
    std::cout<< "recvs from "<< buffer2<< std::endl; 
    
    MPI_Finalize();
    return 0;
}
