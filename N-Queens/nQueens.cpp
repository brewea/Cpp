/*
 * Name: Carter Brewer
 * Date Submitted: 15 Apr
 * Lab Section:
 * Assignment Name: Using Recursion to Solve the N-Queens Problem
 */

#include <iostream>
#include <vector>

using namespace std;

// Checks colums vertically, and diagonally
bool checkCol(vector<vector<int>> &chessBoard, int r, int col, int n)
{
    for (int i = 0; i < col; i++)
	{
		if (chessBoard[r][i]){	return false;}
	}
	for (int i = r, j = col ; i >= 0 && j>=0; i--, j--)
	{
		if (chessBoard[i][j]){return false;}
	}
	for (int i = r, j = col; j>=0 && i < n; i++, j--)
	{
		if (chessBoard[i][j]){return false;}
	}
	return true;
}

void placeQueen(vector<vector<int>> &chessBoard, int c, int n, int *count)
{
	// Counts individual succeesful runs
	if (c >= n){*count+=1;}
	
	// checks each row calling place queen recursively to check whole board
	// Places quee if not being attacked
	for (int r = 0; r < n; r++)
	{
		if (checkCol(chessBoard, r, c, n) == true)
		{
			chessBoard[r][c] = 1;
			placeQueen(chessBoard, c + 1, n, count);
			chessBoard[r][c] = 0;
		}
		
	}
	

}
//Uses recursion to count how many solutions there are for
//placing n queens on an nxn chess board
int nQueens(int n)
{
    //Implement int nQueens(int n)
    //Feel free to implement any recursive helper functions
	// Create the board
	vector<vector<int>> chessBoard(n, vector<int>(n,0));
	int count = 0;
	int permutations = 0;
	int col = 0;
	for (int i = 0; i < n/2; i++)
	{
		chessBoard[i][0] = 1;
		
		placeQueen(chessBoard, col+1, n, &count);
		permutations += count*2;
		chessBoard[i][0] = 0;
		count = 0;
	}
	if (n%2 ==1)
	{
		chessBoard[n/2][0] = 1;
		placeQueen(chessBoard, col+1, n, &count);
		permutations += count;
	}
	

	return permutations;
}

int main()
{
    cout << "1: " << nQueens(1) << endl;
    cout << "2: " << nQueens(2) << endl;
    cout << "3: " << nQueens(3) << endl;
    cout << "4: " << nQueens(4) << endl;
    cout << "5: " << nQueens(5) << endl;
    cout << "6: " << nQueens(6) << endl;
    cout << "7: " << nQueens(7) << endl;
    cout << "8: " << nQueens(8) << endl;
    cout << "9: " << nQueens(9) << endl;
    cout << "10: " << nQueens(10) << endl;
    cout << "11: " << nQueens(11) << endl;
    cout << "12: " << nQueens(12) << endl;
    return 0;
}