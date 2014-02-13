
#include "Clase.h"



int main (){
	system("clear");
	int opcion;
	char nombrefichero[50];
	GRAFO G(nombrefichero);
	while(true) 
    {
		opcion = menu ();
		switch (opcion)
		{
			case 1:
				system("clear");
				cout << "Introduzca el nombre del fichero a cargar: ";
				cin >> nombrefichero;
				G.cargargrafo(nombrefichero);
				break;
				
			case 2:
				system("clear");
				G.FordFulkerson();
				break;
				
			case 3:
				cout << "Adios!!" << endl;
				return 0;
				break;
				
		}
    }
	return 0;
}
