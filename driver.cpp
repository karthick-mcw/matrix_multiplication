#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "matmul.hpp"

using namespace std;

bool checkMatrix(int** res, int** C, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (res[i][j] != C[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Function to read a matrix from a file
int** readMatrix(const string& filename, int& rows, int& cols) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "File doesn't open: " << filename << endl;
        exit(0);
    }

    infile >> rows >> cols; // Read the dimensions

    int** matrix = new int*[rows]; // Dynamically allocate memory for the matrix
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            infile >> matrix[i][j]; // Read matrix elements
        }
    }

    infile.close();
    return matrix;
}

// Function to print a matrix
void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Free dynamically allocated memory
void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    string testCases[] = {"Unit_test/unit_2"};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int t = 0; t < numTestCases; t++) {
        string subdir = testCases[t];
        cout << "Test case of " << subdir << endl;

        string fileA = subdir + "/A.txt";
        string fileB = subdir + "/B.txt";
        string fileC = subdir + "/C.txt";

        int rowsA, colsA, rowsB, colsB, rowsC, colsC;

        // Read matrices A, B, and C
        int** A = readMatrix(fileA, rowsA, colsA);
        int** B = readMatrix(fileB, rowsB, colsB);
        int** C = readMatrix(fileC, rowsC, colsC);
        
        if (colsA != rowsB) {
            cout << "Matrix dimensions do not match for multiplication!" << endl;
            freeMatrix(A, rowsA);
            freeMatrix(B, rowsB);
            freeMatrix(C, rowsC);
            continue;
        }

        // Allocate memory for result matrix
        int** res = new int*[rowsA];
        for (int i = 0; i < rowsA; i++) {
            res[i] = new int[colsB]();
        }

        // Measure time for matrix multiplication
        cout<<endl;
        auto start = chrono::high_resolution_clock::now();
        matrix_multiplication(A, rowsA, colsA, B, rowsB, colsB , res); // Populate `res`
        auto end = chrono::high_resolution_clock::now();
        cout << endl;
        chrono::duration<double, milli> duration = end - start;
        cout << "Time taken for matrix multiplication: " << duration.count() << " ms" << endl;

        cout << "Resultant Matrix:" << endl;
        printMatrix(res, rowsA, colsB);

        cout << "Expected Matrix C:" << endl;
        printMatrix(C, rowsC, colsC);

        if (checkMatrix(res, C, rowsC, colsC)) {
            cout << "~~~ Test case passed ~~~" << endl;
        } else {
            cout << "!!! Test case failed !!!" << endl;
        }

        // Free allocated memory
        freeMatrix(A, rowsA);
        freeMatrix(B, rowsB);
        freeMatrix(C, rowsC);
        freeMatrix(res, rowsA);

        cout << endl;
    }

    return 0;
}
