#include <iostream>
#include <string>
#define INF 1000000

using namespace std;

int *Dijkstra(const int, const int * const *, const int, int *);
void printPath(const int *, int, int);

int main(void){
	int n;
	cin >> n;

	int **adj = new int *[n];

	for (int i = 0; i < n; i++){
		adj[i] = new int[n];

		for (int j = 0; j < n; j++)
			cin >> adj[i][j];
	}

	string show_path;
	cin >> show_path;

	for (int i = 0; i < n; i++){
		int *SPT = new int [n];// shortest path table
		int *path;

		path = Dijkstra(n, adj, i, SPT);

		for (int j = 0; j < n; j++){
			if (SPT[j] != INF && j != i){

				// printf("Path(%d,%d):", i, j);
				cout << "Path(" << i << "," << j << "):";
				if (show_path == "Show-path"){
					printPath(path, i, j);
					cout << "->" << j;
				}
				cout << endl;

				// printf("Cost:%d\n", SPT[j]);
				cout << "Cost:" << SPT[j] << endl;
			}
		}
		delete [] SPT;
	}

	return 0;
}

int *Dijkstra(const int n, const int * const *adj, const int source, int *SPT){
	int *path = new int[n]; // the shortest path
	bool *CL = new bool[n]; // correct league 
	bool *IT = new bool[n]; // in tree?

	for (int i = 0; i < n; i++){
		SPT[i] = INF;
		path[i] = -1;
		CL[i] = false;
		IT[i] = false;
	}
	SPT[source] = 0;
	path[source] = -1;
	CL[source] = true;
	IT[source] = true;

	for (int i = 0; i < n; i++){
		if (adj[source][i]){
			SPT[i] = adj[source][i];
			path[i] = source;
			IT[i] = true;
		}
	}

	do {
		int SN = INF; //smallest number
		int SV = -1; // smallest number's vertex
		for (int i = 0; i < n; i++){
			if (!CL[i] && SPT[i] < SN){
				SN = SPT[i];
				SV = i;
			}
		}

		if (SV == -1) break;

		CL[SV] = true;

		for (int i = 0; i < n; i++){
			if (adj[SV][i] && !IT[i] && adj[SV][i] + SPT[SV] < SPT[i]){
				SPT[i] = adj[SV][i] + SPT[SV];
				IT[i] = true;
				path[i] = SV;
			}
		}
	} while(1);

	return path;
}

void printPath(const int *path, int source, int i){
	if (i == source) return;

	printPath(path, source, path[i]);

	if (path[i] == source)
		cout << path[i];
	else
		cout <<"->" << path[i];
}