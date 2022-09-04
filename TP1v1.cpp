#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
using namespace std;
//cargo los nombres en el arreglo nom y prod
void ordenar(float arr[], string prodOrd[],int dim){
	for(int x=0; x<dim;x++){
		for(int i = 0; i < dim-1; i++){
				if(arr[i]> arr[i+1]){
					double aux=arr[i];
					arr[i] = arr[i+1];
					arr[i+1] = aux;
					string aux2 = prodOrd[i];
					prodOrd[i] = prodOrd[i+1];
					prodOrd[i+1] = aux2;

				}
		}
	}
}
void  cargarNombre(string nom[], string prod[], int cantC=8, int  cantP=5){
	int i=0,x=0;
	string n,p;
	fstream nombres;
	nombres.open("Nombres.txt");
	if(!nombres){
		cout<<"no se encontro";
	}
	while(getline(nombres,n)){
		if(i<cantC){
			//cout<<n<<endl;
			nom[i]=n;
		}else{
			prod[x]=n;
			x++;
		}
		i++;
	}
	nombres.close();
}

void cargarDatos( float matPeso[][5], float matKM[][5],float arrEntre[]){
	fstream datos;
	double peso, km;
	int id, idP;
	datos.open("Datos.txt");
		if(!datos){
			cout<<"no se encontro";
		}

	while(datos>>id >> idP >> peso >> km){
	//	cout<<id<<" " << idP<<" " << peso <<" "<< km<<endl;
		matPeso[id][idP]+=peso;
		matKM[id][idP]+=km;
		arrEntre[idP]++;
	}
	datos.close();
}
int main() {
	//variables
	int cant=0, idM,may=0,idMayKm;
	const int cantC=8, cantP=5;
	string nombres[cantC], prod[cantP],dat, prodOrd[cantP];
	float matPeso[cantC][cantP]{}, matKM[cantC][cantP]{},
	kmOrd[cantP], mayKm=0;
	float arrEntre[cantC]{};
	//fstream datos;
	//carga de datos
	cargarNombre(nombres, prod, cantC, cantP);

	//proceso de datos
	cargarDatos(matPeso,matKM,arrEntre);

	//lista los datos
	cout<<"Listado por clientes, de los tipoos de productos"
			" que superan los 13000kg acumulados:"<<endl;
	for(int i =0; i<cantC; i++){
		cout<<nombres[i]<<": ";
		for(int x = 0; x<cantP; x++ ){
			if(matPeso[i][x]>13000 ){
				cant++;
				// solucionar problma con la coma
				cout<<prod[x]<<" ";
				if (cant>may){
					may = cant;
					idM= i;
				}
			}
		}
		cant=0;
		cout<<endl;
	}

	cout<<endl;
	//listar km recorrido
	cout<<"Listado de Km recorridos por "
			"tipo de producto(ascendente):"<<endl;
	for(int i =0; i<cantP; i++){// falta ordenar
		prodOrd[i]=prod[i];
		kmOrd[i]=matKM[idM][i];
		if(matKM[idM][i]>mayKm){
			mayKm = matKM[idM][i];
			idMayKm = i;
		}
	}
	ordenar(kmOrd,prodOrd,cantP);
	for(int i =0; i<cantP; i++){
		cout<<prodOrd[i]<<": ";
		cout<<kmOrd[i]<<endl;
	}
	cout<<endl;
	cout<<"Cantidad de entregas para el producto " <<prod[idMayKm]<<": ";
	cout<<arrEntre[idMayKm];
	return 0;
}
