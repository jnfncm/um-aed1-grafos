#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <queue>
#include <list>
using namespace std;

#define MAX_NODOS 20000

int nnodos;
list<int> G[MAX_NODOS];
bool visitado[MAX_NODOS];
queue<int> camino;
bool retrocedo = false;
bool todosvisitadosv = false;

void leer(void) {
	cin >> nnodos;
	if (nnodos < 0 || nnodos > MAX_NODOS) {
		cerr << "Numero de sitios (" << nnodos << ") no valido\n";
		exit(0);
	}
	for (int i = 0; i < nnodos; i++) {
		G[i].clear();
	}
	int i = -1;
	while (i < nnodos) {
		string linea;
		getline(cin, linea);
		istringstream iss(linea);
		int j;
		while (iss >> j) {
			j--;
			G[i].push_back(j);
		}
		i++;
	}
}

bool todosvisitados() {
	if (todosvisitadosv) {
		return true;
	}
	else {
		bool v = true;
		for (int i = 0; i < nnodos; i++) {
			if (!visitado[i]) {
				v = false;
			}
		}
		return v;
	}
}

void buscar(int v) {
	visitado[v] = true;
	camino.push(v);

	if (v == nnodos - 1) {
		todosvisitadosv = true;
	} else {
		for (list<int>::iterator i = G[v].begin(); i != G[v].end(); i++) {
			if (!todosvisitados() && !visitado[*i]) {
				buscar(*i);
				if (retrocedo) {
					camino.push(v);
					retrocedo = false;
				}
			}
		}
		if (!todosvisitados()) {
			retrocedo = true;
		}
	}
}

void lanzar(void) {
	memset(visitado, 0, sizeof(visitado));
	while (!camino.empty()) {
		camino.pop();
	}
	retrocedo = false;
	todosvisitadosv = false;
	buscar(0);
	if (todosvisitados()) {
		cout << camino.size() << endl;
		while(!camino.empty()) {
			cout << camino.front() + 1 << endl;
			camino.pop();
		}
	} else {
		cout << "INFINITO" << endl;
	}
}

int main(void) {
	int ncasos;
	cin >> ncasos;
	for (int i = 0; i < ncasos; i++) {
		leer();
		cout << "Caso " << i + 1 << endl;
		lanzar();
	}
}
