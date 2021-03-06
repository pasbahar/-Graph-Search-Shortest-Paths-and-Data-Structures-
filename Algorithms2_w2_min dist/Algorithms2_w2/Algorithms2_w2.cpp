// Algorithms2_w2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <assert.h>
#include <algorithm>
#include <time.h>
#include <set>
using namespace std;

#define MAX_W 1000000
class Edge {
public:
	int tail;
	int w;
	Edge(int t = -1, int weight = MAX_W) :w(weight), tail(t) {}
};
class Node {
public:
	bool isVisited;
	vector<Edge> adj;
	Node() :isVisited(false) {}
	Edge &operator[](int index)
	{
		return adj[index];
	}
};

typedef vector<Node> Graph;
// read from file with adjacency list representation of undirected graph
void getFromtxt(char *name, Graph &graph)
{
	ifstream input;
	input.open(name);//read from a txt file
	if (input.is_open())
	{
		int num = -1;
		int w = 10000;
		char comma = ',';
		std::string line;
		graph.push_back(Node());// graph index begin with 1 not 0
		while (std::getline(input, line))
		{
			std::istringstream streamline(line);
			streamline >> num;//omit the node id
			graph.push_back(Node());//add an node
			while (streamline >> num >> comma >> w)
				graph.back().adj.push_back(Edge(num, w));
		}
	}
}


class Dijkstra
{
public:
	void compute(Graph& graph, int node)
	{
		dp = vector<int>(graph.size(), 0);

		//set source
		graph[node].isVisited = true;
		visited.push_back(node);

		//mainloop 
		mainloop(graph);
		ofstream output("digkstra.txt");
		int index[] = { 7,37,59,82,99,115,133,165,188,197 };
		set<int> indexes(index, index + 10);
		for (int i = 1; i<dp.size(); ++i)
			if (indexes.count(i))output << dp[i] << ',';

	}

	void mainloop(Graph & graph)
	{
		while (visited.size()<graph.size() - 1)
		{
			int next, node, edge;
			findNext(graph, next, node, edge);

			graph[next].isVisited = true;
			dp[next] = dp[node] + graph[node][edge].w;
			visited.push_back(next);
		}

	}

	void findNext(Graph &graph, int &next, int &node, int &edge)
	{
		next = -1; node = -1; edge = -1;
		int min = MAX_W + MAX_W;
		for (int i = 0; i<visited.size(); ++i)
		{
			for (int e = 0; e< graph[visited[i]].adj.size(); ++e)
			{
				int tail = graph[visited[i]][e].tail;
				if (!graph[tail].isVisited)
				{
					if (dp[visited[i]] + graph[visited[i]][e].w<min)
					{
						min = dp[visited[i]] + graph[visited[i]][e].w;
						node = visited[i];
						edge = e;
						next = tail;
					}
				}

			}
		}

	}
private:
	vector<int> path;
	vector<int> dp;
	vector<int> visited;
};

int main()
{
	Graph graph;
	char name[] = "dijkstraData.txt";
	getFromtxt(name, graph);

	Dijkstra Dij;
	Dij.compute(graph, 1);
}
