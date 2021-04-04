#include <iostream>
#include <vector>
#define SIZE 100
using namespace std;

int list[SIZE];

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
		int U[SIZE] = { 0 };

		while (i <= mid && j <= high)
		{
			if (list[i] < list[j])
			{
				U[k] = list[i];
				i++;
			}
			else
			{
				U[k] = list[j];
				j++;
			}
			k++;
		}

		if (i > mid)
		{
			while (j <= high)
			{
				U[k] = list[j];
				k++;	j++;
			}
		}
		else {
			while (i <= mid)
			{
				U[k] = list[i];
				k++;	i++;
			}
		}

		for (int p = low; p <= high; p++)
			list[p] = U[p];
	}
}

void QuickSort(int low, int high)
{
	int pivotpoint;
	if (low < high)
	{
		// partition
		int pivotitem = list[low];
		int j = low;
		for (int i = low + 1; i <= high; i++)
		{
			if (list[i] < pivotitem)
			{
				j++;
				// exchange list[i] <-> list[j]
				int tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
			}
			pivotpoint = j;
			//exchange list[low]<->list[pivotpoint]
			int tmp = list[low];
			list[low] = list[pivotpoint];
			list[pivotpoint] = tmp;
		}

		// recursion
		QuickSort(low, pivotpoint - 1);
		QuickSort(pivotpoint + 1, high);
	}
}

int main()
{

}