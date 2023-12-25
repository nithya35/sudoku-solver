## Harssha wardan , Sree nithya
## Project - Sudoku generator and solver

# Sudoku

The Sudoku is a  program to create and solve Sudoku puzzles according to below rules.

Rules:
* In a valid Sudoku grid, every number from 1 to 9 must appear:
    * Only once in every row
    * Only once in every column
    * Only once in every 3x3 squared region

# Functionality

Our Sudoku meets the full specs. It is able to create a unique sudoku board in three modes : easy , moderate and hard (1 for easy , 2 for moderate and 3 for hard)

# Files

Many new libraries like  windows.h , dos.h , stdlib are used in this which are very standard C libraries and are very important.
We created a custom library functions.h
For sudoku algorithm , we implemented backtracking.

## recursion/backtracking

The sudoku program uses recursion and backtracking to output both created and solved puzzles. On each coordinate in the grid, the program calls the solve sudoku method, which seeks a solvable solution and recurses until one is found . It backtracks when an non-unique sudoku is created until the puzzle can be solved at a prior square.

## input method

First the coordinates of the square where we want to fill a number should be entered and then the number should be entered.
