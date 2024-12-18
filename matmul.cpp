#include <bits/stdc++.h>

using namespace std;

int** matrix_multiplication(int** A, int rowsA, int colsA, int** B, int rowsB, int colsB) {
    // Check if matrix multiplication is valid
    if (colsA != rowsB) {
        cerr << "Error: Number of cols in A should match number of rows in B" << endl;
        return nullptr;
    }

    // Allocate memory for the result matrix
    int** result = (int**)malloc(rowsA * sizeof(int*));
    for (int i = 0; i < rowsA; i++) {
        result[i] = (int*)malloc(colsB * sizeof(int));
    }

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            result[i][j] = 0;
        }
    }

    //multiplication
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            for (int k = 0; k < colsA; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return result;
}

//free dynamically allocated memory
void free_matrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
