#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

void printBoard(int board[9][9])
{
    for (int row = 0; row < 9; row++)
    {
        if (row % 3 == 0 && row != 0)
        {
            cout << "---------------------" << endl;
        }

        for (int col = 0; col < 9; col++)
        {
            if (col % 3 == 0 && col != 0)
            {
                cout << "| ";
            }
                
            cout << board[row][col] << " ";
            
        }
        cout << endl;
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
            if (board[row][col] == 0)
            {
                for (int num = 1; num <= 9; num++)
                {
                    if (isValid(board, row, col, num))
                    {
                        board[row][col] = num;
                        
                        if (solveSudoku(board, color, timeline))
                        {
                            return true;
                        }
    
                        board[row][col] = 0;
                        
                    }
                }
                return false;
            }
        }
    }
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

    if (solveSudoku(board))
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