#include <stdio.h>
#include <stdbool.h>
#define MAX 100
void printSolution(int board[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}
bool isSafe(int board[MAX][MAX], int row, int col, int n) {
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1) {
            return false;
        }
    }
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) {
            return false;
        }
    }
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 1) {
            return false;
        }
    }
    return true;
}
bool solveNQueens(int board[MAX][MAX], int row, int n) {
    if (row >= n) {
        return true;
    }
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            board[row][col] = 1;
            if (solveNQueens(board, row + 1, n)) {
                return true;
            }
            board[row][col] = 0;
        }
    }
    return false;
}
int main() {
    int n;
    printf("Enter the value of N (for N-Queens problem): ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Invalid value for N. It should be greater than 0.\n");
        return -1;
    }
    int board[MAX][MAX] = {0}; 
    if (solveNQueens(board, 0, n)) {
        printf("Solution to the N-Queens problem:\n");
        printSolution(board, n);
    } else {
        printf("No solution exists for N = %d.\n", n);
    }

    return 0;
}
