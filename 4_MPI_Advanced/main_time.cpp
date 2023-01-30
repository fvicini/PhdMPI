
#include <iostream>
#include <unistd.h> // library for usleep
#include <mpi.h>

int main(int argc, char **argv) 
{    
    MPI_Init(&argc, &argv);
        
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    MPI_Barrier(MPI_COMM_WORLD);
    double startTime = MPI_Wtime(); // start time
    
    int seconds = 1 + rank; 
    usleep(seconds * 1000 * 1000); // takes microseconds
    
    double endTime = MPI_Wtime(); // end time
    double elapsedTime = endTime - startTime;
    
    double maxElapsedTime = 0.0;
    MPI_Allreduce(&elapsedTime, &maxElapsedTime, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
    
    std::cout.precision(4);
    std::cout<< std::scientific<< "Process "<< rank<< " ";
    std::cout<< "LocalTime "<< elapsedTime<< " secs"<< " ";
    std::cout<< "MaxTime "<< maxElapsedTime<< " secs"<< std::endl;
    
    MPI_Finalize();
    return 0;
}
