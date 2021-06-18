#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define UNMATCH 2
#define GAP 3

int M[100 + 1][100 + 1];
int P[100 + 1][100 + 1];

void DP(int m, int n, string x, string y)
{
	//opt
	for (int i = m; i > 0; i--)
		M[i][0] = 3 * i;
	for (int j = n; j > 0; j--)
		M[0][j] = 3 * j;

	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			int penalty = (x[i-1] == y[j-1]) ? 0 : UNMATCH;
			M[i][j] = min(M[i - 1][j - 1] + penalty, M[i - 1][j] + GAP);
			M[i][j] = min(M[i][j], M[i][j - 1] + GAP);

			if (M[i][j] == M[i - 1][j - 1] + penalty)
				P[i][j] = 1;
			else if (M[i][j] == M[i - 1][j] + GAP)
				P[i][j] = 2;
			else if (M[i][j] == M[i][j - 1] + GAP)
				P[i][j] = 3;
		}
	}

	//align & print
	{
		string a_x, a_y;

		int p = max(m, n);
		int i = m, j = n;
		while(p--)
		{
			switch (P[i][j])
			{
			case 1:
				a_x.insert(0, 1, x[i-1]);
				a_y.insert(0, 1, y[j - 1]);
				i--;
				j--;
				break;
			case 2:
				a_x.insert(0, 1, x[i - 1]);
				a_y.insert(0, 1, '-');
				i--;
				break;
			case 3:
				a_x.insert(0, 1, '-');
				a_y.insert(0, 1, y[j - 1]);
				j--;
				break;
			}
		}
		cout << a_x << '\n' << a_y << '\n';
	}

	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= n; j++)
			cout << M[i][j] << '\t';
		cout << '\n';
	}
}

int main()
{
	ifstream input;
	input.open("input.txt");

	int n_data;	input >> n_data;
	while (n_data--)
	{
		int m;	input >> m;
		string x;	input >> x;
		int n;	input >> n;
		string y;	input >> y;

		fill(&M[0][0], &M[100][100 + 1], 0);
		fill(&P[0][0], &P[100][100 + 1], 0);

		DP(m, n, x, y);
	}

}