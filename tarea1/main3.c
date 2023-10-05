#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

const int MAX = 1000;

struct charM {
    char orientacion[20];
    char** mp;
    int dimension;
};

char* strReverse(char* src){
    int l = strlen(src);
    char* dest = calloc(l,sizeof(char));
    for(int i = 0;i<l;i++){
        dest[i]=src[l-i-1];
    }
    return dest;
}
void liberar(struct charM* matriz){
    for(int i = matriz->dimension; i>0; i--){
        free(matriz->mp[i]);
    }
    free(matriz->mp);
    free(matriz);
}

char* getLine(FILE* fp){
    char temp[MAX];
    int i = 0;
    char c = 'a';
    while(c != '\n' && !feof(fp)){
        c = fgetc(fp);
        if(c >= 65 && c<= 122){
            temp[i] = c;
            i++;
        }
    }
    if(temp[i-1]<65 || temp[i-1]>122){
        temp[i-1] = 0;
    } // por alguna razón a veces se añadia el caracter 127 al final de forma ¿aleatoria?
    //printf("%d\n",i);
    size_t u = i;
    //printf("u1: %ld || ",u);
    char* line = calloc(u,sizeof(char));
    //strncpy(line,temp,u);
    strcpy(line,temp);
    //printf("u2: %ld || ",u);
    //printf("len: %ld\n",strlen(line));
    //printf("%s (in getLine de largo: %ld) (%d)\n",line,strlen(line),line[strlen(line)-1]);
    return line;
}

/* int comprobarSopa(char* clave, char* archivo){
    //int flag = 1;
    //char ** strArray;
    char temp[MAX];
    char temp2[MAX];
    int c;
    int i,u = 0;
    int i2 = 2;
    FILE *arc = fopen(archivo,"r");

    if (arc != NULL){    
        printf("Archivo abierto :D\n");
        fgets(temp,__INT_MAX__,arc);
        int largo = strlen(temp)/2;
        printf("Largo de la sopa de letras: %d\n",largo);
        char* strArray[largo];
        strArray[i] = temp;
        i++;
        while (i<largo){
            fgets(temp,__INT_MAX__,arc);
            while(c != '\n' || c != ' '){
                temp[u] = fgetc(arc);
            }
            strArray[i] = temp;
            printf("%d: %s",i2,strArray[i]);
            i++;
            i2++;
            //TODAS LAS LINEAS TIENEN SALTO DE LINEA 
            //MENOS LA ULTIMA
        }
        //strcat(clave,"miau");
        strcat(strArray[i-1],"\n"); //añadir el ulitmo salto de linea
        printf("%s",strArray[i-1]);
        fclose(arc);
        printf("Archivo cerrado :D\n");

        int j = 0;
        int flag = 0;
        while(!flag && j<=i){
            if(strstr(strArray[j],clave)!=NULL){
                flag = 1;
            }
            j++;
        }
        if (flag){printf("ENCONTRADOOOOO, lo encontre, lo encontre\n");}
        else {printf("tu wea no está >:c\n");}
        return 0;
    }
    else{return -1;}

    //faltan dos cosas nomas: - (R)quitar espacios a la hora de getear lineas.
    //                        -caso vertical -> trasponer el strArray.
}
 */

struct charM* crearMatriz(const char* nombreArchivo){
    char* tmp;
    int i= 0;
    FILE *fp = fopen(nombreArchivo,"r");
    struct charM* strArray = malloc(sizeof(struct charM));
    if (fp == NULL){
        printf("No se pudo abrir el archivo :c\n");
        return NULL;
    }
    tmp = getLine(fp);
    printf("orientaciooon: %s\n",tmp);
    strcpy(strArray->orientacion,tmp);
    tmp = getLine(fp);
    const int n = strlen(tmp);
    printf("%d\n",n);
    strArray->mp = calloc(n,sizeof(char*));
    strArray->mp[0] = tmp;
    strArray->dimension = n;
    //printf("%s (in getLine de largo: %d) (%d)\n",tmp,n,tmp[n-1]);
    i++;
    while(!feof(fp)){
        //printf("a\n");
        strArray->mp[i] = getLine(fp);
        //printf("Linea %d: %s\n",i+1,strArray->mp[i]);
        i++;
    }
    int m = strlen(strArray->mp[1]);
    if(strArray->mp[1][m-1]<65 || strArray->mp[1][m-1]>122){
        strArray->mp[1][m-1] = 0;
    }
    //printf("Linea %d: %s\nchar n%d: %c\n",2,strArray->mp[1],m,strArray->mp[1][m-1]);
    //sizeof();
    fclose(fp);
    return strArray;
}
int buscarPalabra(struct charM *matrix, char* clave){
    for(int i = 0;i<matrix->dimension;i++){
        if(strstr(matrix->mp[i],clave) != NULL || strstr(matrix->mp[i],strReverse(clave)) != NULL){
            printf("%d\n",i);
            return 1;
            
        }
    }
    return 0;
}

int trasponerMatriz(struct charM* matrix){
    printf("vamos a trasponer rawr\n");
    char tmp;
    int n = matrix->dimension;
    printf("n: %d\n",matrix->dimension);
    //matrix->mp[0][0]='Z';
    for(int i = 75;i<n;i++){
        for(int j = i; j<n;j++){
            //printf("%d,%d\n",i,j);
            tmp = matrix->mp[i][j];
            matrix->mp[i][j] = matrix->mp[j][i];
            matrix->mp[j][i] = tmp;
        }
    }
    return 0;
}
void printMatriz(struct charM* matrix){
    printf("%d\n",matrix->dimension);
    for(int i = 0;i<matrix->dimension;i++){
        printf("Linea %d: %s\n",i,matrix->mp[i]);
    }
}
void prueba(){
    FILE *arc = fopen("archivo.txt","r");
    char* linea;
    if (arc != NULL){    
        printf("Archivo abierto :D\n");
        linea = getLine(arc);
        printf("%s\n",linea);
        free(linea);
        return;
    }
}
int carpetas(){
    DIR *dir;
    struct dirent* entry;
    char direct[100] = "./archivos/";
    char cambiar[300];

    const char *archiv = "./archivos";

    if (opendir("./CWD") == NULL){
        mkdir("./CWD", 0700);
    }

    dir = opendir(archiv);
    if (dir==NULL){
        printf("no se abrió el archivo");
        exit(2);
    }

     while ((entry = readdir(dir)) != NULL) {
        if((strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0) ){
        // Procesar la entrada (nombre del archivo) aquí
        printf("Nombre del archivo: %s\n", entry->d_name);
        strcat(direct, entry->d_name);
        FILE *archivo;
        char linea[13];
        char letraSopa[2];
        int contador_horizontal = 0;
        int contador_vertical = 0;
        archivo = fopen(direct, "r");
        if (fgets(linea, sizeof(linea), archivo) != NULL){
            printf("la linea es: %s", linea);    
        }

        fgets(letraSopa, sizeof(letraSopa), archivo);
        contador_horizontal++;
        while(letraSopa[0] != '\n'){
            fgets(letraSopa, sizeof(letraSopa), archivo);
            contador_horizontal++;
        }
        contador_horizontal = (contador_horizontal-1)/2;
        contador_vertical = contador_horizontal;
        printf("el tamaño del archivo es: %dx%d\n", contador_horizontal, contador_vertical);
        printf("\n");
        printf("%d", strcmp(linea, "horizontal"));
        if (strcmp(linea, "vertical") == 13){
            if (opendir("./CWD/vertical") == NULL){
                mkdir("./CWD/vertical", 0700);
            }
            printf("%d\n", contador_horizontal);
            if (contador_horizontal == 50){
                if (opendir("./CWD/vertical/50x50") == NULL){
                    mkdir("./CWD/vertical/50x50", 0700);
                }
                strcpy(cambiar, "./CWD/vertical/50x50/");
                strcat(cambiar, entry->d_name);
                printf("%s", direct);
                rename(direct, cambiar);
            }    
            else if(contador_horizontal == 100){
                if (opendir("./CWD/vertical/100x100") == NULL){
                    mkdir("./CWD/vertical/100x100", 0700);
                }
                strcpy(cambiar, "./CWD/vertical/100x100/");
                strcat(cambiar, entry->d_name);
                printf("%s", direct);
                rename(direct, cambiar);
            }
            else if((contador_horizontal == 200)){
                if (opendir("./CWD/vertical/200x200") == NULL){
                    mkdir("./CWD/vertical/200x200", 0700);
                }
                strcpy(cambiar, "./CWD/vertical/200x200/");
                strcat(cambiar, entry->d_name);
                printf("%s", direct);
                rename(direct, cambiar);

            }
        }    
        if (strcmp(linea, "horizontal") == 13){
            if (opendir("./CWD/horizontal") == NULL){
                mkdir("./CWD/horizontal", 0700);
            }
            printf("%d\n", contador_horizontal);
            if (contador_horizontal == 50){
                if (opendir("./CWD/horizontal/50x50") == NULL){
                    mkdir("./CWD/horizontal/50x50", 0700);
                }
                strcpy(cambiar, "./CWD/horizontal/50x50/");
                strcat(cambiar, entry->d_name);
                printf("%s", direct);
                rename(direct, cambiar);
            }    
            else if(contador_horizontal == 100){
                if (opendir("./CWD/horizontal/100x100") == NULL){
                    mkdir("./CWD/horizontal/100x100", 0700);
                }
                strcpy(cambiar, "./CWD/horizontal/100x100/");
                strcat(cambiar, entry->d_name);
                printf("%s", direct);
                rename(direct, cambiar);
            }
            else if((contador_horizontal == 200)){
                if (opendir("./CWD/horizontal/200x200") == NULL){
                    mkdir("./CWD/horizontal/200x200", 0700);
                }
                strcpy(cambiar, "./CWD/horizontal/200x200/");
                strcat(cambiar, entry->d_name);
                printf("%s", direct);
                rename(direct, cambiar);

            }
        }    
        }

        strcpy(direct, "./archivos/");
        
    }
    return 0;
}
int main(){
    printf("Inicio de la ejecución\n");
    int opcion;
    printf("Que quiere hacer? (1) Ordenar archivos (2) Comprobar sopa de letras\n");
    scanf("%d",&opcion);
    if (opcion == 1){
        carpetas();
    }else if(opcion == 2){
        struct charM *matrix = crearMatriz("hola.txt");
        printf("orientacion: %s\n",matrix->orientacion);
        if(strcmp(matrix->orientacion,"vertical") == 0){
            trasponerMatriz(matrix);
        }
        clock_t start = clock();        
        for (int i = 0; i<100;i++){
            buscarPalabra(matrix,"HOLA");
        }
        clock_t end = clock();
        double total = (double)(end - start) / (CLOCKS_PER_SEC*100);
        printf("start: %ld\nend: %ld\ncocks realizados:%f\n",start,end,total);
    }
    printf("Fin de la ejecución.\n");
    return 0;
}