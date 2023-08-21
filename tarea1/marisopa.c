#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

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
}