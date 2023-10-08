#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>



struct tableroN{
    int bUP;
    int bLeft;
    int bRight;
    int bDown;
};

struct jugador{
    int numJugador;
    char nombre[2];
    char carta;
    int coord_x;
    int coord_y;
};









struct jugador*  hacerinicio(){
    char inicio[75][75];
    for (int i = 0; i < 75; i++){
        for (int j = 0; j < 75; j++){
            inicio[i][j] = '-';
        }
   }
    FILE *file;
    file = fopen("Inicio.txt", "r");
    char caracter;
    int fila = 40;
    int j = 40;
    int r = fila+5;
    while ((caracter = fgetc(file)) != EOF){
  
        if (fila< r && caracter != ' ' && caracter != '\n' && caracter != '1' && caracter != '2' && caracter != '3' && caracter != '4'){
            
            inicio[fila][j] = caracter;
            fila++;
        }
        else if(caracter == '\n'){
            j++;
            fila = 40;
        }
    } 

    struct jugador* jugadores = malloc(4*sizeof(struct jugador));
    int k = 0;
    char* nombre = malloc(3*sizeof(char));
    for (int i = 0; i <75; i++){
        for(int j = 0; j<75; j++){
    
                    if(inicio[i][j] ==  'J'){
                        switch (k){
                         
                            case 0:
                                strcpy(nombre,"J1");
                                strcpy(jugadores[k].nombre, nombre);
                                jugadores[k].numJugador = 1;
                                printf("%c1", inicio[i][j]);
                                break;
                            case 1:
                                strcpy(nombre,"J2");
                                strcpy(jugadores[k].nombre, nombre);
                                jugadores[k].numJugador = 2;
                                printf("%c2", inicio[i][j]);
                                break;
                            case 2:
                                strcpy(nombre,"J3");
                                strcpy(jugadores[k].nombre, nombre);
                                jugadores[k].numJugador = 3;
                                printf("%c3", inicio[i][j]);
                                break;
                            case 3:
                                strcpy(nombre,"J4");
                                strcpy(jugadores[k].nombre, nombre);
                                jugadores[k].numJugador = 4;
                                printf("%c4", inicio[i][j]);
                                break;

                        }
                       
                        jugadores[k].coord_x = i;
                        jugadores[k].coord_y = j;
                        k++;
                    }
            else{      
            printf("%c", inicio[i][j]);}
        }
        printf("\n");    
    }
    fclose(file);
    return jugadores;
}

char** revolverMazoT(){
    int array[7];
    srand(time(NULL));
    for (int i = 0; i<7; i++){
        int lugarMazo = rand() % 7 + 1;
        for (int j = 0; j<7; j++){
            if (lugarMazo == array[j]){
                i--;
                break;
            }
            else if (j == 6){
                array[i] = lugarMazo;
                //printf(" %d", array[i]);
            }
        }
    }
    printf("\n");
    int j = 1;
    char** arria = malloc(7*sizeof(char*));
    for (int i = 0; i<7; i++){
        
        if (array[i] == j){
            char real = i+1 + '0';
            char cadenaNum[2];
            cadenaNum[0] = real;
            cadenaNum[1] = '\0';
            char* tablero = malloc(20*sizeof(char));
            strcpy(tablero, "tablero");
            char* txt = ".txt";
            strcat(tablero, cadenaNum); 
            strcat(tablero, txt); 
            arria[j-1] = tablero;
            //printf(" %s", arria[j-1]);
            i = -1;
            j++;
        }
    }
    return arria;
}

struct tableroN salidasT(char* archiv){
    struct tableroN ubic;
    ubic.bUP = 0;
    ubic.bRight = 0;
    ubic.bDown = 0;
    ubic.bLeft = 0;
    char matris[5][5];
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            matris[i][j] = '-';
        }
   }
    FILE *file;
    file = fopen(archiv, "r");
    char caracter;
    int fila = 0;
    int j = 0;
    while ((caracter = fgetc(file)) != EOF){
  
        if (caracter != ' ' && caracter != '\n' && caracter != '1' && caracter != '2' && caracter != '3' && caracter != '4'){
            
            matris[fila][j] = caracter;
            j++;
        }
        else if(caracter == '\n'){
            fila++;
            j = 0;
        }
    } 
    for (int i = 0; i <5; i++){
        for(int j = 0; j<5; j++){
            if ( matris[i][j]== 'B' && i == 0 && j == 2){
                ubic.bUP = 1;
            }
            else if (matris[i][j] == 'B' && i == 2 && j == 0){
                ubic.bLeft = 1;
            }
            else if (matris[i][j] == 'B' && i == 2 && j == 4){
                ubic.bRight = 1;
            }
            else if (matris[i][j] == 'B' && i == 4 && j == 2){
                ubic.bDown = 1;
            }
        }  
    }
    return ubic;
}

int main(){

    struct tableroN odnde = salidasT("Inicio.txt");

    struct jugador* jugadores;
    jugadores = hacerinicio();

    for(int i = 0; i<4; i++){
        printf(" %s", jugadores[i].nombre);
        printf(" %d", jugadores[i].numJugador);
        printf(" %d", jugadores[i].coord_x);
        printf(" %d", jugadores[i].coord_y);
    }



    char** array = revolverMazoT();
    for (int i = 0; i<7; i++){
        printf(" %s", array[i]);
        free(array[i]);
 
    }
    free(array);
} 
