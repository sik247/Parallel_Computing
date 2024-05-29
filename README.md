# Parallel_Computing
Paralell Computing Projects in C/C++

# Lab 1 

# Gauss-Seidel Solver

This project is a parallel implementation of the Gauss-Seidel method for solving systems of linear equations.

## Files

- `sik247.c`: This is the main file of the project. It contains the implementation of the Gauss-Seidel method and the calculation of relative error.

## Functions

- `readInputFile`: This function reads the input file which contains the system of linear equations to be solved. It reads the number of variables, error tolerance, initial values, coefficients of the variables, and constants.

- `gaussSeidelIteration`: This function performs one iteration of the Gauss-Seidel method. It updates the values of the variables based on the current values, the coefficients, and the constants.

- `calculateRelativeError`: This function calculates the relative error between the old values of the variables and the new values. It uses OpenMP for parallelization.

## Usage

To compile the program, use the following command:

```bash
gcc -fopenmp sik247.c -o sik247

```

# Lab 2 

# Gauss-Seidel Solver

This project is a parallel implementation of the Gauss-Seidel method for solving systems of linear equations.

## Files

- `sik247.c`: This is the main file of the project. It contains the implementation of the Gauss-Seidel method and the calculation of relative error.

## Functions

- `readInputFile`: This function reads the input file which contains the system of linear equations to be solved. It reads the number of variables, error tolerance, initial values, coefficients of the variables, and constants.

- `gaussSeidelIteration`: This function performs one iteration of the Gauss-Seidel method. It updates the values of the variables based on the current values, the coefficients, and the constants.

- `calculateRelativeError`: This function calculates the relative error between the old values of the variables and the new values. It uses OpenMP for parallelization.

## Usage

To compile the program, use the following command:

```bash
gcc -fopenmp sik247.c -o sik247
``` 
