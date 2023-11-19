#include <iostream>
using namespace std;

// Define the size of the Sudoku grid
#define N 9

// Function prototypes
bool findEmptyLocation(int grid[N][N], int& row, int& col);
bool isSafe(int grid[N][N], int row, int col, int num);
bool solveSudoku(int grid[N][N]);
void printSudoku(int grid[N][N]);

int main() {
    int grid[N][N];

    cout << "Enter the Sudoku puzzle (use 0 for empty cells):\n";

    // Input Sudoku puzzle
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> grid[i][j];

    if (solveSudoku(grid)) {
        cout << "Sudoku puzzle solved:\n";
        printSudoku(grid);
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}

bool findEmptyLocation(int grid[N][N], int& row, int& col) {
    for (row = 0; row < N; ++row)
        for (col = 0; col < N; ++col)
            if (grid[row][col] == 0)
                return true;
    return false;
}

bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if 'num' is not already in the row and column
    for (int x = 0; x < N; ++x)
        if (grid[row][x] == num || grid[x][col] == num)
            return false;

    // Check if 'num' is not in the 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

bool solveSudoku(int grid[N][N]) {
    int row, col;

    // If there are no empty locations, the puzzle is solved
    if (!findEmptyLocation(grid, row, col))
        return true;

    // Try filling the empty location with numbers 1 to 9
    for (int num = 1; num <= 9; ++num) {
        if (isSafe(grid, row, col, num)) {
            // If it's safe, assign the number and recursively try to solve the rest
            grid[row][col] = num;

            if (solveSudoku(grid))
                return true;

            // If assigning num doesn't lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }

    // No number could be assigned, backtracking is needed
    return false;
}

void printSudoku(int grid[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << grid[i][j] << " ";
        cout << endl;
    }
}