#include <iostream>
#include <chrono>
#include <thread>
#include <bits/stdc++.h>
using namespace std;

void printBoard(int board[9][9], int ROW = -1, int COL = -1, bool bt = false, bool timeline = false)
{
    for (int row = 0; row < 9; row++)
    {
        if (row % 3 == 0 && row != 0)
        {
            // Print this line for looks
            cout << "---------------------" << endl;
        }

        for (int col = 0; col < 9; col++)
        {
            if (col % 3 == 0 && col != 0)
            {
                // Line for looks
                cout << "| ";
            }
            // This will be true if we use timeline and colors
            if (ROW != -1 && COL != -1)
            {
                // Color row
                if (row == ROW && col == COL)
                {

                    // Red for bt
                    if (bt)
                    {
                        cout << "\033[31m" << board[row][col] << "\033[0m ";
                    }
                    // Blue for other move
                    else
                    {
                        cout << "\033[34m" << board[row][col] << "\033[0m ";
                    }
                }
                // Not colored
                else
                {
                    cout << board[row][col] << " ";
                }
            }
            else
            {
                // No color
                cout << board[row][col] << " ";
            }
        }
        cout << endl;
    }
    // Gap if we want to see timeline
    if (timeline)
    {
        cout << endl << endl;
        this_thread::sleep_for(chrono::milliseconds(2000));
    }
}

bool isValid(int board[9][9], int row, int col, int num)
{
    // Check row
    for (int i = 0; i < 9; i++)
    {
        if (board[row][i] == num)
        {
            return false;
        }
    }

    // Check col
    for (int i = 0; i < 9; i++)
    {
        if (board[i][col] == num)
        {
            return false;
        }
    }

    // Check grid
    int rowStart = row - row % 3;
    int colStart = col - col % 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i + rowStart][j + colStart] == num)
            {
                return false;
            }
        }
    }

    return true;
}

bool solveSudoku(int board[9][9], bool color = false, bool timeline = false)
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            // Empty cell
            if (board[row][col] == 0)
            {
                // Try every number
                for (int num = 1; num <= 9; num++)
                {
                    if (isValid(board, row, col, num))
                    {
                        // Put it in
                        board[row][col] = num;
                        // Do blue (for possible move)
                        if (timeline)
                        {
                            if (color)
                            {
                                printBoard(board, row, col, false, timeline);
                            }
                            else
                            {
                                printBoard(board);
                            }
                        }
                        
                        // Return true if this lead to the solve
                        if (solveSudoku(board, color, timeline))
                        {
                            return true;
                        }
    
                        // Undo if it doesnt lead to solve
                        board[row][col] = 0;
                        // Do red (for "wrong" move)
                        if (timeline)
                        {
                            if (color)
                            {
                                printBoard(board, row, col, true, timeline);
                            }
                            else
                            {
                                printBoard(board);
                            }
                        }
                    }
                }
                // After we try 1-9, if it didnt return true, there is no solution
                return false;
            }
        }
    }
    // Return true if all cells are filled (corectly)
    return true;
}

bool solveSudokuRandom(int board[9][9])
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            // Empty cell
            if (board[row][col] == 0)
            {
                int numbers[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                
                // Shuffle the numbers
                unsigned seed = random_device{}();
                shuffle(numbers, numbers + 9, default_random_engine(seed));

                // Try every number
                for (int i = 0; i < 9; i++)
                {
                    int num = numbers[i];
                    
                    if (isValid(board, row, col, num))
                    {
                        // Put it in
                        board[row][col] = num;
                        
                        // Return true if this lead to the solve
                        if (solveSudoku(board))
                        {
                            return true;
                        }

                        // Undo if it doesnt lead to solve
                        board[row][col] = 0;
                        
                    }
                }
                // After we try 1-9, if it didnt return true, there is no solution
                return false;
            }
        }
    }
    // Return true if all cells are filled (corectly)
    return true;
}

void generateSudoku(int board[9][9], int difficulty)
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            // Fill the board with 0s
            board[row][col] = 0;
        }
    }   

    // Full solved board
    solveSudokuRandom(board);

    // Remove some numbers to create the puzzle
    int count = 0;
    while (count < difficulty)
    {
        int row = rand() % 9;
        int col = rand() % 9;

        // Remove the number
        if (board[row][col] != 0)
        {
            board[row][col] = 0;
            count++;
        }
    }

    cout << "Generated Sudoku:" << endl;
    printBoard(board);
    cout << endl;
}

int main()
{
    int board[9][9];
    generateSudoku(board, 20);    

    // Can use true and true for color and timeline
    // solveSudoku(board, true, true);
    if (solveSudoku(board))
    {
        cout << endl << "Solved sudoku: " << endl;
        printBoard(board);
    }
    else
    {
        cout << "Cant solve sudoku" << endl;
    }

    return 0;
}