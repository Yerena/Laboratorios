#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<ctype.h>


int ContNumero =0; 
int NumMin;
int NumMax;
int NumProm=0; 


void * minimo(void * arg) {
	int *arreglo = (int *) arg;
	int cont;
	NumMin= arreglo[0];
	for(cont=1; cont < ContNumero; cont++){
		if(arreglo[cont] < NumMin){
			NumMin = arreglo[cont];
		}
	}
	return NULL;
};

void * maximo(void * arg) {
	int *arreglo = (int *) arg;
	int cont;
	NumMax = arreglo[0];
	for(cont=1; cont < ContNumero; cont++){
		if(NumMax < arreglo[cont]){
			NumMax = arreglo[cont];
		}
	}
return NULL;
};



void * promedio(void * arg)
{
	int *arreglo = (int *) arg;
	int cont;
	int suma = 0;
	for(cont=0; cont < ContNumero-1; cont++){
		suma = suma + arreglo[cont];
	}
	NumProm = suma/(ContNumero-1);
	return NULL;
};


int main(int argc, char *argv[]){
	
	pthread_t hilo1;
	pthread_t hilo2;
	pthread_t hilo3;

	
	FILE *archivo;
	archivo = fopen ("Evaluacion3.txt","r");
		if (archivo == NULL){ 
			printf("Error al abrir el archivo de datos.");
		}
		else{
			 
			}

	int cadena[100];
	int buffer;

	
	while(feof(archivo) == 0){
		fscanf(archivo, "%d" ,&buffer);
		cadena[ContNumero] = buffer;
		ContNumero++;
	}
	
	pthread_create(&hilo1,NULL,promedio,&cadena);

	pthread_create(&hilo2,NULL,minimo,&cadena);

	pthread_create(&hilo3,NULL,maximo,&cadena);

	
	pthread_join(hilo1,NULL);
	pthread_join(hilo2,NULL);
	pthread_join(hilo3,NULL);

	printf("El numero promedio de la lista es: %d \n", NumProm);
	printf("El numero mayor de la lista es: %d \n", NumMax);
	printf("El numero menor de la lista es: %d \n", NumMin);

	fclose(archivo);
	return 0;
}
