#include <iostream>
#include <chrono>
#include <thread>
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

int main()
{
    
    int board[9][9] = {
        {4, 0, 0,    0, 0, 0,    0, 0, 0},
        {0, 0, 0,    2, 1, 8,    0, 7, 0},
        {7, 0, 0,    0, 9, 0,    0, 0, 2},

        {0, 0, 6,    0, 3, 0,    8, 0, 4},
        {1, 0, 0,    0, 0, 0,    0, 2, 0},
        {0, 0, 5,    0, 0, 7,    0, 0, 0},

        {0, 1, 0,    0, 6, 0,    0, 0, 0},
        {0, 6, 0,    0, 8, 5,    0, 0, 0},
        {0, 0, 9,    0, 0, 0,    0, 0, 1}};

    // We use true and true for color and timeline
    if (solveSudoku(board, true, true))
    {
        printBoard(board);
        cout << endl << "Solved!";
    }
    else
    {
        cout << "Cant solve sudoku" << endl;
    }

    return 0;
}