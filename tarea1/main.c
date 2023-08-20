#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX = 1000;

char* getLine(FILE* fp){
    char temp[MAX];
    int i = 0;
    char c = 'a';
    while(c != '\n' && !feof(fp)){
        c = fgetc(fp);
        if(c != ' ' && c != '\n' && c!= -1){
            temp[i] = c;
            i++;
        }
    }
    if(temp[strlen(temp)-1]==127){
        temp[strlen(temp)-1] = 0;
    } // por alguna razón a veces se añadia el caracter 127 al final de forma ¿aleatoria?
    char* line = malloc(strlen(temp));
    strcpy(line,temp);
    printf("%s (in getLine de largo: %ld) (%d)\n",line,strlen(line),line[strlen(line)-1]);
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

int crearMatriz(const char* nombreArchivo){
    //char temp[MAX];
    char* tmp;
    int i= 0;
    FILE *fp = fopen(nombreArchivo,"r");
    if (fp == NULL){
        printf("No se pudo abrir el archivo :c\n");
        return -1;
    }

    tmp = getLine(fp);
    printf("%s (in getLine de largo: %ld) (%d)\n",tmp,strlen(tmp),tmp[strlen(tmp)-1]);
    char** strArray = malloc(strlen(tmp));
    strArray[0] = tmp;
    i++;
    while(!feof(fp)){
        printf("a\n");
        strArray[i] = getLine(fp);
        printf("Linea %d: %s\n",i,strArray[i]);
        i++;
    }
    return 0;
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
        crearMatriz("archivo.txt");
    }
    printf("Fin de la ejecución.\n");
    return 0;
}
//62ljwehosf