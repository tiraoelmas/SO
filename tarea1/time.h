#include <stdio.h>
#include <time.h>

int main() {
    clock_t start_time, end_time;
    double tiempo_utilizado_cpu;

    start_time = clock();  // Guardar el tiempo de inicio

    //el código maricon

    end_time = clock();  // Guardar el tiempo al final

    tiempo_utilizado_cpu = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;  // Calcular el tiempo de CPU utilizado

    printf("Tiempo de CPU utilizado: %f segundos\n", cpu_time_used);

    return 0;
}
