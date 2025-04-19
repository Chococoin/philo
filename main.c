#include <stdio.h>
#include <sys/time.h>

int main(void)
{
    struct timeval start;
    struct timeval end;
    long elapsed_time;

    // Obtener tiempo de inicio
    gettimeofday(&start, NULL);

    // Simular una acción (aquí puedes poner cualquier lógica futura de filósofo)
    for (volatile long i = 0; i < 100000000; i++); // Espera artificial

    // Obtener tiempo de final
    gettimeofday(&end, NULL);

    // Calcular tiempo transcurrido en milisegundos
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000L;
    elapsed_time += (end.tv_usec - start.tv_usec) / 1000L;

    // Imprimir el tiempo transcurrido
    printf("Tiempo transcurrido: %ld ms\n", elapsed_time);

    return 0;
}
