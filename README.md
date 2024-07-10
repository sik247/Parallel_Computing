# Parallel_Computing
Paralell Computing Projects in C/C++

# Lab 1 

# Prime Number Finder using MPI

This project is a parallel implementation of a prime number finder using the Message Passing Interface (MPI). It divides the task of finding prime numbers in a given range among multiple processes, each of which checks a subset of the range.

## How it Works

The program takes an integer `N` as a command-line argument and finds all prime numbers up to `N`. It uses the MPI library to distribute the task among multiple processes. Each process checks a subset of the range for prime numbers.

The range for each process is calculated based on the rank of the process and the total number of processes. The range is then divided into smaller ranges, each of which is assigned to a different process.

Each process initializes an array of boolean values representing the numbers in its range, with `true` indicating that a number is prime. It then iterates over the numbers in its range, marking the multiples of each number as not prime.

After all processes have finished checking their ranges, they send their results to the process with rank 0. This process gathers all the results, counts the total number of primes, and writes them to a file.

## Usage

1. Compile the program with an MPI compiler, e.g., `mpicc -o prime_finder prime_finder.c`.
2. Run the program with `mpirun -np <number_of_processes> ./prime_finder <N>`, where `<number_of_processes>` is the number of processes to use and `<N>` is the upper limit for the prime search.

## Requirements

- An MPI library, such as OpenMPI or MPICH.
- A C compiler that supports the MPI library, such as `mpicc`.

## Note

This program uses the MPI_Wtime function to measure the elapsed time for the prime finding task. This function returns the time in seconds since an arbitrary time in the past. The actual time it returns is not important; what matters is the difference between the times at the start and end of the task, which gives the elapsed time.


```

# Lab 2 

# Gauss-Seidel Solver

# Gauss-Seidel Solver using OpenMP

This project is a parallel implementation of the Gauss-Seidel method for solving systems of linear equations using OpenMP. The program reads a system of linear equations from an input file, solves it using the Gauss-Seidel method, and writes the solution to an output file.

## How it Works

The program reads the system of linear equations from an input file. The file should contain the number of variables, the error tolerance, the initial values for the variables, the coefficients of the equations, and the constants on the right-hand side of the equations.

The program then performs iterations of the Gauss-Seidel method until the relative error between the old and new values of the variables is less than the error tolerance. The relative error is calculated as the maximum relative error among all variables.

The Gauss-Seidel method is an iterative method for solving systems of linear equations. In each iteration, each variable is updated based on the current values of the other variables.

The program uses OpenMP to parallelize the calculation of the relative error. The `reduction(max : maxError)` clause is used to find the maximum relative error in parallel.

## Usage

1. Compile the program with an OpenMP-enabled compiler, e.g., `gcc -fopenmp -o gauss_seidel gauss_seidel.c`.
2. Run the program with `./gauss_seidel <inputfile> <numThreads>`, where `<inputfile>` is the name of the input file and `<numThreads>` is the number of threads to use.

## Requirements

- An OpenMP-enabled C compiler, such as GCC with the `-fopenmp` option.
- An input file in the correct format.

## Note

This program uses the `omp_get_wtime` function to measure the execution time of the Gauss-Seidel iterations. This function returns the time in seconds since some arbitrary point in the past. The actual time it returns is not important; what matters is the difference between the times at the start and end of the task, which gives the execution time.
