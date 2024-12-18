#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to read a matrix from a file
int** readMatrix(const string& filename, int& rows, int& cols) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "File does't open";
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

// Function to free dynamically allocated memory
void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    string testCases[] = {"Unit_test/unit_1", "Unit_test/unit_2"}; 
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

        // Print matrices for verification
        cout << "Matrix A:" << endl;
        printMatrix(A, rowsA, colsA);

        cout << "Matrix B:" << endl;
        printMatrix(B, rowsB, colsB);

        cout << "Expected Matrix C:" << endl;
        printMatrix(C, rowsC, colsC);

        // Free allocated memory
        freeMatrix(A, rowsA);
        freeMatrix(B, rowsB);
        freeMatrix(C, rowsC);

    }

    return 0;
}
