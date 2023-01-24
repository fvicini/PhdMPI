
#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) 
{
    // Initialize MPI
    // This must always be called before any other MPI functions
    MPI_Init(&argc, &argv);
    
    std::cout<< "Hello world!"<< std::endl;

    // Finalize MPI
    // This must always be called after all other MPI functions
    MPI_Finalize();

    return 0;
}
