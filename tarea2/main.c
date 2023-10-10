#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


const int MAX = 1000000;
struct charM {
    char** mp;
    int dimension;
};
char* getLine(FILE* fp){
    char temp[MAX];
    int i = 0;
    char c = 'a';
    while(c != '\n' && !feof(fp)){
        c = fgetc(fp);
        if(c == 'B' || c == 'E'|| c == '1'|| c == '2'|| c == '3'|| c == '4'|| c == '/'|| c == '0'){
            temp[i] = c;
            i++;
        }
    }
    size_t u = i;
    char* line = calloc(u,sizeof(char));
    strncpy(line,temp,u);    
    return line;
}


// struct charM* crearMatriz hace una matriz de la sopa de letras contenida en un archivo txt
struct charM* crearMatriz(const char* nombreArchivo){
    char* tmp;
    int i= 0;
    printf("|||||||%s\n", nombreArchivo);
     printf("holaa");
    FILE *fp = fopen(nombreArchivo,"r");
    struct charM* strArray = malloc(sizeof(struct charM));
     printf("holaa");
    if (fp == NULL){
        printf("No se pudo abrir el archivo :c\n");
        return NULL;
    }
    tmp = getLine(fp);
    const int n = strlen(tmp);
    strArray->mp = calloc(n,sizeof(char*));
    strArray->mp[0] = tmp;
    strArray->dimension = strlen(tmp);
    i++;
    while(!feof(fp)){
        strArray->mp[i] = getLine(fp);
        i++;
    }
    printf("rawr");
    fclose(fp);
    return strArray;
}

void printMatriz(struct charM* matrix){
    printf("%d\n",matrix->dimension);
    for(int i = 0;i<matrix->dimension;i++){
        printf("Linea %d: %s\n",i,matrix->mp[i]);
    }
}







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
    struct tableroN ubic;;
    ubic.bUP = 0;
    ubic.bRight = 0;
    ubic.bDown = 0;
    ubic.bLeft = 0;
    FILE *file;
    file = fopen(archiv, "r");
    struct charM* matriz = crearMatriz(archiv);

   if ( matriz->mp[0][2]== 'B'){
                ubic.bLeft = 1;
    }
    if (matriz->mp[2][0] == 'B'){
                ubic.bUP = 1;
    }
    if (matriz->mp[2][4] == 'B'){
                ubic.bDown = 1;
    }
    if (matriz->mp[4][2] == 'B'){
                ubic.bRight = 1;
    }
    printf("miau");
    fclose(file);
    return ubic;
}

void juntarTablas(char inicio[][90],char* tablaCentral, char*tabla_a_unir, struct centros* allcenter, char dir){
    char caracter;
    int m = 0;
     printf("ollaaaa");
    int n = 0;
    for(int i = 0; i<9; i++){

        if (strncmp(allcenter[i].nime, tablaCentral, 10) == 0){
            m = allcenter[i].coord_x;
            n = allcenter[i].coord_y;
        }
    }

    char porsilas[12];
    printf("ollaaaa");
    strncpy(porsilas,tabla_a_unir,12);
    
    FILE* tmp = fopen(porsilas, "r");
    if (tmp == NULL){
        printf("No se pudo abrir el archivo :c\n");
        
    }

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
    
 
    for (int kai = 0; kai<9; kai++){
        if (strncmp(allcenter[kai].nime, "cambiar", 7) == 0 ){
            allcenter[kai].coord_x = m;
            allcenter[kai].coord_y = n;
            strncpy(allcenter[kai].nime, tabla_a_unir, 12);
            break;
        }
    }


    m = m-2;
    int temp = m;
    n = n-2;
    
    while ((caracter = fgetc(tmp)) != EOF){
        if ( caracter == 'B' || caracter == '1' || caracter == '2' || caracter == '3' || caracter == '4' || caracter == 'E' || caracter == '/' || caracter == '0'){
           inicio[m][n] = caracter;
            m++;
        }
        else if(caracter == '\n'){
            n++;
            m = temp ;
        }
    }
    for (int i = 0; i <90; i++){
        for(int j = 0; j<90; j++){
            printf("%c", inicio[i][j]); 
        }
        printf("\n");    
    }    
    fclose(tmp);
}


void verificarTablas(char inicio[][90],char* archivo,char** tableros, char dir, struct centros* allcenter){
    struct tableroN tablaSec;
    struct tableroN tablaTri;
    switch(dir){
        case 'u':
           for(int i = 0; i<9; i++){
                    printf("sas: %s\n",tableros[i]);
                    //aqui esta el sus !!!!!!
                    if(strcmp(tableros[i], "usado") != 0){
                    tablaSec = salidasT(archivo);
                    
                    if(tablaSec.bUP == 1 ){
                        printf("ingreseeeeeee");
                        tablaTri = salidasT(tableros[i]);
                        if (tablaTri.bDown == 1){
                            //juntarTablas(inicio, archivo, tableros[i], allcenter, dir);
                            strcpy(tableros[i], "usado");
                            break;
                        }  
                    }
                }    
            }
            break;
           
        case 'l':
            for(int i = 0; i<9; i++){
                printf("%d", i);
                    if(strcmp(tableros[i], "usado") != 0){
                    tablaSec = salidasT(archivo);
                    printf("%d", tablaSec.bLeft);
                    if(tablaSec.bLeft == 1 ){
                        printf("ingreseeeeeee");
                        tablaTri = salidasT(tableros[i]);
                        if (tablaTri.bRight == 1){
                            juntarTablas(inicio, archivo, tableros[i], allcenter, dir);
                            strcpy(tableros[i], "usado");
                            break;
                        }  
                    }
                }    
            }
            break;
        case 'r':    
            for(int i = 0; i<9; i++){
                printf("%d", i);
                    if(strcmp(tableros[i], "usado") != 0){
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
            }
            break;
        case 'd':    
            for(int i = 0; i<9; i++){
                printf("%d", i);
                    if(strcmp(tableros[i], "usado") != 0){
                    tablaSec = salidasT(archivo);
                    printf("%d", tablaSec.bLeft);
                    if(tablaSec.bDown == 1 ){
                        printf("ingreseeeeeee");
                        tablaTri = salidasT(tableros[i]);
                        if (tablaTri.bUP == 1){
                            juntarTablas(inicio, archivo, tableros[i], allcenter, dir);
                            strcpy(tableros[i], "usado");
                            break;
                        }  
                    }
                }    
            }
            break;    
    }
}

int main(){

char inicio[90][90];
struct centros todos[9];
    for (int i = 0; i < 90; i++){
        for (int j = 0; j < 90; j++){
            inicio[i][j] = '-';
        }
   }
    FILE *file;
    file = fopen("Inicio.txt", "r");
    char caracter;
    int fila = 45;
    int j = 45;
    while ((caracter = fgetc(file)) != EOF){
  
        if (caracter == 'B' || caracter == 'E' || caracter == '1' || caracter == '0' || caracter == '/' || caracter == '1' || caracter == '2' || caracter =='3'|| caracter == '4'){

            inicio[fila][j] = caracter;
            fila++;
        }
        else if(caracter == '\n'){
            j++;
            fila = 45;
        }
    }


    for (int i = 0; i <90; i++){
        for(int j = 0; j<90; j++){
             printf("%c",inicio[j][i]);
            }

        printf("\n");    
    }   
    fclose(file);

   

    for(int rai = 0; rai<9; rai++){
        if (rai == 0){
            strcpy(todos[0].nime, "Inicio.txt");
            todos[0].coord_x = 47;
            todos[0].coord_y = 47; 
        }
        else{
            strcpy(todos[rai].nime, "cambiar");
            todos[rai].coord_x = -1;
            todos[rai].coord_y = -1; 
        }
    }    


    char** tableros = revolverMazoT();
    printf("\n\n");
    verificarTablas(inicio, "Inicio.txt", tableros, 'u', todos);
    char newtable[12];
    for (int i = 0; i<9; i++){
        if (strncmp(todos[i].nime, "tablero", 7) == 0){
            strncpy(newtable, todos[i].nime, 12);
        
        }
        printf(" %s", todos[i].nime);
        printf(" %d", todos[i].coord_x);
        printf(" %d", todos[i].coord_y);    
    }
    //verificarTablas(inicio, newtable, tableros, 'u', todos);
    for (int i = 0; i<9; i++){
        if (strncmp(todos[i].nime, "tablero", 7) == 0){
            strncpy(newtable, todos[i].nime, 12);
        
        }
        printf(" %s", todos[i].nime);
        printf(" %d", todos[i].coord_x);
        printf(" %d", todos[i].coord_y);    
    }
    //verificarTablas(inicio, newtable, tableros, 'u', todos);
 
} 