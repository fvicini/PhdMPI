
#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) 
{
    MPI_Init(&argc, &argv);
    
    int rank, nprocs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    
    int dim[] = { 0, 0 };
    MPI_Dims_create(nprocs, 2, dim); // create 2D cart dimensions
    
    int period[] = {1, 0}; // periodic in the first dimension
    MPI_Comm grid_comm;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dim, period, 1, &grid_comm);
    
    int new_rank;
    int coordinates[2] = { 0, 0 };
    MPI_Comm_rank(grid_comm, &new_rank); // new rank in the communicator
    MPI_Cart_coords(grid_comm, new_rank, 2, coordinates); // coordinate in the grid
    
    std::cout<< "Process "<< rank<< ": "<< " ";
    std::cout<< "new_rank "<< new_rank<< " ";
    std::cout<< "coordinates "<< coordinates[0]<< ", "<< coordinates[1]<< std::endl;
    
    MPI_Barrier(grid_comm);
    
    int source, dest;
    for (int direction = 0; direction < 2; direction++) 
    {
        for (int displacement = -1; displacement < 2; displacement += 2) 
        {
            int bufferSend = new_rank, bufferRecv = -1;
            
            MPI_Cart_shift(grid_comm, direction, displacement, &source, &dest);
                        
            MPI_Sendrecv(&bufferSend, 1, MPI_INT, source, 10, 
                         &bufferRecv, 1, MPI_INT, dest, 10,
                         grid_comm, MPI_STATUS_IGNORE);
            
            std::cout<< "Process "<< rank<< " - ";
            std::cout<< "direction "<< direction<< " ";
            std::cout<< "displacement "<< displacement<< ": ";
            std::cout<< "send to "<< dest<< " ";
            std::cout<< "data "<< bufferSend<< "; ";
            std::cout<< "recv from "<< source<< " ";
            std::cout<< "data "<< bufferRecv<< std::endl;
        }
    }
           
    MPI_Comm_free(&grid_comm);
    
    MPI_Finalize();
    return 0;
}
