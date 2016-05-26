/*
 *  File: ex9a.cc
 *
 *  Created On: 12, April 2016
 *      Author: Shlomo Gottlieb
 *          ID: 313377145
 *
 * Description: This program holds A sudoku board (size: 9*9),
 *              it allows the user to input values the he choices
 *              and finds the first rational solution.
 *              The program also prints the sudoku whether A solution
 *              was found or not.
 *
 */

//========= Includes =========//
#include <iostream>

//========= Using ==========//
using namespace std;

//========= Constants =========//
const int N = 3;            // The size of 1 square in the 							 // sudoku.
const int EMPTY = 0;        // A sign for an empty cell.
const int STOP_INPUT = -1;  // A sign for stop get input.

//====== Function Declaration ======//
void input_sud(int sud[][N*N]);
bool fill_sud(int sud[][N*N], int row, int col);
void print_sud(const int sud[][N*N]);
bool is_legal(const int sud[][N*N], int row, int col, int val);
bool is_row_ok(const int row[], int col, int val);
bool is_col_ok(const int sud[][N*N], int row, int col, int val);
bool is_sqr_ok(const int sud[][N*N], int row, int col, int val);

//========== Main ===========//
int main()
{
	int sud[N*N][N*N] = { { EMPTY } };  // The sudoku board.

	input_sud(sud);
	fill_sud(sud, 0, 0);
    	print_sud(sud);

	return 0;
}

//======== Input Sudoku ========//
// Gets the input for the sudoku in
// the following format, for example: 2 3 1
// puts the value 1 in the cell which his
// row number is 2 and column is 3, (actually row:3 col:4).
void input_sud(int sud[][N*N])
{
	for(int i = 0; i < N*N; i++)
		for(int j = 0; j < N*N; j++)
			cin >> sud[i][j];
}

//======== Fill Sudoku =========//
// Tries to fill-in the given sudoku board
// according to the sudoku rules.
// Returns whether it was possible to solve it or not.
bool fill_sud(int sud[][N*N], int row, int col)
{
    int next_row = (col == N*N - 1) ? row + 1 : row;
    // Points to the row number of the next cell.
    int next_col = (col + 1) % (N*N);
    // Points to the column number of the next cell.

    // If we get here, it means we succeed to solve the sudoku.
	if(row == N*N)
		return true;

    // Checks if we are allowed to change the value of the current cell.
    // If we're not, then we're moving to the next one.
	if(sud[row][col] != EMPTY)
		return fill_sud(sud, next_row, next_col);

    // We're about to try and find the legal and appropriate value
    // to put in the current cell.
    for(int value = 1; value <= N*N; value++)
    {
        sud[row][col] = value;

        // Checks if 'value' can stay in the current cell,
        // and returns true if it does.
        if(is_legal(sud, row, col, value) && fill_sud(sud, next_row, next_col))
            return true;

        // Trial failed!
        sud[row][col] = EMPTY;
    }

    // None of the values solved the sudoku.
	return false;
}

//======== Print Sudoku ========//
// Prints the sudoku Graphically.
void print_sud(const int sud[][N*N])
{
	for(int i = 0; i < N*N; i++)
	{
		for(int j = 0; j < N*N; j++)
			cout << sud[i][j] << ' ';
		cout << endl;
	}
}

//========== Is Legal ==========//
// Checks and returns whether it's legal
// to put 'val' in A specific cell.
bool is_legal(const int sud[][N*N], int row, int col, int val)
{
	return (is_row_ok(sud[row], col, val) &&
            is_col_ok(sud, row, col, val) &&
            is_sqr_ok(sud, row, col, val));
}

//========= Is Row OK =========//
// Checks and returns whether it's legal
// to put 'val' in A specific row.
bool is_row_ok(const int row[], int col, int val)
{
	for(int i = 0; i < N*N; i++)
		if(i != col && row[i] == val)
			return false;       // Found the same value again!

	return true;
}

//========= Is Column OK =========//
// Checks and returns whether it's legal
// to put 'val' in A specific column.
bool is_col_ok(const int sud[][N*N], int row, int col, int val)
{
	for(int i = 0; i < N*N; i++)
		if(i != row && sud[i][col] == val)
			return false;       // Found the same value again!

	return true;
}

//========= Is Square OK =========//
// Checks and returns whether it's legal
// to put 'val' in A specific square.
bool is_sqr_ok(const int sud[][N*N], int row, int col, int val)
{
	int row_corner = (row / N) * N;
	// Holds the row number of the current square corner cell.
	int col_corner = (col / N) * N;
	// Holds the column number of the current square corner cell.

	// Runs over the rows of the current square.
	for(int i = row_corner; i < (row_corner + N); i++)
        // Runs over the columns of the current square.
		for(int j = col_corner; j < (col_corner + N); j++)
			if((i != row || j != col) && sud[i][j] == val)
				return false;       // Found the same value again!

	return true;
}

