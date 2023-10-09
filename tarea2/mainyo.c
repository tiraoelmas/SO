#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
//
struct jugador{
    int num;
    int id;
    char nombre[2];
    char carta;
    int coord_x;
    int coord_y;
};

void enviar(char* msg, int fd[2]){
    int len = strlen(msg)+1;
    write(fd[1],msg,len);
}
void recibir(char* dest, int fd[2]){
    read(fd[0],dest,25);
}
void generarPipes(int array[8][2]){
    for(int i = 0;i<8;i++){
        pipe(array[i]);
    }
    
}

int main(){
    struct jugador jugador[4];
    int pipes[8][2];
    generarPipes(pipes);
    int id= 0;
    printf("proceso god: %d\n",getpid());

    
    printf("pipes creadas!\n");

    for(int i = 0;i<4;i++){
        int pid=fork();
        if (pid==0){
        jugador[i].id = pid;
        id = i+1;
        jugador[i].num = id;
        break;}
    }

    for(int ronda=0;ronda<15;ronda++){
    }
    printf("soy: J%d (%d)\nhijo de:%d\n\n",id,getpid(),getppid());

}