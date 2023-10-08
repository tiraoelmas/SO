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

struct centros{
    char nime[12];
    int coord_x;
    int coord_y;
};

struct jugador{
    int numJugador;
    char nombre[2];
    char carta;
    int coord_x;
    int coord_y;
};


struct centros* guardarCentros(){
    struct centros* allcenter = malloc(225*sizeof(struct centros));
    int k = 0;
    for (int i = 2; i<75; i = i+5){
        for (int j = 2; j<75; j = j+5){
           allcenter[k].coord_x = i;
           allcenter[k].coord_y = j;
           k++;
        }
    }
    return allcenter;
}




char** revolverMazoT(){
    int tableros[7];
    srand(time(NULL));
    for (int i = 0; i<7; i++){
        int lugarMazo = rand() % 7 + 1;
        for (int j = 0; j<7; j++){
            if (lugarMazo == tableros[j]){
                i--;
                break;
            }
            else if (j == 6){
                tableros[i] = lugarMazo;
                //printf(" %d", tableros[i]);
            }
        }
    }
    printf("\n");
    int j = 1;
    char** arria = malloc(7*sizeof(char*));
    for (int i = 0; i<7; i++){
        
        if (tableros[i] == j){
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
    int m = fila + 5;
    while ((caracter = fgetc(file)) != EOF){
  
        if (j < m && fila < m && caracter != ' ' && caracter != '\n' && caracter != '1' && caracter != '2' && caracter != '3' && caracter != '4'){
            
            matris[fila][j] = caracter;
            fila++;
        }
        else if(caracter == '\n'){
            j++;
            fila = 0;
        }
    } 
    for (int i = 0; i <5; i++){
        for(int j = 0; j<5; j++){
            if ( matris[i][j]== 'B' && i == 2 && j == 0){
                ubic.bUP = 1;
            }
            else if (matris[i][j] == 'B' && i == 0 && j == 2){
                ubic.bLeft = 1;
            }
            else if (matris[i][j] == 'B' && i == 4 && j == 2){
                ubic.bRight = 1;
            }
            else if (matris[i][j] == 'B' && i == 2 && j == 4){
                ubic.bDown = 1;
            }
        }  
    }
    fclose(file);
    return ubic;
}

void juntarTablas(char inicio[][75],char* tablaCentral, char*tabla_a_unir, struct centros* allcenter, char dir){
    char caracter;
    int m = 0;
    int n = 0;
    for(int i = 0; i<7; i++){
        if (strcmp(allcenter[i].nime, tablaCentral) == 0){
            m = allcenter[i].coord_x;
            n = allcenter[i].coord_y;
        }
    }
    printf("%s", tabla_a_unir);
    FILE* tmp = fopen(tabla_a_unir, "r");

    switch (dir){
        case 'u':
            n = n-5;
            break;
        case 'l':
            m = m-5;
            break;
        case 'r':
            m = m+5;
            break;
        case 'd':
            n = n+5;
            break;
    }
    allcenter[1].coord_x = 37;
    
    printf("0000000%d00000000", m);
    for (int kai = 0; kai<7; kai++){
        printf("%d", kai);
        if (strcmp(allcenter[kai].nime, "cambiar") == 0 ){
            allcenter[kai].coord_x = m;
            allcenter[kai].coord_y = n;
            strcpy(allcenter[kai].nime,tabla_a_unir);
        }
    }


    m = m-2;
    int temp = m;
    n = n-2;
    
    int r = m + 5;


    while ((caracter = fgetc(tmp)) != EOF){
        if (m < r && caracter != ' ' && caracter != '\n' && caracter != '1' && caracter != '2' && caracter != '3' && caracter != '4'){
           inicio[m][n] = caracter;
            m++;
        }
        else if(caracter == '\n'){
            n++;
            m = temp ;
        }
        printf(" %d|%d ", m,n);
    }
    int k = 0;
    for (int i = 0; i <75; i++){
        for(int j = 0; j<75; j++){
             if(inicio[i][j] ==  'J'){
                        switch (k){
                            case 0:
                                printf("%c1", inicio[j][i]);
                                break;
                            case 1:
                                printf("%c2", inicio[j][i]);
                                break;
                            case 2:
                                printf("%c3", inicio[j][i]);
                                break;
                            case 3:
                                printf("%c4", inicio[j][i]);
                                break;
                        }
                        k++;
                }

                else{
                    printf("%c", inicio[j][i]);
                }  
            }

        printf("\n");    
    }    
    fclose(tmp);
}


void verificarTablas(char inicio[][75],char* archivo,char** tableros, char dir, struct centros* allcenter){
    struct tableroN tablaSec;
    struct tableroN tablaTri;
    switch(dir){
        case 'u':
            for(int i = 0; i<7; i++){
                printf("%d", i);
                
                    tablaSec = salidasT(archivo);
                    printf("%d", tablaSec.bUP);
                    if(tablaSec.bUP == 1 ){
                        printf("ingreseeeeeee");
                        tablaTri = salidasT(tableros[i]);
                        if (tablaTri.bDown == 1){
                            juntarTablas(inicio, archivo, tableros[i], allcenter, dir);
                            strcpy(tableros[i], "usado");
                            break;
                        }  
                    
                }
            }
            break;
        case 'l':
            for(int i = 0; i<7; i++){
                printf("%d", i);
                
                    tablaSec = salidasT(archivo);
                    printf("%d", tablaSec.bLeft);
                    if(tablaSec.bUP == 1 ){
                        printf("ingreseeeeeee");
                        tablaTri = salidasT(tableros[i]);
                        if (tablaTri.bRight == 1){
                            juntarTablas(inicio, archivo, tableros[i], allcenter, dir);
                            strcpy(tableros[i], "usado");
                            break;
                        }  
                    
                }
            }
            break;
        case 'r':    
            for(int i = 0; i<7; i++){
                printf("%d", i);
                    tablaSec = salidasT(archivo);
                    printf("%d", tablaSec.bLeft);
                    if(tablaSec.bRight == 1 ){
                        printf("ingreseeeeeee");
                        tablaTri = salidasT(tableros[i]);
                        if (tablaTri.bLeft == 1){
                            juntarTablas(inicio, archivo, tableros[i], allcenter, dir);
                            strcpy(tableros[i], "usado");
                            break;
                        }  
                    }
               
            }
            break;
        case 'd':    
            for(int i = 0; i<7; i++){
                printf("%d", i);
                    tablaSec = salidasT(archivo);
                    printf("%d", tablaSec.bLeft);
                    if(tablaSec.bDown == 1 ){
                        printf("ingreseeeeeee");
                        tablaTri = salidasT(tableros[i]);
                        if (tablaTri.bUP == 1){
                            printf("%d", allcenter[0].coord_x);
                            juntarTablas(inicio, archivo, tableros[i], allcenter, dir);
                            strcpy(tableros[i], "usado");
                            break;
                        }  
                    
                }
            }
            break;           
    }
}






























int main(){
    char inicio[75][75];
    struct centros todos[7];
    for (int i = 0; i < 75; i++){
        for (int j = 0; j < 75; j++){
            inicio[i][j] = '-';
        }
    }
    FILE *file;
    printf("sas");
    file = fopen("Inicio.txt", "r");
    char caracter;
    int fila = 35;
    int j = 35;
    int r = fila+5;
    while ((caracter = fgetc(file)) != EOF){
  
        if (fila< r && caracter != ' ' && caracter != '\n' && caracter != '1' && caracter != '2' && caracter != '3' && caracter != '4'){
            
            inicio[fila][j] = caracter;
            fila++;
        }
        else if(caracter == '\n'){
            j++;
            fila = 35;
        }
    }

    printf("sas");
    struct jugador jugadores[4];
    int k = 0;
    char nombre[3];
    for (int i = 0; i <75; i++){
        for(int j = 0; j<75; j++){
             if(inicio[i][j] ==  'J'){
                        switch (k){
                         
                            case 0:
                                strcpy(nombre,"J1");
                                strcpy(jugadores[k].nombre, nombre);
                                jugadores[k].numJugador = 1;
                                //printf("%c1", inicio[j][i]);
                                break;
                            case 1:
                                strcpy(nombre,"J2");
                                strcpy(jugadores[k].nombre, nombre);
                                jugadores[k].numJugador = 2;
                                //printf("%c2", inicio[j][i]);
                                break;
                            case 2:
                                strcpy(nombre,"J3");
                                strcpy(jugadores[k].nombre, nombre);
                                jugadores[k].numJugador = 3;
                                //printf("%c3", inicio[j][i]);
                                break;
                            case 3:
                                strcpy(nombre,"J4");
                                strcpy(jugadores[k].nombre, nombre);
                                jugadores[k].numJugador = 4;
                                //printf("%c4", inicio[j][i]);
                                break;
                        }
                        jugadores[k].coord_x = i;
                        jugadores[k].coord_y = j;
                        k++;
                }

                else{
                    //printf("%c", inicio[j][i]);
                }
            }

        //printf("\n");    
    }    
    fclose(file);

    /*struct centros* probar = guardarCentros();
    for(int g = 0; g<225; g++){
        printf("%d|", probar[g].coord_x);
        printf("%d ", probar[g].coord_y);
    }*/

    /*for(int i = 0; i<4; i++){
        printf(" %s", jugadores[i].nombre);
        printf(" %d", jugadores[i].numJugador);
        printf(" %d", jugadores[i].coord_x);
        printf(" %d", jugadores[i].coord_y);
    }*/
 

    for(int rai = 0; rai<7; rai++){
        if (rai == 0){
            strcpy(todos[0].nime, "Inicio.txt");
            todos[0].coord_x = 37;
            todos[0].coord_y = 37; 
        }
        else{
            strcpy(todos[rai].nime, "cambiar");
            todos[rai].coord_x = -1;
            todos[rai].coord_y = -1; 
        }
    }    



    char** tableros = revolverMazoT();
    printf("sas");
    //verificarTablas(inicio, "Inicio.txt", tableros, 'd', todos);

    for (int i = 0; i<7; i++){
        printf(" %s", todos[i].nime);
        printf(" %d", todos[i].coord_x);
        printf(" %d", todos[i].coord_y);
        
    }

  
    for (int i = 0; i<7; i++){
        //printf(" %s", tableros[i]);
        free(tableros[i]);
    }
    free(tableros);
}