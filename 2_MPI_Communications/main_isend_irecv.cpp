
#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) 
{
    MPI_Init(&argc, &argv);
    
    int process_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    
    int tag = 10;
    float a[2] = { 0.0, 0.0 };
    float b[2] = { 0.0, 0.0 };
    MPI_Status status[2];
    MPI_Request request[2];
    
    if (process_rank == 0)
    {
        a[0] = 1.0; a[1] = 2.0;
        MPI_Isend(&a, 2, MPI_FLOAT, 1, tag, MPI_COMM_WORLD, &request[0]);
        MPI_Irecv(&b, 2, MPI_FLOAT, 1, tag + 1, MPI_COMM_WORLD, &request[1]);
    }
    else if (process_rank == 1)
    {
        b[0] = 3.0; b[1] = 4.0;
        MPI_Isend(&b, 2, MPI_FLOAT, 0, tag + 1, MPI_COMM_WORLD, &request[0]);
        MPI_Irecv(&a, 2, MPI_FLOAT, 0, tag, MPI_COMM_WORLD, &request[1]);
    }

    std::cout<< "Process "<< process_rank<< " waiting..."<< std::endl;
    
    MPI_Wait(&request[0], &status[0]);
    MPI_Wait(&request[1], &status[1]);
    
    std::cout<< "Process "<< process_rank<< " ";
    std::cout<< "Status[0] SOURCE: "<< status[0].MPI_SOURCE<< " ";
    std::cout<< "TAG: "<< status[0].MPI_TAG<< std::endl;
    
    std::cout<< "Process "<< process_rank<< " ";
    std::cout<< "Status[1] SOURCE: "<< status[1].MPI_SOURCE<< " ";
    std::cout<< "TAG: "<< status[1].MPI_TAG<< std::endl;
    
    std::cout<< "Process "<< process_rank<< " ";
    std::cout<< "a "<< a[0]<< ", "<< a[1]<< " ";
    std::cout<< "b "<< b[0]<< ", "<< b[1]<< std::endl; 
    
    MPI_Finalize();
    return 0;
}
