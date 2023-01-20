#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) {
  // Initialize MPI
  // This must always be called before any other MPI functions
  MPI_Init(&argc, &argv);

  // Get the number of processes in MPI_COMM_WORLD
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Get the rank of this process in MPI_COMM_WORLD
  int my_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  // Print out information about MPI_COMM_WORLD
  std::cout << "World Size: " << world_size << "   Rank: " << my_rank << std::endl;

  // Finalize MPI
  // This must always be called after all other MPI functions
  MPI_Finalize();

  return 0;
}
