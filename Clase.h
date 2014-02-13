#ifndef _GRAPH_H
#define _GRAPH_H


#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>

using namespace std;


#define gotoxy(x,y)  printf("\33[%d;%dH",y,x)
#define clrscr()     gotoxy(1,1); printf("\33[2J")

const unsigned UERROR = 65000;
const unsigned int maxint=65000;

// Definición de un elemento de una lista de Adyacencia
typedef struct { 
	unsigned		j;				// nodo
	int				capacidad;		// capacidad del arco 
	int				residuo;		// capacidad residual del arco 
	unsigned		inv;			// nos idica la posición del arco (j,i) en
									//LS[j], de esta manera podemos acceder en O(1) a dicho arco.
} ElementoLista;					// Definición de una lista de adyacencia de un nodo typedef vector<ElementoLista> LAnodo;

typedef vector<ElementoLista> LAnodo;

class GRAFO
{ 
	unsigned			n;				// no de nodos
	unsigned			m;				// no de arcos
	vector<LAnodo>		LS;				// Lista de adyacencia de los Sucesores
	void dfs(unsigned i, unsigned t, vector<unsigned> &pred, vector<unsigned> &pospred, vector<int> &CuelloBotella); 
	
public:
	
	void cargargrafo(char nombrefichero[50]);
	GRAFO(char nombrefichero[]);		// constructor 
	~GRAFO();							// destructor 
	void MostrarGrafo();				// Método para mostrar el grafo por pantalla
	void FordFulkerson();				//algoritmo de Ford & Fulkerson
};

GRAFO::GRAFO(char nombrefichero[50]) //constructor
{ 
	n = 0;
	m = 0;  
}

GRAFO::~GRAFO() { 
    LS.clear();
} //destructor

void GRAFO::dfs(unsigned i, unsigned t, vector<unsigned> &pred, vector<unsigned> &pospred, vector<int> &CuelloBotella)
{
	int k;
	int m = 0;
	cout << "s es: " << i << endl;
	cout << "t es: " << t << endl;
	if (i != t) {
		cout << "dfs1" << endl;
		for (k = 0; k < LS[i].size(); k++) {
			cout << "dfs2" << endl;
			cout << pred[LS[i][k].j] << endl;
			cout << LS[i][k].residuo << endl;
			if ((pred[LS[i][k].j] == UERROR) && (LS[i][k].residuo > 0)) {
				cout << "dfs3" << endl;
				pred[LS[i][k].j] = i;
				cout << "dfs4" << endl;
				pospred[LS[i][k].j] = k;
				cout << "dfs5" << endl;
				if (CuelloBotella[i] <= LS[i][k].residuo) {
					m = CuelloBotella[i];
				}
				else {
					m = LS[i][k].residuo;
				}
				CuelloBotella[LS[i][k].j] = m;
				cout << "dfs6" << endl;
				cout << LS[i][k].j << "  " << endl;
				dfs(LS[i][k].j, t, pred, pospred, CuelloBotella);
				cout << "dfs7" << endl;
				
			}
		}
	}

}	
	
int menu () //menú del programa
{
	int opc = 0;
	cout << "1. Cargar Grafo." << endl;
	cout << "2. Mostrar Grafo." << endl;
	cout << "3. Salir"<<endl;
	cout << "Opcion: ";
	do
	{
		cin >> opc;
		
	}while ( opc > 4 || opc < 1);
	
	return (opc);
}
	
void GRAFO::cargargrafo(char nombrefichero[50]) //metodo para cargar un grafo
{
	unsigned int i, j, k,p;
	ElementoLista dummy;
	ElementoLista dummy1;
	ifstream tex;
	tex.open(nombrefichero);
	if (tex.is_open())
	{
		LS.clear();
		tex >> n >> m;
		LS.resize(n);
		k = 0;
		for (k=0;k<m;k++)
		{
			tex >> i >> j >> p;
			
			
			dummy.capacidad = p;
			dummy.j = j-1;
			dummy.residuo = p;
			dummy.inv = LS[i-1].size();
			
			dummy1.capacidad = 0;
			dummy1.j = i-1;
			dummy1.residuo = 0;
			dummy1.inv = LS[j-1].size();
			
			LS[i - 1].push_back(dummy);
			
			LS[j - 1].push_back(dummy1);
		}
	}
	else {
		cout << "ERROR1: No se ha podido acceder al fichero" << endl;
	}
	unsigned w, q;
	cout << "NODO    SUCESOR CAPACIDAD RESIDUO   INVERSA   " << endl;
	for (w = 0; w < n ; w++){
		cout << "-----------------------------------------------" << endl;
		for (q = 0; q < LS[w].size(); q++){
			cout << w + 1 << "         " << LS[w][q].j + 1 << "         " << LS[w][q].capacidad << "         " << LS[w][q].residuo << "         " << LS[w][q].inv << endl;
		}
	}
	

	tex.close(); 
}

void GRAFO::FordFulkerson()
{
	int maxflow = 0;
	bool camino = true;
	unsigned s, t, k;
	vector<int> CuelloBotella;
	vector<unsigned> pred, pospred;
	
	cout << "Introduzca el nodo fuente:" << endl;
	cin >> s;
	s--;
	cout << "Introduzca el nodo sumidero:" << endl;
	cin >> t;
	t--;
	while (camino == true) {
		cout << "FF1" << endl;
		pred.resize(n,UERROR);
		cout << "FF2" << endl;
		pospred.resize(n);
		cout << "FF3" << endl;
		CuelloBotella.resize(n,maxint);
		cout << "FF4" << endl;
		pred[s] = s;
		cout << s << endl;
		dfs(s, t, pred, pospred, CuelloBotella);
		cout << "FF6" << endl;
		if (pred[t] == UERROR) {
			cout << "FF7" << endl;
			camino = false;
			cout << "El Flujo máximo es: " << maxflow << endl;
			
			
		}
		else {
			cout << "FF8" << endl;
			maxflow += CuelloBotella[t];
			k = t;
			cout << "Camino Incremental:" << endl;
			while (k != s) {
				cout << "FF9" << endl;
				LS[pred[k]][pospred[k]].residuo -= CuelloBotella[t];
				cout << "FF10" << endl;
				LS[k][LS[pred[k]][pospred[k]].inv].residuo += CuelloBotella[t];
				k = pred[k];
				cout << "FF11" << endl;

			}
		}

	}
	unsigned i, j;
	cout << "Patrón de Flujo Máximo es: " << endl;
	for (i = 0; i < n; i++){
		for (j = 0; j < LS[i].size(); j++){
			if (LS[i][j].capacidad > 0) {
				cout << "El flujo máximo del nodo " << i << " al nodo: " << LS[i][j].j << " es: " << (LS[i][j].capacidad - LS[i][j].residuo) << endl;
				cout << "RESIDUO " << i << " " << LS[i][j].residuo << endl;
			}
		}
	}
}




#endif