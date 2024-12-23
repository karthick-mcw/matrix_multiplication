#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cstdlib>
#include <stdexcept> 
#include "matmul.hpp"

using namespace std;

void freeMatrix(int** matrix, int rows);
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

int** readMatrix(const string& filename, int& rows, int& cols) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Unable to open file: " << filename << endl;
        throw runtime_error("Unable to open file");
    }

    if (!(infile >> rows >> cols) || rows <= 0 || cols <= 0) {
        cerr << "Error: Invalid matrix dimensions in file: " << filename << endl;
        throw runtime_error("Invalid matrix dimensions");
    }

    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!(infile >> matrix[i][j])) {
                cerr << "Error: Insufficient or invalid data in file: " << filename << endl;
                freeMatrix(matrix, rows);
                throw runtime_error("Invalid matrix data");
            }
        }
    }

    infile.close();
    
    return matrix;
}

void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
int main() {
    string testCases[] = {
        "Unit_test/unit_1",
        "Unit_test/unit_8",
        "Unit_test/unit_9",
        "Unit_test/unit_10"
    };
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    ofstream resultsFile("results.csv");
    if (!resultsFile.is_open()) {
        cerr << "Error: Unable to open results.csv for writing." << endl;
        return EXIT_FAILURE;
    }

    // Write CSV header
    resultsFile << "Test Case,Status,Success,ijk Time (ms),ikj Time (ms),jik Time (ms),jki Time (ms),kij Time (ms),kji Time (ms)\n";

    for (int t = 0; t < numTestCases; t++) {
        string subdir = testCases[t];
        cout << "Test case of " << subdir << endl;

        string fileA = subdir + "/A.txt";
        string fileB = subdir + "/B.txt";
        string fileC = subdir + "/C.txt";

        int rowsA, colsA, rowsB, colsB, rowsC, colsC;

        int** A = nullptr;
        int** B = nullptr;
        int** C = nullptr;
        string status = "Passed";
        string success = "Success";

        try {
            A = readMatrix(fileA, rowsA, colsA);
            B = readMatrix(fileB, rowsB, colsB);
            C = readMatrix(fileC, rowsC, colsC);
        } catch (const runtime_error& e) {
            // Catch specific error types and write them to the result file
            if (string(e.what()) == "Unable to open file") {
                resultsFile << subdir << ",Error: Unable to open file," << success << ",,,,,,\n";
            } else if (string(e.what()) == "Invalid matrix dimensions") {
                resultsFile << subdir << ",Error: Invalid matrix dimensions," << success << ",,,,,,\n";
            } else if (string(e.what()) == "Invalid matrix data") {
                resultsFile << subdir << ",Error: Invalid matrix data," << success << ",,,,,,\n";
            } else {
                resultsFile << subdir << ",Error: Unknown error," << success << ",,,,,,\n";
            }
            continue;
        }

        if (colsA != rowsB) {
            resultsFile << subdir << ",Error: Dimension mismatch," << success << ",,,,,,\n";
            freeMatrix(A, rowsA);
            freeMatrix(B, rowsB);
            freeMatrix(C, rowsC);
            continue;
        }

        int** res = new int*[rowsA];
        for (int i = 0; i < rowsA; i++) {
            res[i] = new int[colsB]();
        }

        double durations[6] = {0};

        for (int choice = 1; choice <= 6; choice++) {
            double totalDuration = 0.0;
            int numRuns = 100;

            for (int run = 0; run < numRuns; run++) {
                auto start = chrono::high_resolution_clock::now();
                matrix_multiplication_with_tiling(A, rowsA, colsA, B, rowsB, colsB, res, choice);
                auto end = chrono::high_resolution_clock::now();

                chrono::duration<double, milli> duration = end - start;
                totalDuration += duration.count();
            }

            durations[choice - 1] = totalDuration / numRuns;

            if (!checkMatrix(res, C, rowsC, colsC)) {
                status = "Failed";
                success = "Failure";
            }
        }

        resultsFile << subdir << "," << status << "," << success;
        for (double duration : durations) {
            resultsFile << "," << duration;
        }
        resultsFile << "\n";

        freeMatrix(A, rowsA);
        freeMatrix(B, rowsB);
        freeMatrix(C, rowsC);
        freeMatrix(res, rowsA);

        cout << endl;
    }

    resultsFile.close();
    return 0;
}
