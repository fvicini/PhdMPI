
#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) 
{
    MPI_Init(&argc, &argv);
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int numSpawn = 2;
    MPI_Comm parentcomm, intercomm;
    int errcodes[numSpawn];
    
    MPI_Comm_get_parent(&parentcomm);
    
    if (parentcomm == MPI_COMM_NULL)
    {
        // Create 2 more processes
        MPI_Comm_spawn( "./4_MPI_Advanced", MPI_ARGV_NULL, numSpawn, MPI_INFO_NULL, 
                       0, MPI_COMM_WORLD, &intercomm, errcodes);
        
        std::cout<< "Parent Process "<< rank<< std::endl;
    }
    else
    {
        int subRank;
        MPI_Comm_rank(parentcomm, &subRank);
        std::cout<< "Spawned Process "<< rank<< " subRank "<< subRank<< std::endl;
    }
    
    MPI_Finalize();
    return 0;
}
