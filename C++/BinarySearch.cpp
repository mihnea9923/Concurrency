
#include <iostream>
#include <thread>
//#include "mpi.h"
//#include "Communicators.h"
//#include "Dijktra.h"
#define threadsNumber 4
using namespace std;

void binarySearch(int array[], int left, int right, int value)
{
	if (right >= left) {
		int mid = left + (right - left) / 2;
		if (array[mid] == value)
			cout << mid << endl;
		if (array[mid] > value)
			binarySearch(array, left, mid - 1, value);
		binarySearch(array, mid + 1, right, value);
	}

}

int main()
{
	int length, value;
	cout << "Enter vector length\n";
	cin >> length;
	cout << "Enter the value you are looking for(the vector contains elements 1 2 ..." << length << ")\n";
	cin >> value;
	int* v = new int[length];
	for (int i = 0; i < length; i++)
	{
		v[i] = i + 1;
	}
	thread threads[threadsNumber];
	int start = 0, end = length / threadsNumber - 1;
	for (int i = 0; i < threadsNumber; i++)
	{
		threads[i] = thread(binarySearch, v, start, end , value);
		start = end + 1;
		end += length / threadsNumber;
	}

	for (int i = 0; i < threadsNumber; i++)
	{
		if (threads[i].joinable())
		{
			threads[i].join();
		}
	}
	return 0;
}




