//Design and implement Parallel Breadth First Search based on existing Algorithms using OpenMP .
#include <iostream>
#include <queue> // bfs algorithms
#include <vector> //adjecency list representation of the graph
#include <omp.h>  //opemmp directivs
using namespace std;
const int MAXN = 100005;//These lines define constants and arrays for storing graph information. 
vector<int> adj[MAXN];//MAXN represents the maximum number of nodes in the graph, and adj is an array of vectors representing adjacency lists for each node.
bool visited[MAXN];//visited is an array to keep track of whether a node has been visited during BFS.

void bfs(int start) {
queue<int> q;
q.push(start);
visited[start] = true;
while (!q.empty()) {
int v = q.front();
q.pop();
// Process node v here
#pragma omp parallel for
for (int i = 0; i < adj[v].size(); i++) {
int u = adj[v][i];
if (!visited[u]) {
visited[u] = true;
q.push(u);
}
}
}
}
int main() {
int n, m, start;
cin >> n >> m >> start;
for (int i = 0; i < m; i++) {
int u, v;
cin >> u >> v;
adj[u].push_back(v);
adj[v].push_back(u);
}
bfs(start);
// Output visited nodes
cout << "Visited nodes: ";for (int i = 1; i <= n; i++) {
if (visited[i]) {
cout << i << " ";
}
}
cout << endl;
return 0;
}
