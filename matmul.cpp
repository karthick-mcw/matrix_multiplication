#include <bits/stdc++.h>
#include "matmul.hpp"

using namespace std;

void multiply(int** result ,int** A , int** B , int rowsA ,int colsB , int colsA ,int choice );
void matrix_multiplication(int** A, int rowsA, int colsA, int** B, int rowsB, int colsB, int** result) {
    // Check if valid
    if (colsA != rowsB) {
        cout <<"Test Case inappropriate"<<endl;
        exit(EXIT_FAILURE);
    }

    // Initialize the result matrix
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            result[i][j] = 0;
        }
    }

    // Perform multiplication
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            for (int k = 0; k < colsA; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    cout << "Change the loops based on choices"<<endl<<"1 -> ijk , 2-> ikj , 3-> jik , 4-> jki , 5-> kij , 6-> kji"<<endl;
    int choice;
    cin >> choice; 
    choice = 1; //default ijk loops 
    multiply(result , A , B , rowsA , colsB , colsA , choice);
}

void multiply(int** result ,int** A , int** B , int rowsA ,int colsB , int colsA ,int choice = 1){
    if(choice == 1){
        for (int i = 0; i < rowsA; i++) {
          for (int j = 0; j < colsB; j++) {
             for (int k = 0; k < colsA; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    }
    else if(choice == 2){
        for (int i = 0; i < rowsA; i++) {
          for (int k = 0; k < colsB; k++) {
             for (int j = 0; j < colsA; j++) {
                result[i][k] += A[i][j] * B[j][k];
            }
        }
    }}
    else if(choice == 3){
        for (int j = 0; j < rowsA; j++) {
          for (int i = 0; i < colsB; i++) {
             for (int k = 0; k < colsA; k++) {
                result[j][i] += A[j][k] * B[k][i];
            }
        }
    }
    }
     else if(choice == 4){
        for (int j = 0; j < rowsA; j++) {
          for (int k = 0; k < colsB; k++) {
             for (int i = 0; i < colsA; i++) {
                result[i][k] += A[j][i] * B[i][k];
            }
        }
    }
    }
     else if(choice == 5){
        for (int k = 0; k < rowsA; k++) {
          for (int i = 0; i < colsB; i++) {
             for (int j = 0; j < colsA; j++) {
                result[k][i] += A[k][j] * B[j][i];
            }
        }
    }
    }
     else if(choice == 6){
        for (int k = 0; k < rowsA; k++) {
          for (int j = 0; j < colsB; j++) {
             for (int i = 0; i < colsA; i++) {
                result[k][j] += A[k][i] * B[i][j];
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
