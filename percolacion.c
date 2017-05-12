#include "percolacion.h"




int main(int argc, char *argv[]){
//////////////////////////////////////////////////////////////////////////////////////////////////////    
  printf("\n PROGRAMA DE PERCOLACION...\n\n");
  
  int TAM=TAM_D;
  alocar(TAM);
  int sem=0;
  int bandera=0;
  int t=0;
  int k=0;
  int kk=0;
  int pc=0;
  double promedio=0.0;
  for(k=16 ; k < 16 + 20*cantidad; k=k+20){
    TAM=k;
    cero(TAM);
    
    printf("\n kk=%i",kk);
  for(sem=0; sem < realizaciones ; sem++){
    
    if(sem%100 ==0){
      printf("\n realizacion=%i",sem);
    }
    
    semilla=sem;
    srand(semilla);
    llenar_random(M,semilla,TAM);
    
    for(probabilidad=0 ; probabilidad < probabilidades ; probabilidad++ ){
      //printf("\n P=%i",probabilidad*10000/probabilidades);
    
    
    bandera=0;
 
      
    llenar(M,mapa,probabilidad*10000/probabilidades,TAM);
   
    clase[0] = 0;
    clase[1] = 1;
    
    frag_max = hoshen(mapa, TAM, clase);
    corregir_etiquetas(mapa,clase,TAM);

    calculo_ns(mapa,ns,ns_aux,TAM);
    bandera=percolo(mapa, TAM);
    ns[0]=bandera;
      if(bandera!=0){
	salida[probabilidad + probabilidades*sem ]=ns_aux[bandera];
      }
      else{
	vector[sem]=0;
	salida[probabilidad + probabilidades*sem ]=0;
      }

     //salida[probabilidad + probabilidades*sem ]=ns[0];
     
    }
  
  
  
  
  
  }
  
  pc_vector[kk]=encontrar_pc(TAM,salida,contador);
  pc=pc_vector[kk];
  promedio=promedio_tam_percolante(TAM,pc);
  printf("\n TAMANIO=%i   PC=%i   1-PC=%i\n",k,pc_vector[kk], 1000-pc_vector[kk]);
  printf("\n PROMEDIO===%f",promedio);
  vector_prom[kk]=promedio;
  kk=kk+1;
  
  
  }
  //printf("\n \n PC=%i\n",encontrar_pc(TAM,salida,contador));
  /*
    if(bandera!=0)
    printf("Percolo!\n");
  */
  guardar_o(mapa,1,1,TAM);
  guardar_salida(salida,1,1);
  guardar_vector(vector_prom,1,1);

  int m=0;
  for(m=0; m<probabilidades ; m++){
    //printf(" vector(%i)=%f \n",m,contador[m]/realizaciones);
  }

  return 0;
}