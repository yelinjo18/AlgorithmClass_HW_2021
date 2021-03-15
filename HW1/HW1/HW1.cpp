#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int tree[1000 + 1][2];	// tree[(1 <= n_node <= 10000)][l, r]
int goal;

int RecursionGetSize(int now)
{
	if (now == -1)
		return 0;
	else
	{
		int l_size = RecursionGetSize(tree[now][0]);
		int r_size = RecursionGetSize(tree[now][1]);
		if (l_size < r_size)
			goal++;
		return l_size + r_size + 1;
	}
}

int main()
{
	ifstream input;
	input.open("input.txt");

	int n_data;		input >> n_data;
	while (n_data--)
	{
		goal = 0;								//initialize goal.
		fill(&tree[0][0], &tree[1000][2], 0);	//initialize tree.
		int n_node;	input >> n_node;
		for (int i = 1; i <= n_node; i++)
		{
			int a;	input >> a;
			input >> tree[a][0] >> tree[a][1];
		}

		RecursionGetSize(1);
		cout << goal << '\n';
	}
}