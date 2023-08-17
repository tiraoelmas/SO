#include <stdio.h>
#include <stdlib.h>

int comprobarSopa(char* clave, char* archivo){
    FILE *arc = fopen(archivo,'r');
    if (arc != NULL){    
        printf("ola");
    }
}

int main(){
    int wa = 0;
    comprobarSopa("sas","archivo.txt");

    return 0;
}
//62ljwehosf