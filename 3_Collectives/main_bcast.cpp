
#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) 
{
    MPI_Init(&argc, &argv);
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    MPI_Status status;
    double a[2] = { 0.0, 0.0 };
    if ( rank == 0 ) 
    {
        a[0] = 2.1; 
        a[1] = 4.3;
    }
    
    // send the information to all the other processes
    MPI_Bcast(a, 2, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    std::cout<< "Process "<< rank<< " ";
    std::cout<< "a "<< a[0]<< ", "<< a[1]<< std::endl; 
    
    MPI_Finalize();
    return 0;
}
