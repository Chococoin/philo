#include <stdio.h>
#include <sys/time.h>

long get_elapsed_time(struct timeval start)
{
    struct timeval now;
    gettimeofday(&now, NULL);

    long elapsed = (now.tv_sec - start.tv_sec) * 1000L;
    elapsed += (now.tv_usec - start.tv_usec) / 1000L;

    return elapsed;
}

int main(void)
{
    struct timeval start;

    gettimeofday(&start, NULL);

    for (volatile long i = 0; i < 100000000; i++); // Simulación de trabajo

    long elapsed_time = get_elapsed_time(start);

    printf("Tiempo transcurrido: %ld ms\n", elapsed_time);

    return 0;
}
