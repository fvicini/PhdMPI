
#include <iostream>
#include <mpi.h>

int main(int argc, char **argv)
{
    int err;
    err = MPI_Init(&argc, &argv);
    
    int nprocs, my_rank;
    
    // Get the number of processes in MPI_COMM_WORLD
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    
    // Get the rank of this process in MPI_COMM_WORLD
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    std::cout<< "Hello I am process "<< my_rank<< " of "<< nprocs<< " processes"<< std::endl; 
    
    err = MPI_Finalize();
    
    return 0;
}
