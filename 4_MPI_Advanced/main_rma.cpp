
#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) 
{
    MPI_Init(&argc, &argv);
    
    int rank, nprocs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    MPI_Win window;
    int shared_buffer[2] = { rank, rank };
    // create a simple RMA window of 2 integers
    MPI_Win_create(shared_buffer, sizeof(int) * 2, sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &window);
    
    MPI_Win_fence(0, window); // synchronization
    
    int local_buffer[2] = { rank + 2, rank + 4 };
    int get_local_buffer[2] = { 0, 0 };
    
    if (rank == 0)
        MPI_Get(get_local_buffer, 2, MPI_INT, 1, 0, 2, MPI_INT, window);
    else if (rank == 1)
        MPI_Get(get_local_buffer, 2, MPI_INT, 0, 0, 2, MPI_INT, window);
    
    MPI_Win_fence(0, window); // synchronization
    
    std::cout<< "Process "<< rank<< ": ";
    std::cout<< "shared_buffer "<< shared_buffer[0]<< " "<< shared_buffer[1]<< " ";
    std::cout<< "local_buffer "<< local_buffer[0]<< " "<< local_buffer[1]<< " ";
    std::cout<< "get_local_buffer "<< get_local_buffer[0]<< " "<< get_local_buffer[1]<< std::endl;
    
    if (rank == 0)
        MPI_Put(local_buffer, 2, MPI_INT, 1, 0, 2, MPI_INT, window);
    else if (rank == 1)
        MPI_Put(local_buffer, 2, MPI_INT, 0, 0, 2, MPI_INT, window);
    
    MPI_Win_fence(0, window); // synchronization
    
    if (rank == 0)
        MPI_Get(get_local_buffer, 2, MPI_INT, 0, 0, 2, MPI_INT, window);
    else if (rank == 1)
        MPI_Get(get_local_buffer, 2, MPI_INT, 1, 0, 2, MPI_INT, window);
    
    MPI_Win_fence(0, window); // synchronization
    
    std::cout<< "Process "<< rank<< ": ";
    std::cout<< "shared_buffer "<< shared_buffer[0]<< " "<< shared_buffer[1]<< " ";
    std::cout<< "local_buffer "<< local_buffer[0]<< " "<< local_buffer[1]<< " ";
    std::cout<< "get_local_buffer "<< get_local_buffer[0]<< " "<< get_local_buffer[1]<< std::endl;
    
    MPI_Win_free(&window);
    
    MPI_Finalize();
    return 0;
}
