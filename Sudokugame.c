#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"
#include <conio.h>
#include <windows.h>
#include <dos.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF){
    }
}
int main() {
    int Board[9][9] = {0};
    int temp[9][9];
    int d;
    int *difficulty = &d;
    system("cls");
    Menu(difficulty);
    Makegame(Board, d);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++){
            temp[i][j] = Board[i][j];
        }
    }
    int row, col, num;
    while (!Full(Board)) {
        system("cls");
        printBoard(Board, temp);
        printf("Enter the row (1-9):");
        if (scanf("%d", &row) != 1 || row < 1 || row > 9) {
            printf("Invalid input for row. Try again.\n");
            Sleep(2000);
            clearInputBuffer();
            continue;
        }
        printf("Enter the column (1-9):");
        if (scanf("%d", &col) != 1 || col < 1 || col > 9) {
            printf("Invalid input for column. Try again.\n");
            Sleep(2000);
            clearInputBuffer();
            continue;
        }
        printf("Enter the number (1-9):");
        if (scanf("%d", &num) != 1 || num < 1 || num > 9) {
            printf("Invalid input for number. Try again.\n");
            Sleep(2000);
            clearInputBuffer();
            continue;
        }
        row--;
        col--;
        if (temp[row][col] == 0 && Valid(Board, row, col, num)) {
            Board[row][col] = num;
            if (Full(Board)) {
                printf("Congratulations! You solved the Sudoku.\n");
                printBoard(Board, temp);
                Sleep(10000);
            }
        } else {
            printf("Invalid move. Try again.\n");
            Sleep(2000);
        }
    }
    return 0;
}
