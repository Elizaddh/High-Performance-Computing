#!/bin/bash
#SBATCH -o hw5.out
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=4
#SBATCH -p himem

####module add openmpi/gcc/64/1.10.1
module add mpich/ge/gcc/64/3.2
mpirun /home/eliza.dhungel/Course/hw5/hw5
