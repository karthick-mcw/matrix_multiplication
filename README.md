# Matrix Multiplication in C

This project demonstrates a tiled matrix multiplication program implemented in C, capable of handling multiple test cases and verifying results. The program supports six different loop order strategies to optimize performance, and results are recorded in a CSV file.

## Files

- **`matmul.cpp`**: Implements the tiled matrix multiplication function.
- **`matmul.hpp`**: Header file containing declarations for the matrix multiplication functions.
- **`driver.cpp`**: Main program that:
  - Reads matrices from files.
  - Calls the matrix multiplication function.
  - Compares the computed results with expected output matrices.
  - Logs results and execution times for various loop orders.
- **`Unit_test/`**: Contains unit test cases organized into subdirectories (e.g., `unit_1`, `unit_2`, ...). Each subdirectory includes:
  - `A.txt`: Matrix A.
  - `B.txt`: Matrix B.
  - `C.txt`: Expected result matrix.
- **`results.csv`**: Output file where results and execution times for each test case are stored.

## Features

1. **Matrix Multiplication with Tiling:**
   - Implements a tiled approach to matrix multiplication.
   - Supports six different loop order strategies: `ijk`, `ikj`, `jik`, `jki`, `kij`, and `kji`.
   - Allows experimentation with the tile size.

2. **Test Case Automation:**
   - Automatically processes multiple test cases located in the `Unit_test/` directory.
   - Validates results against expected matrices.

3. **Error Handling:**
   - Handles file errors, invalid matrix dimensions, and insufficient data gracefully.

4. **Performance Measurement:**
   - Measures and logs execution time for each loop order strategy.
   - Averages results over multiple runs to ensure consistency.

## Steps to Build and Run

Follow these steps to build and run the program:

### Step 1: Navigate to the Project Folder
```bash
cd Matrix_Multiplication
```

### Step 2: Compile the Program
Compile the program using the provided Bash script:
```bash
bash run_tests.sh
```

### Step 3: Execute the Program
Run the compiled program:
```bash
./matrix_multiplication
```

### Step 4: Check Results
- Verify the results in the `results.csv` file.
- Each row corresponds to a test case and contains:
  - Test case name.
  - Status (Passed/Failed).
  - Success indicator.
  - Execution times (in milliseconds) for all six loop order strategies.

## Detailed Explanation

### Input and Output

1. **Input Matrices:**
   - Matrix `A` is read from `A.txt`.
   - Matrix `B` is read from `B.txt`.
   - Expected result matrix `C` is read from `C.txt`.
   
2. **Output:**
   - The program computes the result matrix and compares it with the expected result (`C`).
   - If there is a mismatch, the test case is marked as failed.
   - Results and execution times are logged in `results.csv`.

### Matrix Multiplication with Tiling
The program uses a tiled approach to improve cache utilization. The tiling block size can be modified via the `TILE_SIZE` constant.

### Error Handling
The program handles:
- Missing or unreadable files.
- Invalid matrix dimensions (non-positive values).
- Insufficient or malformed data in input files.
- Dimension mismatches between matrices.

### Performance Measurement
- Each loop order is run 100 times to calculate the average execution time.
- Results are logged in milliseconds.

## Customization

### Tile Size
Modify the `TILE_SIZE` constant in `matmul.cpp` to experiment with different tile sizes.

### Adding Test Cases
Add new test cases by creating subdirectories in the `Unit_test/` folder with appropriately named `A.txt`, `B.txt`, and `C.txt` files.

## Example CSV Output
```
Test Case,Status,Success,ijk Time (ms),ikj Time (ms),jik Time (ms),jki Time (ms),kij Time (ms),kji Time (ms)
Unit_test/unit_1,Passed,Success,5.23,5.01,5.15,5.08,5.02,5.10
Unit_test/unit_2,Failed,Failure,,,,,,
...
```

## Contact
For any questions or issues, please contact the project maintainer.

