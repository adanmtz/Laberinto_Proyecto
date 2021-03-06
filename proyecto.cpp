/*Modifiqué la lectura del archivo para que sea leído como parámetro en main, así como leer el laberinto por memoria dinámica, es decir,
en las funciones de leerArchivo, dimensionMatriz y algo del main */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <stdbool.h>

void leerArchivo();
void MuestraLaberinto();
void mueveJugador(int);
void dimensionaMatriz();
void RecorrerLaberinto() {

int **mat; // Matriz dinamica que guarda los datos del archivo.            
//int m2[100][100];   // Esta matriz mostrara la solucion, aun no la uso
int i, j;
int fil,col; // filas y columnas del laberinto            
int fp,cp; // coordenadas del jugador
int xfin,yfin; // coordenadas de la salida o meta
int xini,yini; // coordenadas iniciales del jugador
const int ARRIBA=0, DERECHA=1, IZQUIERDA=2, ABAJO=3;
int direccion=0; // El jugador inicia viendo hacia arriba
int movs; // Cuenta los movimientos que hace un jugador para llegar a la meta
int espacios; // Cuenta los espacios que hay en un laberitno
bool ya=false; // Indica si ya pasamos por ese lugar
int arriba, abajo, izquierda, derecha; // Aqui guardamos la informacion de la matriz de las 
                                             // cuatro direcciones junto al jugador

void dimensionaMatriz(char ruta[]) {
     bool flag=true; // Sirve para que aumente el numero de columnas solo hasta que encuentre el primer salto de linea
                     // suponiendo que el archivo tiene todas las lineas de igual numero de caracteres
    FILE *archivo;
    char caracter;
    int codigo;
    
    archivo=fopen(ruta,"rt"); // abrimos el archivo en modo lectura de texto("rt")
    if (archivo==NULL) { // En caso de que el archivo no exista o que este mal el nombre
       printf("Error en lectura de archivo\n");
       system("pause");
       exit (EXIT_FAILURE); // Terminacion del programa por falla
    }
    fil=1;col=1;
    while(!feof(archivo)) { // Dimensionamos nuestra matriz
            caracter=fgetc(archivo);
            codigo = caracter; // obtenemos el codigo Ascii de el caracter
            
            if (codigo==10) { // codigo del salto de linea
               fil++; // Si encontramos un enter añadimos una fila mas a nuestra matriz
               if (flag) flag=false; // solo lo hacemos una vez
            } else if (flag) col++;// añadimos una columna mas a nuestra matriz               
    }
    fclose(archivo); 
    
    // Dimensionamos m[][] dinamicamente 
    mat = (int **)malloc (fil*sizeof(int *));        
    for (j=0;j<fil;j++) 
    mat[j] = (int *) malloc (col*sizeof(int));      
}

void leerArchivo(char ruta[]) {
    int ff,cc,codigo;
    FILE *archivo;
    char caracter;      
    
    archivo=fopen(ruta,"rt"); // abrimos el archivo "laberinto.txt" en modo lectura de texto("rt"
    if (archivo==NULL) { // En caso de que el archivo no exista o que este mal el nombre
       printf("Error en lectura de archivo\n");
       system("pause");
       exit (EXIT_FAILURE); // Terminacion del programa por falla
    }
    
    fclose(archivo);      
}

void RecorrerLaberinto() {
    int old_fp,old_cp; // Las usaremos para poner un espacio en donde estaba el jugador
 
      old_fp=fp; old_cp=cp; // Guardamos las coordenadas del jugador, para colocar un espacio cuando se mueva                   
 
      arriba=mat[fp-1][cp];
      abajo=mat[fp+1][cp];
      derecha=mat[fp][cp+1];
      izquierda=mat[fp][cp-1];
 
      // checamos si la meta esta junto al jugador
      if (derecha==3) direccion=DERECHA;
      else if (izquierda==3) direccion=IZQUIERDA;
      else if (arriba==3) direccion=ARRIBA;
      else if (abajo==3) direccion=ABAJO;
 
      // Si no estamos junto a la meta, avanzamos
      else if (direccion==ARRIBA){ // volteando al norte
        if (derecha==1 && arriba==0) {}// Antes de avanzar checamos si hay pared a la derecha 
         else if (derecha==0) direccion=DERECHA;// si no hay pared a la derecha giramos viendo a la derecha         
         else if (izquierda==0) direccion=IZQUIERDA;// si no, si no hay pared en la izq. giramos viendo hacia alla   
         else direccion=ABAJO;// ultima opcion, abajo giramos viendo hacia abajo
      }
      else if (direccion==1){ // volteando al este/derecha
         if (abajo==1 && derecha==0) {}// Antes de avanzar hacia la derecha checamos si hay pared abajo      
         else if (abajo==0) direccion=ABAJO;// si no hay pared abajo giramos a la derecha, mirando abajo
         else if (arriba==0) direccion=ARRIBA;// si no hay pared arriba giramos
         else direccion=IZQUIERDA;// ultima opcion la izquierda
      }
      else if (direccion==3){ // volteando al sur
         if (abajo==0 && izquierda==1) {}// si no hay pared abajo y a la izq. si, avanzamos      
         else if (izquierda==0) direccion=IZQUIERDA;// si no hay pared a la izquierda giramos
         else if (derecha==0) direccion=DERECHA;// si no hay pared a la derecha giramos 
         else direccion=ARRIBA; // ultima opcion arriba
      }
      else if (direccion==2){ // volteando a la izquierda
         if (izquierda==0 && arriba==1) {}// si hay pared arriba y a la izq. no, avanzamos             
         else if (arriba==0) direccion=ARRIBA;// si no hay pared arriba giramos a la derecha,
         else if (abajo==0) direccion=ABAJO;// si no hay pared abajo giramos 
         else direccion=DERECHA;// ultima opcion volver atras, giramos 
      }
 
      mat[old_fp][old_cp]=0; // ponemos un espacio donde estaba el jugador
 
      switch(direccion){ // Movemos al jugador
        case 0:
             mat[fp-1][cp]=2; // actualizamos matriz            
            fp--; // Actualizamos coordenadas del jugador         
        break;
        case 1:
             mat[fp][cp+1]=2; // actualizamos matriz            
             cp++; // Actualizamos coordenadas del jugador           
        break;
        case 2:
             mat[fp][cp-1]=2; // actualizamos matriz            
            cp--; // Actualizamos coordenadas del jugador           
        break;
        case 3:
             mat[fp+1][cp]=2; // actualizamos matriz           
            fp++; // Actualizamos coordenadas del jugador           
        break;
      }
}
 
int main() {
	
	char arch[]=  "laberinto.txt"; //Nombre del archivo que tiene la informacion del laberinto
	
	dimensionaMatriz(arch);       
    leerArchivo(arch); // Leemos archivo de texto con la informacion del laberinto    

    movs=0; fp=xini;cp=yini;// xini y yini son los valores iniciales de las coordenadas del jugador no  cambian
               // fp Y cp, si van cambiando en el transcurso del programa
	
    //MuestraLaberinto();
    while (fp!=xfin || cp!=yfin) {// Cuando encontramos la meta, salimos del ciclo
      RecorrerLaberinto();
      //MuestraLaberinto();
    }
    system("cls");
    printf ("El jugador llego a la meta\n");
    system("pause");
    return 0;
}
