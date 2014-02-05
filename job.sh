#!/bin/bash
# The #PBS directives are the equivalent of passing the same argument on 
# the qsub command line.

#PBS -N buddhabrot

#PBS -l nodes=4:ppn=4
#PBS -l walltime=00:20:00

#PBS -j oe

#PBS -M fred.usu@gmail.com

#PBS -m abe
. /rc/tools/utils/dkinit
use OpenMPI-GCC-4.8

LD_LIBRARY_PATH=/home/A00721896:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH

mpirun -np $PBS_NP /home/A00721896/Buda/Buda
convert Buda/Buda.ppm - define png:bit-depth=16 -define png:color-type=0 -quality 100 Buda/Buda.png