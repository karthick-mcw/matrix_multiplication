#include <bits/stdc++.h>
#include "matmul.hpp"

using namespace std;

void multiply_with_tiling(int** result, int** A, int** B, int rowsA, int colsB, int colsA, int TILE_SIZE, int choice);

// Main matrix multiplication function with tiling
void matrix_multiplication_with_tiling(int** A, int rowsA, int colsA, int** B, int rowsB, int colsB, int** result , int choice) {
    // Check if valid multiplication
    if (colsA != rowsB) {
        cout << "Test Case inappropriate" << endl;
        exit(EXIT_FAILURE);
    }

    // Initialize the result matrix
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            result[i][j] = 0;
        }
    }

    // Ask user for loop choice
    // Define TILE_SIZE for tiling
    int TILE_SIZE = 32; // You can experiment with this value

    // Perform multiplication with tiling
    multiply_with_tiling(result, A, B, rowsA, colsB, colsA, TILE_SIZE, choice);
}

// Function to perform matrix multiplication with tiling for different loop choices
void multiply_with_tiling(int** result, int** A, int** B, int rowsA, int colsB, int colsA, int TILE_SIZE, int choice) {
    if (choice == 1) { // ijk
        for (int i = 0; i < rowsA; i += TILE_SIZE) {
            for (int j = 0; j < colsB; j += TILE_SIZE) {
                for (int k = 0; k < colsA; k += TILE_SIZE) {
                    for (int iBlock = i; iBlock < min(i + TILE_SIZE, rowsA); iBlock++) {
                        for (int jBlock = j; jBlock < min(j + TILE_SIZE, colsB); jBlock++) {
                            for (int kBlock = k; kBlock < min(k + TILE_SIZE, colsA); kBlock++) {
                                result[iBlock][jBlock] += A[iBlock][kBlock] * B[kBlock][jBlock];
                            }
                        }
                    }
                }
            }
        }
    } else if (choice == 2) { // ikj
        for (int i = 0; i < rowsA; i += TILE_SIZE) {
            for (int k = 0; k < colsA; k += TILE_SIZE) {
                for (int j = 0; j < colsB; j += TILE_SIZE) {
                    // Block-level multiplication
                    for (int iBlock = i; iBlock < min(i + TILE_SIZE, rowsA); iBlock++) {
                        for (int kBlock = k; kBlock < min(k + TILE_SIZE, colsA); kBlock++) {
                            for (int jBlock = j; jBlock < min(j + TILE_SIZE, colsB); jBlock++) {
                                result[iBlock][jBlock] += A[iBlock][kBlock] * B[kBlock][jBlock];
                            }
                        }
                    }
                }
            }
        }
    } else if (choice == 3) { // jik
        for (int j = 0; j < rowsA; j += TILE_SIZE) {
            for (int i = 0; i < colsB; i += TILE_SIZE) {
                for (int k = 0; k < colsA; k += TILE_SIZE) {
                    // Block-level multiplication
                    for (int jBlock = j; jBlock < min(j + TILE_SIZE, rowsA); jBlock++) {
                        for (int iBlock = i; iBlock < min(i + TILE_SIZE, colsB); iBlock++) {
                            for (int kBlock = k; kBlock < min(k + TILE_SIZE, colsA); kBlock++) {
                                result[jBlock][iBlock] += A[jBlock][kBlock] * B[kBlock][iBlock];
                            }
                        }
                    }
                }
            }
        }
    } else if (choice == 4) { // jki
        for (int j = 0; j < rowsA; j += TILE_SIZE) {
            for (int k = 0; k < colsB; k += TILE_SIZE) {
                for (int i = 0; i < colsA; i += TILE_SIZE) {
                    // Block-level multiplication
                    for (int jBlock = j; jBlock < min(j + TILE_SIZE, rowsA); jBlock++) {
                        for (int kBlock = k; kBlock < min(k + TILE_SIZE, colsB); kBlock++) {
                            for (int iBlock = i; iBlock < min(i + TILE_SIZE, colsA); iBlock++) {
                                result[jBlock][kBlock] += A[jBlock][iBlock] * B[iBlock][kBlock];
                            }
                        }
                    }
                }
            }
        }
    } else if (choice == 5) { // kij
        for (int k = 0; k < rowsA; k += TILE_SIZE) {
            for (int i = 0; i < colsB; i += TILE_SIZE) {
                for (int j = 0; j < colsA; j += TILE_SIZE) {
                    // Block-level multiplication
                    for (int kBlock = k; kBlock < min(k + TILE_SIZE, rowsA); kBlock++) {
                        for (int iBlock = i; iBlock < min(i + TILE_SIZE, colsB); iBlock++) {
                            for (int jBlock = j; jBlock < min(j + TILE_SIZE, colsA); jBlock++) {
                                result[kBlock][iBlock] += A[kBlock][jBlock] * B[jBlock][iBlock];
                            }
                        }
                    }
                }
            }
        }
    } else if (choice == 6) { // kji
        for (int k = 0; k < rowsA; k += TILE_SIZE) {
            for (int j = 0; j < colsB; j += TILE_SIZE) {
                for (int i = 0; i < colsA; i += TILE_SIZE) {
                    // Block-level multiplication
                    for (int kBlock = k; kBlock < min(k + TILE_SIZE, rowsA); kBlock++) {
                        for (int jBlock = j; jBlock < min(j + TILE_SIZE, colsB); jBlock++) {
                            for (int iBlock = i; iBlock < min(i + TILE_SIZE, colsA); iBlock++) {
                                result[kBlock][jBlock] += A[kBlock][iBlock] * B[iBlock][jBlock];
                            }
                        }
                    }
                }
            }
        }
    }
}

// Free dynamically allocated memory
void free_matrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
