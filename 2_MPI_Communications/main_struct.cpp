
#include <iostream>
#include <mpi.h>

struct Car 
{
    int Model;
    int Color;
};

int main(int argc, char **argv) 
{
    MPI_Init(&argc, &argv);

    const int tag = 13;
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // create a MPI type for struct Car
    const int nitems = 2; // number of struct fields
    int blocklengths[nitems] = { 1, 1 }; // lengths of types for each struct field
    MPI_Datatype types[nitems] = { MPI_INT, MPI_INT }; // MPI types of each struct field
    MPI_Datatype mpi_car_type; // the new MPI dataType
    MPI_Aint offsets[nitems]; // offset computed directly from fields

    offsets[0] = offsetof(Car, Model);
    offsets[1] = offsetof(Car, Color);

    // create the new dataType
    MPI_Type_create_struct(nitems, blocklengths, offsets, types, &mpi_car_type);
    MPI_Type_commit(&mpi_car_type); // commit operation

    Car car = { 0, 0 };
    
    if (rank == 0) 
    {
        car.Model = 4;
        car.Color = 100;

        MPI_Send(&car, 1, mpi_car_type, 1, tag, MPI_COMM_WORLD);

        std::cout<< "Process "<< rank<< ": sent structure car"<< std::endl;
    }
    else if (rank == 1) 
    {
        MPI_Status status;
        MPI_Recv(&car, 1, mpi_car_type, 0, tag, MPI_COMM_WORLD, &status);
        std::cout<< "Process "<< rank<< ": recv structure car"<< std::endl;
    }
    
    std::cout<< "Process "<< rank<< ": car.Model "<< car.Model<< " car.Color "<< car.Color<< std::endl;

    MPI_Type_free(&mpi_car_type); // destroy operation

    MPI_Finalize();
    return 0;
}
