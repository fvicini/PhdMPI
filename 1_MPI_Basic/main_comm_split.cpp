
#include <iostream>
#include <mpi.h>
int main(int argc, char **argv)
{
    int err;
    MPI_Init(&argc, &argv);
    
    int nprocs, my_rank;
    
    // Get the rank and size in the original communicator
    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    unsigned int color = world_rank / 4; // Determine color based on row
    
    // Split the communicator based on the color and use the
    // original rank for ordering
    MPI_Comm row_comm;
    err = MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &row_comm);
    
    int row_rank, row_size;
    MPI_Comm_rank(row_comm, &row_rank);
    MPI_Comm_size(row_comm, &row_size);
    
    std::cout<< "WORLD RANK/SIZE: "<< world_rank<< "/"<< world_size<< "\t";
    std::cout<< "ROW RANK/SIZE: "<< row_rank<< "/"<< row_size<< std::endl;
    
    // Free the communicator
    MPI_Comm_free(&row_comm);
    
    MPI_Finalize();
    
    return 0;
}
