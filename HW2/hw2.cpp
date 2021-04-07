#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;
vector<int> mydata;
double result[12][3];

void MergeSort(int low, int high);
void QuickSort(int low, int high);
void getRandomSortTime(int n, int x, int y);

int main()
{
	srand(static_cast<unsigned int>(time(0)));		
	ifstream input;
	input.open("input.txt");
	//cout << float(time / CLOCKS_PER_SEC);

	// sorted data
	int iter = 3;
	while (iter--)
	{
		// make sorted data
		int n;	input >> n;
		result[0][2 - iter] = n;
		mydata.resize(0);
		for (int i = 0; i < n; i++)
			mydata.push_back(i);

		// Get merge sort time
		clock_t s = clock();
		MergeSort(0, n - 1);
		double time = clock() - s;
		result[1][2 - iter] = double(time / CLOCKS_PER_SEC);

		// Get quick sort time
		s = clock();
		QuickSort(0, n - 1);
		time = clock() - s;
		result[2][2 - iter] = double(time / CLOCKS_PER_SEC);
	}

	// random data
	iter = 3;
	while (iter--)
	{
		// make random data
		int n;	input >> n;
		result[3][2 - iter] = n;
		getRandomSortTime(n, 4, 2 - iter);
		getRandomSortTime(n, 5, 2 - iter);
		getRandomSortTime(n, 6, 2 - iter);

		// get average
		result[7][2 - iter] = double(result[7][2 - iter] / 3);
		result[11][2 - iter] = double(result[11][2 - iter] / 3);
	}

	// print result
	{
		//sorted
		cout << "sorted    \t";
		for (int i = 0; i < 3; i++)
			cout << "N=" << result[0][i] << '\t';
		cout << '\n';
		cout << "Merge Sort\t";
		for (int i = 0; i < 3; i++)
			cout << result[1][i] << '\t';
		cout << '\n';
		cout << "Quick Sort\t";
		for (int i = 0; i < 3; i++)
			cout << result[2][i] << '\t';
		cout << "\n\n";

		//random
		cout << "random    \t" << "      \t";
		for (int i = 0; i < 3; i++)
			cout << "N=" << result[3][i] << "\t";
		cout << '\n';

		cout << "Merge Sort\tdata 1\t";
		for (int i = 0; i < 3; i++)
			cout << result[4][i] << '\t';
		cout << '\n';
		cout << "          \tdata 2\t";
		for (int i = 0; i < 3; i++)
			cout << result[5][i] << '\t';
		cout << '\n';
		cout << "          \tdata 3\t";
		for (int i = 0; i < 3; i++)
			cout << result[6][i] << '\t';
		cout << '\n';
		cout << "          \taverage\t";
		cout << fixed;
		cout.precision(3);
		for (int i = 0; i < 3; i++)
			cout << result[7][i] << '\t';
		cout << '\n';

		cout.unsetf(ios::fixed);
		cout << "Quick Sort\tdata 1\t";
		for (int i = 0; i < 3; i++)
			cout << result[8][i] << '\t';
		cout << '\n';
		cout << "          \tdata 2\t";
		for (int i = 0; i < 3; i++)
			cout << result[9][i] << '\t';
		cout << '\n';
		cout << "          \tdata 3\t";
		for (int i = 0; i < 3; i++)
			cout << result[10][i] << '\t';
		cout << '\n';
		cout << "          \taverage\t";
		cout << fixed;
		cout.precision(3);
		for (int i = 0; i < 3; i++)
			cout << result[11][i] << '\t';
		cout << '\n';
	}
}

void getRandomSortTime(int n, int x, int y)
{
	mydata.resize(0);
	for (int i = 0; i < n; i++)
		mydata.push_back(int(rand() % n));

	vector<int> save(mydata);

	// Get merge sort time
	clock_t s = clock();
	MergeSort(0, n - 1);
	double time = clock() - s;
	result[x][y] = double(time / CLOCKS_PER_SEC);
	result[7][y] += result[x][y];

	mydata.resize(save.size());

	copy(save.begin(), save.end(), mydata.begin());

	// Get quick sort time
	s = clock();
	QuickSort(0, n - 1);
	time = clock() - s;
	result[x + 4][y] = double(time / CLOCKS_PER_SEC);
	result[11][y] += result[x + 4][y];
}

void MergeSort(int low, int high)
{
	int mid;
	if (low < high) {
		mid = int((low + high) / 2);

		// recursion
		MergeSort(low, mid);
		MergeSort(mid + 1, high);

		// merge
		int i = low;
		int j = mid + 1;
		int k = low;
		vector<int> U(mydata.size());

		while (i <= mid && j <= high)
		{
			if (mydata[i] < mydata[j])
			{
				U[k] = mydata[i];
				i++;
			}
			else
			{
				U[k] = mydata[j];
				j++;
			}
			k++;
		}

		if (i > mid)
		{
			while (j <= high)
			{
				U[k] = mydata[j];
				k++;	j++;
			}
		}
		else {
			while (i <= mid)
			{
				U[k] = mydata[i];
				k++;	i++;
			}
		}

		for (int p = low; p <= high; p++)
			mydata[p] = U[p];
	}
}

void QuickSort(int low, int high)
{
	int pivotpoint;
	if (low < high)
	{
		// partition
		int pivotitem = mydata[low];
		int j = low;
		for (int i = low + 1; i <= high; i++)
		{
			if (mydata[i] < pivotitem)
			{
				j++;
				// exchange list[i] <-> list[j]
				int tmp = mydata[i];
				mydata[i] = mydata[j];
				mydata[j] = tmp;
			}
			pivotpoint = j;
			//exchange list[low]<->list[pivotpoint]
			int tmp = mydata[low];
			mydata[low] = mydata[pivotpoint];
			mydata[pivotpoint] = tmp;
		}

		// recursion
		QuickSort(low, pivotpoint - 1);
		QuickSort(pivotpoint + 1, high);
	}
}