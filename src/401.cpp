#include <stdlib.h>
#include <string.h>
#include <iostream>
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
		G[c1 - 'A'][c2 - 'A']= true;
	}
}

void bpp(int v) {
	visitado[v]= true;
	cout << char(v + 'A');
	for (int w = 0; w < nnodos; w++) {
		if (!visitado[w] && G[v][w]) {
			bpp(w);
		}
	}
}

void busquedaPP(void) {
	memset(visitado, 0, sizeof(visitado));
	for(int v = 0; v < nnodos; v++) {
		if(!visitado[v]) {
			bpp(v);
		}
	}
	cout << endl;
}

int main (void) {
	int ncasos;
	cin >> ncasos;
	for(int i = 0; i < ncasos; i++) {
		leeGrafo();
		busquedaPP();
	}
}
