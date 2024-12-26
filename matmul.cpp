#include <bits/stdc++.h>
#include "matmul.hpp"

using namespace std;

// Function to perform the tiling operation
void tile_multiply_block(int** result, int** A, int** B, int iStart, int iEnd, int jStart, int jEnd, int kStart, int kEnd) {
    for (int i = iStart; i < iEnd; i++) {
        for (int j = jStart; j < jEnd; j++) {
            for (int k = kStart; k < kEnd; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Main matrix multiplication function with tiling
void matrix_multiplication_with_tiling(int** A, int rowsA, int colsA, int** B, int rowsB, int colsB, int** result, int choice) {
    // Check if valid multiplication
    if (colsA != rowsB) {
        cout << "Test Case inappropriate" << endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            result[i][j] = 0;
        }
    }

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
                    tile_multiply_block(result, A, B, i, min(i + TILE_SIZE, rowsA), j, min(j + TILE_SIZE, colsB), k, min(k + TILE_SIZE, colsA));
                }
            }
        }
    } else if (choice == 2) { // ikj
        for (int i = 0; i < rowsA; i += TILE_SIZE) {
            for (int k = 0; k < colsA; k += TILE_SIZE) {
                for (int j = 0; j < colsB; j += TILE_SIZE) {
                    tile_multiply_block(result, A, B, i, min(i + TILE_SIZE, rowsA), j, min(j + TILE_SIZE, colsB), k, min(k + TILE_SIZE, colsA));
                }
            }
        }
    } else if (choice == 3) { // jik
        for (int j = 0; j < colsB; j += TILE_SIZE) {
            for (int i = 0; i < rowsA; i += TILE_SIZE) {
                for (int k = 0; k < colsA; k += TILE_SIZE) {
                    tile_multiply_block(result, A, B, i, min(i + TILE_SIZE, rowsA), j, min(j + TILE_SIZE, colsB), k, min(k + TILE_SIZE, colsA));
                }
            }
        }
    } else if (choice == 4) { // jki
        for (int j = 0; j < colsB; j += TILE_SIZE) {
            for (int k = 0; k < colsA; k += TILE_SIZE) {
                for (int i = 0; i < rowsA; i += TILE_SIZE) {
                    tile_multiply_block(result, A, B, i, min(i + TILE_SIZE, rowsA), j, min(j + TILE_SIZE, colsB), k, min(k + TILE_SIZE, colsA));
                }
            }
        }
    } else if (choice == 5) { // kij
        for (int k = 0; k < colsA; k += TILE_SIZE) {
            for (int i = 0; i < rowsA; i += TILE_SIZE) {
                for (int j = 0; j < colsB; j += TILE_SIZE) {
                    tile_multiply_block(result, A, B, i, min(i + TILE_SIZE, rowsA), j, min(j + TILE_SIZE, colsB), k, min(k + TILE_SIZE, colsA));
                }
            }
        }
    } else if (choice == 6) { // kji
        for (int k = 0; k < colsA; k += TILE_SIZE) {
            for (int j = 0; j < colsB; j += TILE_SIZE) {
                for (int i = 0; i < rowsA; i += TILE_SIZE) {
                    tile_multiply_block(result, A, B, i, min(i + TILE_SIZE, rowsA), j, min(j + TILE_SIZE, colsB), k, min(k + TILE_SIZE, colsA));
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
