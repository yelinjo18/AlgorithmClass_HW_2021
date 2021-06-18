#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int sudoku[9][9];
bool check_x[9][10], check_y[9][10], check_box[9][10];

int whichbox(int x, int y)
{
	if (x > -1 && x < 3)
	{
		if (y > -1 && y < 3)
			return 0;
		else if (y > 2 && y < 6)
			return 1;
		else if (y > 5 && y < 9)
			return 2;
	}
	else if (x > 2 && x < 6)
	{
		if (y > -1 && y < 3)
			return 3;
		else if (y > 2 && y < 6)
			return 4;
		else if (y > 5 && y < 9)
			return 5;
	}
	else if (x > 5 && x < 9)
	{
		if (y > -1 && y < 3)
			return 6;
		else if (y > 2 && y < 6)
			return 7;
		else if (y > 5 && y < 9)
			return 8;
	}
}

bool promising(int x, int y, int i)
{
	if (check_x[x][i] == false && check_y[y][i] == false && check_box[whichbox(x, y)][i] == false)
	{
		//cout << "sudoku(" << x << ", " << y << ") = " << i << " is promising!\n";
		return true;
	}
	else
		return false;
}

void print_sudoku()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			cout << sudoku[i][j] << " ";
		cout << "\n";
	}
}

void backtracking(int n)
{
	int m_x = n / 9, m_y = n % 9;

	// 만약 스도쿠가 아직 안채워져있다면
	if (sudoku[m_x][m_y] == 0)
	{
		for (int i = 1; i < 10; i++)
		{
			if (promising(m_x, m_y, i))	// 빈자리에 숫자 1~9까지 넣어가며 promising한지 확인
			{
				check_x[m_x][i] = check_y[m_y][i] = check_box[whichbox(m_x, m_y)][i] = true;
				sudoku[m_x][m_y] = i;

				if (n == 80)
				{
					print_sudoku();
					break;
				}
				else
					backtracking(n + 1);

				check_x[m_x][i] = check_y[m_y][i] = check_box[whichbox(m_x, m_y)][i] = false;
				sudoku[m_x][m_y] = 0;
			}
		}
	}
	else
	{
		backtracking(n + 1);
	}	
}

int main()
{
	ifstream input;
	input.open("input.txt");

	int n_data;	input >> n_data;
	int n = 1;
	while (n_data--)
	{
		//initialize
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 10; j++)
				check_x[i][j] = check_y[i][j] = check_box[i][j] = false;

		// input
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				input >> sudoku[i][j];
				if (sudoku[i][j] != 0)
					check_x[i][sudoku[i][j]] = check_y[j][sudoku[i][j]] = check_box[whichbox(i, j)][sudoku[i][j]] = true;
			}
		}
		
		// solve
		cout << "sudoku " << n << '\n';
		backtracking(0);
		n++;	
	}
}