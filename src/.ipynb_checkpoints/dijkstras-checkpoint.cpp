#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include <algorithm>
#include "dijkstras.h"

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
	struct Compare {
	    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
	        return a.second > b.second; 
	    }
	};
	int numVertices = G.size();
	vector<int> distances(numVertices, INF);
	vector<bool> visited(numVertices, false);
	distances[source] = 0;
	previous[source] = -1;
	priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> minHeap;
	minHeap.push({source, 0}); // (vertex, weight)
	while (!minHeap.empty()) {
	    int u = minHeap.top().first; 
	    minHeap.pop();
	    if (visited[u]) continue;
	    visited[u] = true;
	    for (const Edge& edge : G[u]) {
	        int v = edge.dst;
	        int weight = edge.weight;
	        if (!visited[v] && distances[u] + weight < distances[v]) {
	            distances[v] = distances[u] + weight;
	            previous[v] = u;
	            minHeap.push({v, distances[v]});
	        }
	    }
	}
	return distances;
}
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
	vector<int> path;
	int curr = destination;
	while(previous[curr] != -1){
		path.push_back(curr);
		curr = previous[curr];
	}
	path.push_back(curr);
	reverse(path.begin(), path.end());
	return path;
}
void print_path(const vector<int>& v, int total){
	for(int i: v){
		cout << i << " ";
	}
	cout << endl;
	cout << "Total cost is " << total << endl;
}
