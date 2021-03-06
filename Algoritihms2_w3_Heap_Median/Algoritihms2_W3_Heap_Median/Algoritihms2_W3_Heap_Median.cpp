// Algoritihms2_W3_Heap_Median.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <queue>
#include <functional>

const int sz = 10000;

using namespace std;
/*
* Class Declaration
*/

//read from file
void BuildArray(int array[])
{
	ifstream dataFile;
	dataFile.open("Median.txt", ios::in);

	for (int i = 0; i < sz; i++)
		dataFile >> array[i];
}


int main()
{
	priority_queue<int> Low;
	priority_queue<int, vector<int>, greater<int> > High;
	int data[sz], medians[sz], result;
	long long sumOfMedians;
	BuildArray(data);
	Low.push(data[0]);

	medians[0] = Low.top();
	sumOfMedians = medians[0];
	for (int i = 1; i < sz; i++)
	{
		if (data[i] > Low.top())
		{
			High.push(data[i]);
		}
		else
		{
			Low.push(data[i]);
		}
		if (High.size() > Low.size())
		{
			Low.push(High.top());
			High.pop();
		}

		if (Low.size() - High.size() > 1 )
		{
			High.push(Low.top());
			Low.pop();
		}
		medians[i] = Low.top();
		sumOfMedians += medians[i];
	}
	result = sumOfMedians % 10000;
	cout << result << endl;
    return 0;
}

