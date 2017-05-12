#include "percolacion.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void guardar_o(int *matriz,int num,int opcion,int TAM){    // la funcion guardar graba los datos de matriz en un archivo llamado salia-1.dat
  
  if(num==2){
    num=0;
  }
  else{
    num=num/4000;
  }
  FILE *archivo;   // creo el archivo
  char nombre[12];
  char ext[12]=".dat";
  char ruta[22];
  if(opcion==1){
  strncpy(ruta, "./", 22);
  }
  if(opcion==2){
  strncpy(ruta, "./presion_1/", 22);
  }
  if(opcion==3){
  strncpy(ruta, "./presion_2/", 22);
  }
  
  //sprintf(nombre,"%d",num);
  strncpy(nombre, "matriz", 12);
  int largo = strlen(nombre) ;
  strcat(nombre,ext);
  strcat(ruta,nombre);
  //printf("\n  el tam del string es =%i \n",largo);
 
  archivo= fopen(ruta,"w+"); //abro el archivo y le asigno el nombre
  int f=0; 
  int c=0;
  
  for(f=0 ; f<TAM ; f++){ //barro todas las filas de la matriz
    for(c=0 ; c<TAM ; c++){ //barro todas las columnas de la matriz
      fprintf(archivo,"%i	",matriz[TAM*f + c]); //guardo un dato y le doy enter
    }
      fprintf(archivo,"\n"); //cuando termino una fila le doy un enter
  }
  
  
  fclose(archivo); //cierro el archivo
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void llenar_random(int *matriz,int semilla,int TAM){
 int f=0;
 int c=0;
     for(f=0 ; f<(TAM) ; f++){
      for(c=0 ; c<(TAM) ; c++){
      M[f*TAM + c]= rand()%10001;
      }
     }
     
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alocar(int TAM){
  
  M = malloc(sizeof(int)*(TAM*TAM));
  mapa = malloc(sizeof(int)*(TAM*TAM));
  ns = malloc(sizeof(int)*(TAM*TAM));
  ns_aux = malloc(sizeof(int)*(TAM*TAM));
  vector = malloc(sizeof(int)*realizaciones);
  salida = malloc(sizeof(int)*realizaciones*probabilidades);
   clase = (int*)malloc(TAM*TAM*sizeof(int));
   contador = malloc(sizeof(double)*probabilidades);
   pc_vector = malloc(sizeof(int)*cantidad);
   vector_prom=malloc(sizeof(double)*cantidad);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void llenar(int *matriz,int *mapa,int probabilidad,int TAM){
  
 int f=0;
 int c=0;
      for(f=0 ; f<(TAM) ; f++){
      for(c=0 ; c<(TAM) ; c++){
      if(matriz[f*TAM + c]>probabilidad){
	mapa[f*TAM + c]=1;
      }
      else{
	mapa[f*TAM + c]=0;
      }
     }
     }
  
  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int hoshen(int *mapa,int TAM, int *clase)
{
  /*
    Esta funcion implementa en algoritmo de Hoshen-Kopelman.
    Recibe el puntero que apunta a la mapa y asigna etiquetas 
    a cada fragmento de mapa. 
  */

  
  int s,s1,s2,frag;

  s=0;
  s1=0;
  frag=2;     //es el numero de etiqueta actual. Se va actualizando cada vez que encontras un cluster. Arranca = 2 porque es la primer etiqueta disponible

  
  // primer elemento del mapa; lo tengo que tratar diferente porque no tiene contra que comparar

  if (*mapa) frag=actualizar(mapa,clase,0,frag);


  
  
  // primera fila del mapa; la trabajo como caso especial porque no puede entrar en conflicto con una fila anterior
  
  for(int i = 1;i<TAM;i++) 
  {
    if (*(mapa+i)) 
    {
     s1 = *(mapa+i-1);  
     frag=actualizar(mapa+i,clase,s1,frag);
    }
  }
  


  
  // el resto de las filas

  for (int i = TAM; i < TAM*TAM; i=i+TAM) // primer elemento de cada fila
  { //printf("Primer elemento de cada fila: %i\n", i);
    

    if (*(mapa+i))
    {
      s1 = *(mapa+i-TAM);
      frag = actualizar(mapa+i,clase,s1,frag);
    }


    // el resto de cada fila
    for (int j = 1; j < TAM; j++)
    { //printf("%i\n", i+j);
      if(*(mapa+i+j))
      {
        s1 = *(mapa+i+j-TAM);
        s2 = *(mapa+i+j-1);
        

        if (s1*s2>0)
        {
          conflicto_etiqueta(mapa+i+j,s1, s2, clase);
          //printf("s1 y s2 mayor a cero \n");
        }
        else
        {
          if (s1!=0) frag = actualizar(mapa+i+j,clase,s1,frag); //printf("arriba soy 1 \n") 
          else  
          {
            if (s2!=0) frag = actualizar(mapa+i+j,clase,s2,frag); //printf("izquierda soy 1: %i \t %i \n", s2, i+j-1) 
            else frag = actualizar(mapa+i+j,clase,0,frag); //printf("rodeado de ceros: %i \t %i \n", s2, s1)
          }
        }

      }
    }

  }

  return frag;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int actualizar(int *mapa, int *clase, int s, int frag)
{
  if (s!=0) *mapa = s;
  else 
  {
    *mapa = frag;
    //printf("%f\n",*mapa );
    //printf("frag: %i\n", frag);
    clase[frag] = frag;
    //printf("clase[frag]: %i\n", clase[frag]);
    frag++;
  }
  return frag;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void conflicto_etiqueta(int *mapa, int s1,int s2, int *clase)
{
  int s = s2; //defino s como el s2 original por prolijidad. La etiqueta del nuevo va a ser s2 solo que el vector clase se acomoda
  while (clase[s1]<0)
    s1 = -clase[s1];

 while (clase[s2]<0)
    s2 = -clase[s2];
 
 if (s1<s2)
 {
   clase[s2] = -s1;
   actualizar(mapa, clase, s, 0);  //aca la variable frag = 0 porque no es una situacion en donde actualizas nada
 }
 else 
 {
  if(s1>s2)
  {
   clase[s1] = -s2;
   actualizar(mapa,clase,s,0);
  }
  else actualizar(mapa,clase,s,0); //si son iguales s1 y s2
 }

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void corregir_etiquetas(int *mapa, int *clase,int TAM)
{
  for (int i = 0; i < TAM*TAM; ++i)
  {
    while(clase[*(mapa+i)]<0)
    {
      *(mapa+i) = - clase[*(mapa+i)];
    }
    *(mapa+i) = clase[*(mapa+i)];
  }
  
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int percolo(int *mapa, int TAM) 
/*Devuelve un 1 si percolo o un 0 si no percolo. Los prints estan para verificar que lo este haciendo bien, obviamente se pueden sacar*/
{
  for (int i = 0; i < TAM; ++i)
  {
    //printf("%i\n",i );
    for (int j = TAM*TAM - TAM; j < TAM*TAM; ++j)
    {
      //printf("%i\n",j );
      if(mapa[i]==mapa[j] && mapa[i]!=0)
      {
        //printf("Percolo! : mapa[%i]=%i y mapa[%i]=%i\n", i, mapa[i], j, mapa[j] );
        return mapa[i];
      }
    }
  }
  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calculo_ns(int *mapa,int *ns,int *ns_aux,int TAM){
  int f=0;
  int c=0;
  
   for(f=0; f<(TAM*TAM) ;f++){
    ns[f]=0;
    ns_aux[f]=0;
   }
  
  
  for(f=0; f<TAM ;f++){
    for(c=0; c<TAM;c++){
      ns_aux[mapa[TAM*f + c]]= ns_aux[mapa[TAM*f + c]] + 1;
      
      //printf("\n fila=%i  columna=%i-->> mapa=%i   ___  ns_aux=%i   ",f,c,mapa[TAM_M*f + c],ns_aux[mapa[TAM_M*f + c]]);
    }
   }
   
   for(f=1; f<(TAM*TAM) ;f++){
     ns[ns_aux[f]]= ns[ns_aux[f]] + 1;
     
  }
   ns[0]=ns_aux[0];
  
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void guardar_salida(int *matriz,int num,int opcion){    // la funcion guardar graba los datos de matriz en un archivo llamado salia-1.dat
  
  if(num==2){
    num=0;
  }
  else{
    num=num/4000;
  }
  FILE *archivo;   // creo el archivo
  char nombre[12];
  char ext[12]=".dat";
  char ruta[22];
  if(opcion==1){
  strncpy(ruta, "./", 22);
  }
  if(opcion==2){
  strncpy(ruta, "./presion_1/", 22);
  }
  if(opcion==3){
  strncpy(ruta, "./presion_2/", 22);
  }
  
  //sprintf(nombre,"%d",num);
  strncpy(nombre, "salida", 12);
  int largo = strlen(nombre) ;
  strcat(nombre,ext);
  strcat(ruta,nombre);
  //printf("\n  el tam del string es =%i \n",largo);
 
  archivo= fopen(ruta,"w+"); //abro el archivo y le asigno el nombre
  int f=0; 
  int c=0;
  
  for(f=0 ; f<realizaciones ; f++){ //barro todas las filas de la matriz
    for(c=0 ; c<probabilidades ; c++){ //barro todas las columnas de la matriz
      fprintf(archivo,"%i	",matriz[probabilidades*f + c]); //guardo un dato y le doy enter
    }
      fprintf(archivo,"\n"); //cuando termino una fila le doy un enter
  }
  
  
  fclose(archivo); //cierro el archivo
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int encontrar_pc(int TAM,int *salida,double *contador){
  
  int p=0;
  int r=0;
  int bandera=0;
  int pc=0;
  int flag=0;
  for(p=0; p<probabilidades ; p++){
  for(r=0; r< realizaciones ; r++){
    if(salida[r*probabilidades +p]>0){
    contador[p]=contador[p]+1.0;
    }
  }
  }
  
  for(p=0; p<probabilidades ; p++){
    
    if( (contador[probabilidades-p]/realizaciones)>0.5 && flag==0){
      pc=p;
      flag=1;
      printf("\n P=%f		pc=%i",(contador[probabilidades-p ]/realizaciones),pc);
      
    }
  }
  return pc;
}

void cero(int TAM){
  int f=0; 
  int c=0;
  for(c=0; c<probabilidades;c++){
    contador[c]=0.0;
  }
  
  for(f=0 ; f<realizaciones ; f++){ 
    for(c=0 ; c<probabilidades ; c++){
    salida[f*probabilidades + c]=0;
      
    }
  }
  
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double promedio_tam_percolante(int TAM,int pc){
  
  int r=0;
  int p=0;
  double prom=0.0;
  int contador=0;
  p=pc;
  for(r=0; r<realizaciones;r++){
    if(salida[r*probabilidades + 1000-p]>0){
    prom=prom+salida[r*probabilidades + 1000 -p];
    contador=contador + 1;
    }
  }
  printf("\n contador=%i",contador);
  prom=prom/contador;
  return prom;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void guardar_vector(double *vector,int num,int opcion){    // la funcion guardar graba los datos de matriz en un archivo llamado salia-1.dat
  
  if(num==2){
    num=0;
  }
  else{
    num=num/4000;
  }
  FILE *archivo;   // creo el archivo
  char nombre[12];
  char ext[12]=".dat";
  char ruta[22];
  if(opcion==1){
  strncpy(ruta, "./", 22);
  }
  if(opcion==2){
  strncpy(ruta, "./presion_1/", 22);
  }
  if(opcion==3){
  strncpy(ruta, "./presion_2/", 22);
  }
  
  //sprintf(nombre,"%d",num);
  strncpy(nombre, "vector", 12);
  int largo = strlen(nombre) ;
  strcat(nombre,ext);
  strcat(ruta,nombre);
  //printf("\n  el tam del string es =%i \n",largo);
 
  archivo= fopen(ruta,"w+"); //abro el archivo y le asigno el nombre
  int f=0; 
  
  
  for(f=0 ; f<cantidad ; f++){ //barro todas las filas de la matriz

      fprintf(archivo,"%f	",vector[f]); //guardo un dato y le doy enter

  }
  
  
  fclose(archivo); //cierro el archivo
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
