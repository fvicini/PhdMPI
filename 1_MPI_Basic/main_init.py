
import mpi4py
mpi4py.rc.initialize = False  # do not initialize MPI automatically
mpi4py.rc.finalize = False    # do not finalize MPI automatically

from mpi4py import MPI # import the 'MPI' module

# manual initialization of the MPI environment
MPI.Init()

print("Hello world!")

# manual finalization of the MPI environment
MPI.Finalize()
