/*
Mandar Patil
mpatil2
Fall 24 - CSE 101
MatrixTest.c
Test file for testing function of Matrix.c 
*/
#include "Matrix.h"

int main() {
    Matrix A = newMatrix(3); 
    Matrix B = newMatrix(3); 

    changeEntry(A, 1, 1, 1.0);
    changeEntry(A, 1, 2, 2.0);
    changeEntry(A, 2, 2, 3.0);
    changeEntry(A, 3, 1, 4.0);

    changeEntry(B, 1, 1, 5.0);
    changeEntry(B, 2, 2, 6.0);
    changeEntry(B, 2, 3, 7.0);
    changeEntry(B, 3, 3, 8.0);

    printf("\nMatrix A:\n"); 
    printMatrix(stdout, A); 

    printf("\nMatrix B:\n"); 
    printMatrix(stdout, B); 

    Matrix C = sum(A, B); 
    printf("\nSum of Matrix A and B:\n");
    printMatrix(stdout, C); 

    Matrix D = diff(A, B); 
    printf("\nDifference of Matrix A and B\n"); 
    printMatrix(stdout, D); 

    Matrix E = scalarMult(2.0, A);
    printf("\nMatrix E = 2 * A:\n");
    printMatrix(stdout, E);

    Matrix F = transpose(A);
    printf("\nMatrix F = Transpose of A:\n");
    printMatrix(stdout, F);

    Matrix G = product(A, B);
    printf("\nMatrix G = A * B:\n");
    printMatrix(stdout, G);

    makeZero(A);
    printf("\nMatrix A after makeZero:\n");
    printMatrix(stdout, A);

    if (equals(B, B)) {
        printf("\nMatrix B is equal to itself.\n");
    } else {
        printf("\nMatrix B is not equal to itself. (This should not happen!)\n");
    }

    Matrix copy_B = copy(B); 
    printf("\nCopy of matrix B\n"); 
    printMatrix(stdout, copy_B); 

}