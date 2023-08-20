#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comprobarSopa(char* clave, char* archivo){
    //int flag = 1;
    //char ** strArray;
    char temp[100];
    int i = 0;
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
            strArray[i] = temp;
            //printf("%d: %s",i2,strArray[i]);
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

int main(){
    printf("Inicio de la ejecución\n");
    int opcion = 1;
    //scanf("%d",&opcion);
    if (opcion == 1){
        comprobarSopa("SAS","archivo.txt");
    }else if(opcion == 2){
        char prueba[2] = "sa";
        printf("%d\n",prueba[2]);
        //printf("%d\n",strlen(prueba));
    }
    printf("Fin de la ejecución.\n");
    return 0;
}
//62ljwehosf