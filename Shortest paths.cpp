#include <iostream>
#include <string>
#define INF 1000000

using namespace std;

int *Dijkstra(const int, const int * const *, const int, int *);
void printPath(const int *, int, int);

int main(void){
	// total # of vertices
	int n;
	cin >> n;

	// intake the weight matrix
	int **weight = new int *[n];

	for (int i = 0; i < n; i++){
		weight[i] = new int[n];

		for (int j = 0; j < n; j++)
			cin >> weight[i][j];
	}

	// print path or not
	string show_path;
	cin >> show_path;

	// single source - all destination shortest path
	for (int i = 0; i < n; i++){
		int *dist = new int [n];
		int *parent;

		parent = Dijkstra(n, weight, i, dist);

		for (int j = 0; j < n; j++){
			if (dist[j] != INF && j != i){

				// printf("Path(%d,%d):", i, j);
				cout << "Path(" << i << "," << j << "):";
				if (show_path == "Show-path"){
					printPath(parent, i, j);
				}
				cout << endl;

				// printf("Cost:%d\n", dist[j]);
				cout << "Cost:" << dist[j] << endl;
			}
		}
		delete [] dist;
	}

	return 0;
}

int *Dijkstra(const int n, const int * const *weight, const int source, int *dist){
	int *parent = new int[n]; // the parent in shortest path tree
	bool *visit = new bool[n]; // in tree or not

	for (int i = 0; i < n; i++){
		dist[i] = INF;
		parent[i] = -1;
		visit[i] = false;
	}
	dist[source] = 0;
	parent[source] = source;

	int max_edges = n;

	while (max_edges--) {
		int SN = INF; //smallest number
		int SV = -1; // smallest number's vertex

		for (int i = 0; i < n; i++){
			if (!visit[i] && dist[i] < SN){
				SN = dist[i];
				SV = i;
			}
		}

		if (SV == -1) break;

		visit[SV] = true;

		for (int i = 0; i < n; i++){
			if (weight[SV][i] && !visit[i] && weight[SV][i] + dist[SV] < dist[i]){
				dist[i] = weight[SV][i] + dist[SV];
				parent[i] = SV;
			}
		}
	}

	return parent;
}

void printPath(const int *parent, int source, int i){
	if (parent[i] != i)
		printPath(parent, source, parent[i]);


	if (i == source)
		cout << i;
	else
		cout <<"->" << i;
}