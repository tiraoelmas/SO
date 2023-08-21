#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX = 1000;

struct charM {
    char*** mp;
    int dimension;
};

void liberar(struct charM* matriz){
    for(int i = matriz->dimension; i>0; i--){
        free(matriz->mp[i]);
    }
    free(matriz->mp);
    free(matriz);
}
char* getLine(FILE* fp){
    char* temp[MAX];
    int i = 0;
    char c = 'a';
    while(c != '\n' && !feof(fp)){
        c = fgetc(fp);
        if(c != ' ' && c != '\n' && c!= -1){
            temp[i] = malloc(1);
            temp[i] = c;
            i++;
        }
    }
    if(temp[strlen(temp)-1]==127){
        temp[strlen(temp)-1] = 0;
    } // por alguna razón a veces se añadia el caracter 127 al final de forma ¿aleatoria?
    char* line = malloc(strlen(temp));
    strcpy(line,temp);
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

    //faltan dos cosas nomas: -quitar espacios a la hora de getear lineas.
    //                        -caso vertical -> trasponer el strArray.
}
 */

struct charM* crearMatriz(const char* nombreArchivo){
    //char temp[MAX];
    char* tmp;
    int i= 0;
    FILE *fp = fopen(nombreArchivo,"r");
    struct charM* strArray = malloc(sizeof(struct charM));
    if (fp == NULL){
        printf("No se pudo abrir el archivo :c\n");
        return NULL;
    }

    tmp = getLine(fp);
    (*strArray).mp = malloc(strlen(tmp));
    strArray->mp[0] = tmp;
    strArray->dimension = strlen(tmp);
    printf("%s (in getLine de largo: %ld) (%d)\n",tmp,strlen(tmp),tmp[strlen(tmp)-1]);
    i++;
    while(!feof(fp)){
        //printf("a\n");
        strArray->mp[i] = getLine(fp);
        printf("Linea %d: %s\n",i+1,strArray->mp[i]);
        i++;
    }
    //sizeof();
    return strArray;
}
int buscarPalabra(struct charM matrix){
    return 0;
}
int trasponerMatriz(struct charM* matrix){
    printf("vamos a trasponer rawr\n");
    char tmp;
    int n = matrix->dimension;
    for(int i = 0;i<n;i++){
        for(int j = i; j<n;j++){
            printf("%d,%d\n",i,j);
            tmp = matrix->mp[i][j];
            //matrix->mp[i][j] = matrix->mp[j][i];
            //matrix->mp[j][i] = tmp;
        }
    }
    return 0;
}
void printMatriz(struct charM* matrix){
    for(int i = 0;i<matrix->dimension;i++){
        printf("%s\n",matrix->mp[i]);
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
int main(){
    printf("Inicio de la ejecución\n");
    int opcion = 4;
    //scanf("%d",&opcion);
    if (opcion == 1){
        //comprobarSopa("SAS","archivo.txt");
    }else if(opcion == 2){
        char prueba[2] = "sa";
        printf("%d\n",prueba[2]);
        //printf("%d\n",strlen(prueba));
    }else if(opcion == 3){
        prueba();
    }else if(opcion == 4){
        struct charM *matrix = crearMatriz("archivo.txt");
        int i = trasponerMatriz(matrix);
        //printMatriz(matrix);
        //liberar(matrix);
    }
    printf("Fin de la ejecución.\n");
    return 0;
}
//62ljwehosf