#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void readInputFile(const char* filename, int* numVariables, double* errorTolerance,
                   double** initialValues, double*** coefficients, double** constants) {
    FILE* file = fopen(filename, "r");
    fscanf(file, "%d", numVariables);
    fscanf(file, "%lf", errorTolerance);

    *initialValues = (double*)malloc(*numVariables * sizeof(double));
    for (int i = 0; i < *numVariables; ++i) {
        fscanf(file, "%lf", &(*initialValues)[i]);
    }

    *coefficients = (double**)malloc(*numVariables * sizeof(double*));
    *constants = (double*)malloc(*numVariables * sizeof(double));
    for (int i = 0; i < *numVariables; ++i) {
        (*coefficients)[i] = (double*)malloc(*numVariables * sizeof(double));
        for (int j = 0; j < *numVariables; ++j) {
            fscanf(file, "%lf", &(*coefficients)[i][j]);
        }
        fscanf(file, "%lf", &(*constants)[i]);
    }

    fclose(file);
}

void gaussSeidelIteration(double** coefficients, double* constants, double* values, int numVariables) {
    for (int i = 0; i < numVariables; ++i) {
        double sum = constants[i];
        for (int j = 0; j < numVariables; ++j) {
            if (i != j) {
                sum -= coefficients[i][j] * values[j];
            }
        }
        values[i] = sum / coefficients[i][i];
    }
}

double calculateRelativeError(double* oldValues, double* newValues, int numVariables) {
    double maxError = 0.0;
    #pragma omp parallel for reduction(max : maxError)
    for (int i = 0; i < numVariables; ++i) {
        double error = fabs(newValues[i] - oldValues[i]) / fabs(newValues[i]);
        if (error > maxError) {
            maxError = error;
        }
    }
    return maxError;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <inputfile> <numThreads>\n", argv[0]);
        return 1;
    }

    char* inputFilename = argv[1];
    int numThreads = atoi(argv[2]);

    int numVariables;
    double errorTolerance;
    double* initialValues;
    double** coefficients;
    double* constants;

    readInputFile(inputFilename, &numVariables, &errorTolerance, &initialValues, &coefficients, &constants);

    omp_set_num_threads(numThreads);

    double* values = (double*)malloc(numVariables * sizeof(double));
    for (int i = 0; i < numVariables; ++i) {
        values[i] = initialValues[i];
    }

    int numIterations = 0;
    double relativeError = 1.0;
    double startTime, endTime, totalTime = 0.0;

    while (relativeError > errorTolerance) {
        double* oldValues = (double*)malloc(numVariables * sizeof(double));
        for (int i = 0; i < numVariables; ++i) {
            oldValues[i] = values[i];
        }

        startTime = omp_get_wtime();
        gaussSeidelIteration(coefficients, constants, values, numVariables);
        endTime = omp_get_wtime();
        totalTime += (endTime - startTime);
        relativeError = calculateRelativeError(oldValues, values, numVariables);
        free(oldValues);
        ++numIterations;
    }

    printf("Number of iterations: %d\n", numIterations);
    printf("Execution time: %f seconds\n", totalTime);

    // char outputFilename[100];
    // sprintf(outputFilename, "%s.sol", inputFilename);
    // FILE* outputFile = fopen(outputFilename, "w");
    // for (int i = 0; i < numVariables; ++i) {
    //     //change made here 
    //     fprintf(outputFile, "%.6lf\n", values[i]);    
    //     }
    // fclose(outputFile);
    char outputFilename[100];
    char* inputNumber = strtok(inputFilename, "."); 
    sprintf(outputFilename, "%s.sol", inputNumber);
    FILE* outputFile = fopen(outputFilename, "w");
    for (int i = 0; i < numVariables; ++i) {
        fprintf(outputFile, "%.6lf\n", values[i]);    
    }
    fclose(outputFile);

    free(initialValues);
    for (int i = 0; i < numVariables; ++i) {
        free(coefficients[i]);
    }
    free(coefficients);
    free(constants);
    free(values);

    return 0;
}
