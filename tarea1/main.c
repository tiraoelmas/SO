#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    //printf("%ld\n",u);
    char* line = calloc(u,sizeof(char));
    strncpy(line,temp,u);
    //strcpy(line,temp);
    for(int j = 0;j<strlen(line+1);j++){
        if (line[j]< 65 || line[j]> 90){
            //printf("bra\n\n\n");
        }
    }
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
    printf("orientaciooon: %s\n",tmp);
    strcpy(strArray->orientacion,tmp);
    tmp = getLine(fp);
    const int n = strlen(tmp);
    strArray->mp = calloc(n,sizeof(char*));
    strArray->mp[0] = tmp;
    strArray->dimension = strlen(tmp);
    printf("%s (in getLine de largo: %d) (%d)\n",tmp,n,tmp[n-1]);
    i++;
    while(!feof(fp)){
        //printf("a\n");
        strArray->mp[i] = getLine(fp);
        //printf("Linea %d: %s\n",i+1,strArray->mp[i]);
        i++;
    }
    printf("Linea %d: %s\n",2,strArray->mp[1]);
    //sizeof();
    fclose(fp);
    return strArray;
}
int buscarPalabra(struct charM *matrix, char* clave){
    for(int i = 0;i<matrix->dimension;i++){
        if(strstr(matrix->mp[i],clave) != NULL || strstr(matrix->mp[i],strReverse(clave)) != NULL){
            return 1;
        }
    }
    return 0;
}

int trasponerMatriz(struct charM* matrix){
    printf("vamos a trasponer rawr\n");
    char tmp;
    int n = matrix->dimension;
    //matrix->mp[0][0]='Z';
    for(int i = 0;i<n;i++){
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
int main(){
    //printf("%c",-47);
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
        clock_t start = clock();
        struct charM *matrix = crearMatriz("banco.txt");
        //printf("%d\n",strcmp(matrix->orientacion,"vertical"));
        printf("orientacion: %s\n",matrix->orientacion);
        if(strcmp(matrix->orientacion,"vertical") == 0){
            trasponerMatriz(matrix);
        }
        printMatriz(matrix);
        //printf("%s\n",strReverse("Hola"));

        //clock_t start = clock();
        //for(int p = 0;p<100000000;p++){}
        printf("%d\n",buscarPalabra(matrix,"BANCO"));
        clock_t end = clock();
        double total = (double)(end - start) / CLOCKS_PER_SEC;
        printf("start: %ld\nend: %ld\n",start,end);
        //liberar(matrix);
    }
    printf("Fin de la ejecución.\n");
    return 0;
}
//62ljwehosf