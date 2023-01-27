
#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) 
{
    MPI_Init(&argc, &argv);
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    MPI_Status status;
    int a[8] = { 0 };
    if ( rank == 0 ) 
    {
        for (unsigned int i = 0; i < 8; i++)
            a[i] = i + 1; 
    }
    
    // send the information to all the other processes
    MPI_Scatter(a, 2, MPI_INT, a, 2, MPI_INT, 0, MPI_COMM_WORLD);
    
    std::cout<< "Before Process "<< rank<< " ";
    std::cout<< "a: ";
    for (unsigned int i = 0; i < 8; i++)
        std::cout<< (i == 0 ? "" : ", ")<< a[i];
    std::cout<< std::endl;
        
    a[0] *= 2;
    a[1] *= 2;
    
    // get the information from the other processes
    MPI_Gather(a, 2, MPI_INT, a, 2, MPI_INT, 0, MPI_COMM_WORLD);
    
    // stop processes to obtain a good output
    MPI_Barrier(MPI_COMM_WORLD);
    
    std::cout<< "After Process "<< rank<< " ";
    std::cout<< "a: ";
    for (unsigned int i = 0; i < 8; i++)
        std::cout<< (i == 0 ? "" : ", ")<< a[i];
    std::cout<< std::endl;
    
    MPI_Finalize();
    return 0;
}
