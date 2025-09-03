#include <stdio.h>
#include <pthread.h>

void *time_stamp(void *arg)
{
    (void)arg;
    int time = 0;
    while (time < 1000)
    {
        printf("Time Stamp: %d", time);
        time++;
    }
    return NULL;
}

void *turno_de_comer(void *arg)
{
    (void)arg;
    printf("Turno de un filosofo a ver si puede comer.");
    return NULL;
}

void *watch_dies(void *arg)
{
    (void)arg;
    printf("Controla si alguien muere.\n");
    return NULL;
}

int main()
{
    pthread_t clock;

    if(pthread_create(&clock, NULL, turno_de_comer, NULL) != 0)
    {
        printf("Error la crear el thread.\n");
        return 1;
    }
    else
    {
        pthread_create(&clock2, NULL, time_stamp, NULL);
    }
    pthread_detach();
    pthread_join(clock, NULL);
}