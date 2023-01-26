
#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) 
{
    MPI_Init(&argc,&argv);
    
    int rank, procs, tag = 10;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    MPI_Request rqst;
    MPI_Status status;

    int buffer[2];
    
    if (rank == 0)
    {
        buffer[0] = 2; 
        buffer[1] = 3; 
    }
    
    //Step 1) Initialize persistent send/recv requests
    if (rank == 1)
        MPI_Recv_init(buffer, 2, MPI_INT, 0, tag, MPI_COMM_WORLD, &rqst);
    if (rank == 0)
        MPI_Send_init(buffer, 2, MPI_INT, 1, tag, MPI_COMM_WORLD, &rqst);

    for (unsigned int i = 0; i < 2; i++)
    {
        //Step 2) Use start in place of send/recv
        if (rank == 1)
            MPI_Start(&rqst);

        if (rank == 0)
            buffer[0] += i;
        //... do work

        if (rank == 0)
            MPI_Start(&rqst);

        //Wait for send/recv to complete
        MPI_Wait(&rqst, &status);
        
        std::cout<< "Iteration "<< i<< " ";
        std::cout<< "Rank "<< rank<< " ";
        std::cout<< "Buffer "<< buffer[0]<< ", "<< buffer[1]<< std::endl;
    }

    //Step 3) Clean up the requests
    MPI_Request_free(&rqst);
    
    MPI_Finalize();
    return 0;
}
