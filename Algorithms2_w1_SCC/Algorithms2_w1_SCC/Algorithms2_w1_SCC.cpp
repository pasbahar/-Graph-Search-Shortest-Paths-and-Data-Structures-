// Algorithms2_w1_SCC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>

namespace std {};
using namespace std;

void build_graphs_from_stream(istream& is, map<size_t,vector<size_t> >& graph, map<size_t, vector<size_t> >& reverse_graph)
{
	size_t i = 0, j = 0;

	//is >> i;
	//graph.resize(i);
	//reverse_graph.resize(i);

	while (is >> i >> j)
	{
	//	--i; --j;
		if (i != j)
		{
			graph[i].push_back(j);
			reverse_graph[j].push_back(i);
		}
	}

	return;
}

void calculate_leaders_using_DFS( map<size_t, vector<size_t> >& graph, map<size_t, bool>& explored, size_t i, map<size_t, vector<size_t> >& leader, size_t s)
{
	explored[i] = true;

	leader[s].push_back(i);

	for (size_t j = 0; j < graph[i].size(); ++j)
	{
		if (!explored[graph[i][j]])
		{
			calculate_leaders_using_DFS(graph, explored, graph[i][j], leader, s);
		}
	}

	return;
}

void calculate_leaders_using_DFS_loop(map<size_t,size_t>& finish_time, map<size_t, vector<size_t> >& graph, map<size_t, vector<size_t> >& leader)
{
	size_t s = 0;
	map<size_t, bool> explored;

	for (map<size_t,size_t>::reverse_iterator it=finish_time.rbegin();it!=finish_time.rend();++it)
	{

		if (!explored[it->second])
		{
			s = it->second;
			calculate_leaders_using_DFS(graph, explored, it->second, leader, s);
		}
	}

	return;
}

void calculate_finish_times_using_DFS( map<size_t, vector<size_t> >& graph, map<size_t,bool>& explored, size_t i, map<size_t,size_t>& finish_time, size_t& t)
{
	explored[i] = true;

	for (size_t j = 0; j < graph[i].size(); ++j)
	{
		if (explored[graph[i][j]] == false)
		{
			calculate_finish_times_using_DFS(graph, explored, graph[i][j], finish_time, t);
		}
	}

	finish_time[t] = i;
	++t;

	return;
}

void calculate_finish_times_using_DFS_loop( map<size_t, vector<size_t> >& graph, map<size_t,size_t>& finish_time)
{
	size_t t = 1;
	map<size_t,bool> explored;

	for (map<size_t, vector<size_t> >::const_iterator it = graph.begin(); it != graph.end(); ++it)
	{
		if (!explored[it->first])
		{
			calculate_finish_times_using_DFS(graph, explored, it->first, finish_time, t);
		}
	}

//	assert(t == graph.size());

	return;
}

map<size_t, vector<size_t> > count_strongly_connected_components(map<size_t, size_t>& scc, map<size_t, vector<size_t> >& graph, map<size_t, vector<size_t> >& reverse_graph)
{
	map<size_t, size_t> finish_time;
	calculate_finish_times_using_DFS_loop(reverse_graph, finish_time);

	map<size_t, vector<size_t> > leader;
	calculate_leaders_using_DFS_loop(finish_time, graph, leader);

	return leader;
}

int main()
{
	map<size_t, vector<size_t> > graph, reverse_graph, leader;
	map<size_t,size_t>scc;
	vector<size_t> number_of_comp;
		
		ifstream ifs;
		ifs.open("SCC.txt");

		build_graphs_from_stream(ifs, graph, reverse_graph);

		ifs.close();


	leader= count_strongly_connected_components(scc, graph, reverse_graph);

	cout << "Number of Strongly Connected Components: " << leader.size() << endl;

	for (map<size_t, vector<size_t> >::const_iterator it = leader.begin(); it != leader.end(); ++it)
	{
		number_of_comp.push_back((it->second).size());
	}
	sort(number_of_comp.rbegin(), number_of_comp.rend());

	for (int i=0; i<2; i++)
	{
		cout << number_of_comp[i] << " ";
	}
	return 0;
}
