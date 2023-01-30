
#include <iostream>
#include <omp.h>
#include <mpi.h>

int main(int argc, char **argv) 
{    
    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);
    
    if (provided != MPI_THREAD_FUNNELED)
        std::cerr<< "Warning MPI did not provide MPI_THREAD_FUNNELED"<< std::endl;
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if (rank == 0)
        omp_set_num_threads(3); // set number of threads on each process
    else if (rank == 1)
        omp_set_num_threads(2); // set number of threads on each process
    
    std::cout<< "Process "<< rank<< " numThreads "<<omp_get_num_threads()<< std::endl;
    #pragma omp parallel default(none), shared(rank), shared(ompi_mpi_comm_world, std::cout)
    {
        int flag;
        MPI_Is_thread_main(&flag);
    
        #pragma omp critical
        std::cout<< "Process "<< rank<< " "
        << "numThreads "<<omp_get_num_threads()<< " "
        << "thread "<< omp_get_thread_num()<< " "
        << "isMainThread "<< flag<< std::endl;
        
        #pragma omp master
        {
            // do some MPI operation with master thread
        }

    }
    
    MPI_Finalize();
    return 0;
}
