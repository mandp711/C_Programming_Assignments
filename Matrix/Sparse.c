/*
Mandar Patil
mpatil2
Fall 24 - CSE 101
Sparse.c
Main Program that prints all the operations of Matrix ADT
*/
#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main(int argc, char *argv[]) {
    // Check for correct command-line arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open files for reading and writing
    FILE *inFile = fopen(argv[1], "r");
    FILE *outFile = fopen(argv[2], "w");
    if (inFile == NULL) {
        fprintf(stderr, "Error: Cannot open file %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if (outFile == NULL) {
        fprintf(stderr, "Error: Cannot open file %s for writing\n", argv[2]);
        fclose(inFile);
        exit(EXIT_FAILURE);
    }

    // Read matrix dimensions and initialize matrices
    int n, aNNZ, bNNZ;
    fscanf(inFile, "%d %d %d", &n, &aNNZ, &bNNZ);
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    // Read non-zero entries for Matrix A
    for (int i = 0; i < aNNZ; i++) {
        int row, col;
        double value;
        fscanf(inFile, "%d %d %lf", &row, &col, &value);
        changeEntry(A, row, col, value);
    }

    // Read non-zero entries for Matrix B
    for (int i = 0; i < bNNZ; i++) {
        int row, col;
        double value;
        fscanf(inFile, "%d %d %lf", &row, &col, &value);
        changeEntry(B, row, col, value);
    }

    // Print matrices A and B to output file
    fprintf(outFile, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(outFile, A);
    fprintf(outFile, "\nB has %d non-zero entries:\n", NNZ(B));
    printMatrix(outFile, B);

    // Perform operations and print results

    // 1. Scalar multiplication of A by 1.5
    Matrix scalarA = scalarMult(1.5, A);
    fprintf(outFile, "\n(1.5)*A =\n");
    printMatrix(outFile, scalarA);
    freeMatrix(&scalarA);

    // 2. Sum of A and B
    Matrix sumAB = sum(A, B);
    fprintf(outFile, "\nA+B =\n");
    printMatrix(outFile, sumAB);
    freeMatrix(&sumAB);

    Matrix sumAA = sum(A, A); 
    fprintf(outFile, "\nA+A =\n");
    printMatrix(outFile, sumAA); 
    freeMatrix(&sumAA); 

    // 3. Difference of A and B
    Matrix diffAB = diff(B, A);
    fprintf(outFile, "\nB-A =\n");
    printMatrix(outFile, diffAB);
    freeMatrix(&diffAB);

    Matrix diffAA = diff(A, A);
    fprintf(outFile, "\nA-A =\n");
    printMatrix(outFile, diffAA);
    freeMatrix(&diffAA);

    // 4. Transpose of A
    Matrix transA = transpose(A);
    fprintf(outFile, "\nTranspose(A) =\n");
    printMatrix(outFile, transA);
    freeMatrix(&transA);

    // 5. Product of A and B
    Matrix prodAB = product(A, B);
    fprintf(outFile, "\nA*B =\n");
    printMatrix(outFile, prodAB);
    freeMatrix(&prodAB);

    // 6. Product of B and B
    Matrix prodBB = product(B, B);
    fprintf(outFile, "\nB*B =\n");
    printMatrix(outFile, prodBB);
    freeMatrix(&prodBB);

    // Free matrices and close files
    freeMatrix(&A);
    freeMatrix(&B);
    fclose(inFile);
    fclose(outFile);

    return 0;
}
