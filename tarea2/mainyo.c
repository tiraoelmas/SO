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
void generarCartas(int roles[4]){

}
void asignarRoles(){

}

int main(){
    const int lenM;
    struct jugador jugador;
    int pipes[8][2];
    int mazoCartas[4];
    char orden[lenM];
    char input[lenM]; 
    char ret[lenM];
    generarPipes(pipes);
    generarCartas(mazoCartas);
    int id= 0;
    int pid;
    char accion[lenM];
    printf("proceso god: %d\n",getpid());

    
    printf("pipes creadas!\n");

    for(int i = 0;i<4;i++){
        if ((pid=fork())==0){
        
        jugador.id = pid;
        id = i+1;
        jugador.num = id;
        break;}
    }
    printf("Hola, me presento, soy: J%d (%d)\nhijo de:%d\n\n",jugador.num,getpid(),getppid());
    //if(id == 0){jugador;}



    if(id == 0){ //logica principal del juego (en proceso padre)
        printf("padre diciendo wa\n");
        for(int ronda=1;ronda<=15;ronda++){
            printf("\nINICIO DE LA RONDA: %d\n",ronda);

            write(pipes[0][1],"nueva ronda",12);
            for(int turno=1;turno<=4;turno++){
                printf("Es el turno del J%d\n",turno);
                read(pipes[turno][0],accion,lenM);
            }
        }
    }/* else if(id == 1){ //soy el jugador 1 :oooo
        read(pipes[0][0],input,lenM);
        scanf("%s",input);
        //hacer algo con el input
        //generar ret
        printf("%s",input);
        write(pipes[1][1],ret,lenM);
    }
    else if(id == 2){ //soy el jugador 2 >:I
        read(pipes[0][0],input,lenM);
        scanf("%s",input);
        //hacer algo con el input
        //generar ret
        printf("%s",input);
        write(pipes[1][1],ret,lenM);
    }
    else if(id == 3){ //soy el jugador 3 c:
        read(pipes[0][0],input,lenM);
        scanf("%s",input);
        //hacer algo con el input
        //generar ret
        printf("%s",input);
        write(pipes[1][1],ret,lenM);
    }
    else if(id == 4){ //soy el jugador 4 grrr wofwof miau
        read(pipes[0][0],input,lenM);
        scanf("%s",input);
        //hacer algo con el input
        //generar ret
        printf("%s",input);
        write(pipes[1][1],ret,lenM);
    } */
    else{
        if(id==1){
            read(pipes[0][0],input,12);
            if(!strcmp(input,"nueva ronda")){
                printf("Indique la acción a realizar: \n");
                scanf("%s",input);printf("\n");
                //hacer algo con el input
                //generar ret
                printf("echo: %s\n",input);
                write(pipes[id+3][1],ret,lenM);
            }
        }
    }
}