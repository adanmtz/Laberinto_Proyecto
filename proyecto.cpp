/*Amigos, podemos usar este código y ya solo lo modificamos para las caracteristicas qu pide el profe, está en C, y yá es solo modificar
y/o agregar variables, funciones, etc., cualquier cosa por correo o whats, avisenme si están de acuerdo para empezar sobre este código */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
 
int m[100][100]; // Matriz que guarda los datos del archivo. El maximo del laberinto son 100 filas por 100 columnas. 
                 //Se puede modificar
 
int f,c; // filas y columnas del laberinto
int fp,cp; // coordenadas del jugador
int fs,cs; // coordenadas de la salida o meta
const int ARRIBA=0, DERECHA=1, IZQUIERDA=2, ABAJO=3;
int direccion=0; // El jugador inicia viendo hacia arriba
int arriba, abajo, izquierda, derecha; // Aqui guardamos la informacion de la matriz de las 
                                             // cuatro direcciones junto al jugador
 
void leerArchivo() {
     int maxCol;
    FILE *archivo;
    char caracter;
    int codigo;
    bool flag=true; // Sirve para que aumente el numero de columnas solo hasta que encuentre le primer salto de linea
               // suponiendo que el archivo tiene todas las lineas de igual numero de caracteres
 
        archivo=fopen("laberinto.txt","rt"); // abrimos el archivo "laberinto.txt" en modo lectura de texto("rt"
        if (archivo==NULL) { // En caso de que el archivo no exista o que este mal el nombre
           printf("Error en lectura de archivo\n");
           system("pause");
           exit (EXIT_FAILURE); // Terminacion del programa por falla
           }
 
        while(!feof(archivo)) { // Este ciclo sirve para dimensionar nuestra matriz
                caracter=fgetc(archivo);
                codigo = caracter; // obtenemos el codigo Ascii de el caracter
 
                if (codigo==10) { // codigo del salto de linea
                   f++; // Si encontramos un enter añadimos una fila mas a nuestra matriz
                   if (flag) {maxCol=c; flag=false;} // solo lo hacemos una vez
                   c=0;
                } else {
                       m[f][c]=codigo-48;
                       if (m[f][c]==2){fp=f;cp=c;}
                       if (m[f][c]==3){fs=f;cs=c;}
                       c++ ;// añadimos una columna mas a nuestra matriz
                }
        }
        c=maxCol; // si no ponemos esto la matriz queda de una columna
        fclose(archivo);
        //printf ("%d filas, %d columnas",f,maxCol); // para debug
}
/* 
void MuestraLaberinto() {
     // En esta funcion las paredes se muestran como asteriscos "*", el jugador como "J" y la meta como "M"
    system("cls");
    for (int i=0;i<f;i++) {
        for (int ii=0;ii<c;ii++) {
           if (m[i][ii]==1) printf ("*");
           else if (i==fs && ii==cs) printf ("M");
           else if (i==fp && ii==cp) printf ("J");
           else printf (" ");
        }
    printf ("\n");
    }
    //printf ("Direccion %d, arriba %d, abajo %d, derecha %d, izquierda %d\n",direccion,arriba,abajo,derecha,izquierda); // debug
    system("pause"); // esperamos que el usuario presione una tecla
}
 */
void RecorrerLaberinto() {
    int old_fp,old_cp; // Las usaremos para poner un espacio en donde estaba el jugador
 
      old_fp=fp; old_cp=cp; // Guardamos las coordenadas del jugador, para colocar un espacio cuando se mueva                   
 
      arriba=m[fp-1][cp];
      abajo=m[fp+1][cp];
      derecha=m[fp][cp+1];
      izquierda=m[fp][cp-1];
 
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
 
      m[old_fp][old_cp]=0; // ponemos un espacio donde estaba el jugador
 
      switch(direccion){ // Movemos al jugador
        case 0:
             m[fp-1][cp]=2; // actualizamos matriz            
            fp--; // Actualizamos coordenadas del jugador         
        break;
        case 1:
             m[fp][cp+1]=2; // actualizamos matriz            
             cp++; // Actualizamos coordenadas del jugador           
        break;
        case 2:
             m[fp][cp-1]=2; // actualizamos matriz            
            cp--; // Actualizamos coordenadas del jugador           
        break;
        case 3:
             m[fp+1][cp]=2; // actualizamos matriz           
            fp++; // Actualizamos coordenadas del jugador           
        break;
      }
}
 
int main() {
    leerArchivo();
    //MuestraLaberinto();
    while (fp!=fs || cp!=cs) {// Cuando encontramos la meta, salimos del ciclo
      RecorrerLaberinto();
      //MuestraLaberinto();
    }
    system("cls");
    printf ("El jugador llego a la meta\n");
    system("pause");
    return 0;
}
