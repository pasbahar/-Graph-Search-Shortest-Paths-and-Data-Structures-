// Algoritms_w4_hash.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>;
#include<fstream>;
#include<map>;

using namespace std;
const int NUM_ELEMENTS = 1000000;
const int MIN = -10000;
const int MAX = 10000;

int main()
{
	map<signed long long int,bool> numbers;
	typedef map<signed long long int, bool>::const_iterator iter;
	iter start, end;
	signed long long int number;
	long long int probe_sum;
	int count = 0;
	bool found[MAX - MIN + 1];
	for (int i = 0; i <=MAX-MIN; i++)
		found[i] = false;

	ifstream datafile;
	datafile.open("Data.txt",ios::in);
	while (datafile >> number)
		numbers[number];

	start = numbers.begin();
	end = numbers.end();
	end--;

	while (start != end)
	{
		probe_sum = start->first + end->first;
		if (probe_sum < MIN)
		{
			// the value is too small, there is just no hope for success, let go the small side
			start++;
		}
		else if (probe_sum > MAX)
		{
			// the value is too large, there is just no hope for success, let go the small side
			end--;
		}
		else
		{
			if (start->first != end->first)
			{
				found[probe_sum - MIN] = true;
			}
			iter current_start = start;
			iter current_end = end;
			while (start != end)
			{
				// let see if there are any more solution starting with the same end
				start++;
				probe_sum = start->first + end->first;
				if (probe_sum < MIN)
				{
					// This is impossible
					break;
				}
				else if (probe_sum > MAX)
				{
					break;
				}
				else
				{
					if (start->first != end->first)
					{
						found[probe_sum - MIN] = true;
					}
				}
			}
			start = current_start;

			while (start != end)
			{
				// let see if there are any more solution starting with the same start
				end--;
				probe_sum = start->first + end->first;
				if (probe_sum < MIN)
				{
					break;
				}
				else if (probe_sum > MAX)
				{
					// This is impossible
					break;
				}
				else
				{
					if (start->first != end->first)
					{
						found[probe_sum - MIN] = true;
					}
				}
			}
			end = current_end;
			// We have exhausted all solution with start and end, so skip them both
			start++;
			if (start == end) break;
			end--;
		}
	}

	for (int i = MIN; i <= MAX; i++)
	{
		if (found[i - MIN])
		{
			count++;
		}
	}
	
	cout << count << endl;

    return 0;
}

