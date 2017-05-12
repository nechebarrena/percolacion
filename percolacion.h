#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>
#include <libconfig.h>
#include <stdbool.h>
#include <sys/stat.h>



#define TAM_D	128		// tamano matriz
#define Z 	27000		// iteraciones
#define realizaciones 2700
#define probabilidades 1000
#define cantidad 1

int *M;				// matriz original con numeros random
int *mapa;			// matriz mapeada a 0 o 1 dependiendo de la probabilidad
int *clase;     // clase es el array con las etiquetas. Si clase[i]<0 => la etiqueta es falsa y tenes que recorrer el vector hasta encontrar la verdadera.
int semilla;
int probabilidad;
//int n;
int frag_max;	
int *ns;
int *ns_aux;
int *vector;
int *salida;
double *contador;
int *pc_vector;
double *vector_prom;

void guardar_o(int *matriz,int num,int opcion,int TAM);
void llenar_random(int *matriz,int semilla,int TAM);			// no hacia falta que sea double, lo mantuvimos para hacerlo generico.
void alocar(int TAM);
void llenar(int *matriz,int *mapa,int probabilidad,int TAM);
int hoshen(int *mapa,int TAM, int *clase);
int actualizar(int *mapa, int *clase, int s, int frag); // pasar frag como puntero quizas es lo mejor
void conflicto_etiqueta(int *mapa, int s1,int s2, int *clase);
void corregir_etiquetas(int *mapa, int *clase,int TAM);
int percolo(int *mapa, int TAM);
void calculo_ns(int *mapa,int *ns,int *ns_aux,int TAM);
void guardar_salida(int *matriz,int num,int opcion);
int encontrar_pc(int TAM,int *salida,double *contador);
void cero(int TAM);
double promedio_tam_percolante(int TAM,int pc);
void guardar_vector(double *vector,int num,int opcion);

//void etiquetar(int *mapa, int n)
