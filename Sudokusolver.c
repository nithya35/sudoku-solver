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
int main() {
    int input_board[9][9];
    int temp[9][9];
      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++){
            temp[i][j] =input_board[i][j];
        }
    }
    take_input(input_board);
    solveSudoku(input_board);
    printBoard(input_board,temp);
    printf(ANSI_COLOR_CYAN"press any key to close..."ANSI_COLOR_RESET);
    getch();
    return 0;
}
