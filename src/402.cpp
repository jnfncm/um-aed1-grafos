#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <queue>
using namespace std;

#define MAX_NODOS 26

int nnodos;
int naristas;
bool G[MAX_NODOS][MAX_NODOS];
bool visitado[MAX_NODOS];

void leeGrafo(void) {
	cin >> nnodos >> naristas;
	if (nnodos < 0 || nnodos > MAX_NODOS) {
		cerr << "Numero de nodos (" << nnodos << ") no valido\n";
		exit(0);
	}
	memset(G, 0, sizeof(G));
	char c1, c2;
	for (int i = 0; i < naristas; i++) {
		cin >> c1 >> c2;
		G[c1 - 'A'][c2 - 'A'] = true;
	}
}

void bpa(int v) {
	queue<int> cola;
	int x, y;
	cout << char(v + 'A');
	visitado[v] = true;
	cola.push(v);
	while(!cola.empty()) {
		x = cola.front();
		cola.pop();
		for(y = 0; y < nnodos; y++) {
			if(!visitado[y] && G[x][y]) {
				visitado[y] = true;
				cout << char(y + 'A');
				cola.push(y);
			}
		}
	}

}

void bpaInit(void) {
	memset(visitado, 0, sizeof(visitado));
	for(int v = 0; v < nnodos; v++) {
		if(!visitado[v]) {
			bpa(v);
		}
	}
	cout << endl;
}

int main (void) {
	int ncasos;
	cin >> ncasos;

	for(int i = 0; i < ncasos; i++) {
		leeGrafo();
		bpaInit();
	}
}
