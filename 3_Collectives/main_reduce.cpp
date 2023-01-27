
#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) 
{
    MPI_Init(&argc, &argv);
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    MPI_Status status;
    int a[2] = { rank, rank + 1 };
    int sum[2] = { 0, 0 };
    
    std::cout<< "Before Process "<< rank<< " ";
    std::cout<< "a: "<< a[0]<< ", "<< a[1]<< std::endl;
    
    MPI_Reduce(&a, &sum, 2, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
            
    std::cout<< "After Process "<< rank<< " ";
    std::cout<< "sum: "<< sum[0]<< ", "<< sum[1]<< std::endl;
    
    MPI_Finalize();
    return 0;
}
