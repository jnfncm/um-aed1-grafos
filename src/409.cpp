#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_PAG_ORIG 1001

int N;
bool M[MAX_PAG_ORIG][MAX_PAG_ORIG];
bool A[MAX_PAG_ORIG][MAX_PAG_ORIG];
vector<list<int>> paginasSimples;
int V[MAX_PAG_ORIG];
int numPagSim;

void leer(void) {
	cin >> N;
	if (N < 0 || N > MAX_PAG_ORIG) {
		cerr << "Numero de pagina originales (" << N << ") no valido\n";
		exit(0);
	}
	memset(M, 0, sizeof(M));
	memset(A, 0, sizeof(A));
	paginasSimples.clear();
	memset(V, -1, sizeof(V));
	numPagSim = 0;
	int i = 0;
	while (i < N + 1) {
		string linea;
		getline(cin, linea);
		istringstream iss(linea);
		int j;
		while (iss >> j) {
			if (j != 0) {
				M[i][j] = true;
			}
		}
		i++;
	}
}

void warshall(void) {
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			A[i][j] = M[i][j];
		}
		A[i][i] = false;
	}

	for (int k = 1; k < N + 1; k++) {
		for (int i = 1; i < N + 1; i++) {
			for (int j = 1; j < N + 1; j++) {
				A[i][j] = A[i][j] || (A[i][k] && A[k][j]);
			}
		}
	}
}

void procesarOriginales(int i, int j) {
	if (V[i] != -1) {
		paginasSimples.at(V[i]).push_back(j);
		V[j] = V[i];
	} else if (V[j] != -1) {
		paginasSimples.at(V[j]).push_back(i);
		V[i] = V[j];
	} else {
		list<int> nueva;
		nueva.push_back(i);
		nueva.push_back(j);
		V[i] = numPagSim;
		V[j] = numPagSim;
		numPagSim++;
		paginasSimples.push_back(nueva);
	}
}

bool comparaSimples(list<int> a, list<int> b) {
	return a.front() < b.front();
}

void acabarSimples(void) {
	for (int i = 1; i < N + 1; i++) {
		if (V[i] == -1) {
			list<int> nueva;
			nueva.push_back(i);
			paginasSimples.push_back(nueva);
			V[i] = numPagSim;
			numPagSim++;
		}
	}
	for (vector<list<int>>::iterator k = paginasSimples.begin(); k != paginasSimples.end(); k++) {
		(*k).sort();
		(*k).unique();
	}
	sort(paginasSimples.begin(), paginasSimples.end(), comparaSimples);
}

void lanzar(void) {
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			if (A[i][j] && A[j][i]) {
				procesarOriginales(i, j);
			}
		}
	}
	acabarSimples();
}

int main(void) {
	int ncasos;
	cin >> ncasos;
	for (int i = 0; i < ncasos; i++) {
		leer();
		cout << "Caso " << i + 1 << ": total ";
		warshall();
		lanzar();
		cout << numPagSim << endl;
		int j = 0;
		for (vector<list<int>>::iterator i = paginasSimples.begin(); i != paginasSimples.end(); i++) {
			j++;
			cout << "Simple " << j << ":";
			for (list<int>::iterator k = (*i).begin(); k != (*i).end(); k++) {
				cout << " " << (*k);
			}
			cout << endl;
		}
	}
}
